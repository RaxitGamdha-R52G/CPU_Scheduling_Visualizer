#include "PriorityPreemptiveScheduler.h"

#include "../../ProcessManager/ProcessManager.h"
#include "../../TimelineManager/TimelineManager.h"
#include "../SchedulerContext.h"

#include <algorithm>
#include <vector>
#include <limits>

void PriorityPreemptiveScheduler::run(const PriorityPreemptiveOptions& options) {
    // Copy processes to avoid mutating the manager
    auto processes = ProcessManager::getAllProcesses();
    const int n = static_cast<int>(processes.size());

    for (auto& p : processes) {
        p.remainingTime = p.burstTime;
    }

    // Track last execution time (for aging)
    std::vector<TimeUnit> lastExecutionTime(n);
    for (int i = 0; i < n; ++i) {
        lastExecutionTime[i] = processes[i].arrivalTime;
    }

    // Sort once by arrival time, then PID
    std::sort(processes.begin(), processes.end(),
        [](const ProcessControlBlock& a, const ProcessControlBlock& b) {
            if (a.arrivalTime != b.arrivalTime)
                return a.arrivalTime < b.arrivalTime;
            return a.pid < b.pid;
        });

    int completed = 0;

    while (completed < n) {
        TimeUnit now = SchedulerContext::getCurrentTime();
        int chosen = -1;

        // Apply aging if enabled
        if (options.enableAging) {
            for (int i = 0; i < n; ++i) {
                if (processes[i].remainingTime > 0 &&
                    processes[i].arrivalTime <= now &&
                    lastExecutionTime[i] < now) {

                    TimeUnit waited = now - lastExecutionTime[i];
                    int boosts = waited / options.agingInterval;

                    if (boosts > 0) {
                        processes[i].priority = std::max(
                            0,
                            processes[i].priority - boosts * options.agingStep
                        );
                        lastExecutionTime[i] = now;
                    }
                }
            }
        }

        // Helper: decide if process i is better than process j
        auto isBetter = [&](int i, int j) {
            if (j == -1) return true;

            if (processes[i].priority != processes[j].priority)
                return processes[i].priority < processes[j].priority;

            if (processes[i].arrivalTime != processes[j].arrivalTime)
                return processes[i].arrivalTime < processes[j].arrivalTime;

            return processes[i].pid < processes[j].pid;
            };

        // Select highest-priority among arrived
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= now && processes[i].remainingTime > 0 && isBetter(i, chosen)) {
                chosen = i;
            }
        }

        // CPU idle
        if (chosen == -1) {
            TimeUnit nextArrival = std::numeric_limits<TimeUnit>::max();
            for (const auto& p : processes) {
                if (p.remainingTime > 0) {
                    nextArrival = std::min(nextArrival, p.arrivalTime);
                }
            }
            SchedulerContext::advanceTime(nextArrival - now);
            continue;
        }

        // Find next arrival that could preempt
        TimeUnit nextArrival = std::numeric_limits<TimeUnit>::max();
        for (const auto& p : processes) {
            if (p.remainingTime > 0 && p.arrivalTime > now) {
                nextArrival = std::min(nextArrival, p.arrivalTime);
            }
        }

        TimeUnit exec = (nextArrival == std::numeric_limits<TimeUnit>::max())
            ? processes[chosen].remainingTime
            : std::min(processes[chosen].remainingTime, nextArrival - now);

        TimeUnit start = now;
        TimeUnit end = start + exec;

        TimelineManager::addEntry(processes[chosen].pid, start, end);
        SchedulerContext::advanceTime(exec);

        processes[chosen].remainingTime -= exec;
        if (processes[chosen].remainingTime == 0) {
            completed++;
        }

        // Reset aging clock for running process
        lastExecutionTime[chosen] = SchedulerContext::getCurrentTime();
    }
}
