#include "SRTFScheduler.h"

#include "../../ProcessManager/ProcessManager.h"
#include "../../TimelineManager/TimelineManager.h"
#include "../SchedulerContext.h"

#include <algorithm>
#include <vector>
#include <limits>

void SRTFScheduler::run() {
	// Copy processes to avoid mutating the manager
	std::vector<ProcessControlBlock> processes = ProcessManager::getAllProcesses();

	const int n = static_cast<int>(processes.size());

	// Initialize remaining times
	for (auto& p : processes) {
		p.remainingTime = p.burstTime;
	}

	int completedCount = 0;
	int currentIndex = -1;

	// Sort once by arrival time, then PID
	sort(processes.begin(), processes.end(),
		[](const ProcessControlBlock& a, const ProcessControlBlock& b) {
			if (a.arrivalTime != b.arrivalTime) return a.arrivalTime < b.arrivalTime;
			return a.pid < b.pid;
		});

	while (completedCount < n) {
		TimeUnit currentTime = SchedulerContext::getCurrentTime();

		int chosenIndex = -1;
		TimeUnit minRemaining = std::numeric_limits<TimeUnit>::max();

		// Select process with shortest remaining time
		for (int i = 0; i < n; i++) {
			if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
				if (processes[i].remainingTime < minRemaining) {
					minRemaining = processes[i].remainingTime;
					chosenIndex = i;
				}
			}
		}

		// If no process has arrived, CPU is idle
		if (chosenIndex == -1) {
			// Find next arrival
			TimeUnit nextArrival = std::numeric_limits<TimeUnit>::max();
			for (int i = 0; i < n; ++i) {
				if (processes[i].remainingTime > 0) {
					nextArrival = std::min(nextArrival, processes[i].arrivalTime);
				}
			}
			SchedulerContext::advanceTime(nextArrival - currentTime);
			continue;
		}

		// Determine next event (arrival or completion)
		TimeUnit nextArrival = std::numeric_limits<TimeUnit>::max();
		for (int i = 0; i < n; ++i) {
			if (processes[i].remainingTime > 0 &&
				processes[i].arrivalTime > currentTime) {
				nextArrival = std::min(nextArrival,
					processes[i].arrivalTime);
			}
		}

		TimeUnit execTime;
		if (nextArrival == std::numeric_limits<TimeUnit>::max()) {
			execTime = processes[chosenIndex].remainingTime;
		}
		else {
			execTime = std::min(
				processes[chosenIndex].remainingTime,
				nextArrival - currentTime
			);
		}

		// Execute chosen process
		TimeUnit startTime = currentTime;
		TimeUnit endTime = startTime + execTime;

		TimelineManager::addEntry(
			processes[chosenIndex].pid,
			startTime,
			endTime
		);

		SchedulerContext::advanceTime(execTime);
		processes[chosenIndex].remainingTime -= execTime;

		if (processes[chosenIndex].remainingTime == 0) {
			completedCount++;
		}
	}
}