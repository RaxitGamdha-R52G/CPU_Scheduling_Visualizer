#include "SJFScheduler.h"

#include "../../ProcessManager/ProcessManager.h"
#include "../../TimelineManager/TimelineManager.h"
#include "../SchedulerContext.h"

#include <algorithm>
#include <vector>

void SJFScheduler::run() {
	// Copy processes to avoid mutating the manager
	std::vector<ProcessControlBlock> processes = ProcessManager::getAllProcesses();

	const int n = static_cast<int>(processes.size());
	std::vector<bool> completed(n, false);
	int completedCount = 0;

	// Sort once by arrival time, then PID
	sort(processes.begin(), processes.end(),
		[](const ProcessControlBlock& a, const ProcessControlBlock& b) {
			if (a.arrivalTime != b.arrivalTime) return a.arrivalTime < b.arrivalTime;
			return a.pid < b.pid;
		});

	while (completedCount < n) {
		TimeUnit currentTime = SchedulerContext::getCurrentTime();

		int chosenIndex = -1;
		TimeUnit minBurst = std::numeric_limits<TimeUnit>::max();

		// Select shortest job among arrived & not completed
		for (int i = 0; i < n; i++) {
			if (!completed[i] && processes[i].arrivalTime <= currentTime) {
				if (processes[i].burstTime < minBurst) {
					minBurst = processes[i].burstTime;
					chosenIndex = i;
				}
			}
		}

		// If no process has arrived, CPU is idle
		if (chosenIndex == -1) {
			// Find next arrival
			TimeUnit nextArrival = std::numeric_limits<TimeUnit>::max();
			for (int i = 0; i < n; ++i) {
				if (!completed[i]) {
					nextArrival = std::min(nextArrival, processes[i].arrivalTime);
				}
			}
			SchedulerContext::advanceTime(nextArrival - currentTime);
			continue;
		}

		// Execute chosen process
		TimeUnit startTime = SchedulerContext::getCurrentTime();
		TimeUnit endTime = startTime + processes[chosenIndex].burstTime;

		TimelineManager::addEntry(
			processes[chosenIndex].pid,
			startTime,
			endTime
		);

		SchedulerContext::advanceTime(processes[chosenIndex].burstTime);
		completed[chosenIndex] = true;
		completedCount++;
	}
}