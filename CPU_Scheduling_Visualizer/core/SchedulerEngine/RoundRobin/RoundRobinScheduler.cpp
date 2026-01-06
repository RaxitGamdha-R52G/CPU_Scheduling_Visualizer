#include "RoundRobinScheduler.h"

#include "../../ProcessManager/ProcessManager.h"
#include "../../TimelineManager/TimelineManager.h"
#include "../SchedulerContext.h"

#include <queue>
#include <algorithm>
#include <vector>
#include <limits>
#include <stdexcept>

void RoundRobinScheduler::run(int timeQuantum) {
	if (timeQuantum <= 0) {
		throw std::invalid_argument("TimeQuantum must be > 0");
	}
	// Copy processes to avoid mutating the manager
	std::vector<ProcessControlBlock> processes = ProcessManager::getAllProcesses();

	const int n = static_cast<int>(processes.size());

	// Sort once by arrival time, then PID
	sort(processes.begin(), processes.end(),
		[](const ProcessControlBlock& a, const ProcessControlBlock& b) {
			if (a.arrivalTime != b.arrivalTime) return a.arrivalTime < b.arrivalTime;
			return a.pid < b.pid;
		});


	std::queue<int> readyQueue;
	int nextArrivalIndex = 0;
	int completedCount = 0;
	
	// Initialize remaining times
	for (auto& pcb : processes) {
		pcb.remainingTime = pcb.burstTime;
	}

	while (completedCount < n) {
		TimeUnit currentTime = SchedulerContext::getCurrentTime();

		// Enqueue newly arrived processes
		while (nextArrivalIndex < n && processes[nextArrivalIndex].arrivalTime <= currentTime) {
			readyQueue.push(nextArrivalIndex);
			nextArrivalIndex++;
		}

		// If no process is ready, CPU is idle
		if (readyQueue.empty()) {
			if (nextArrivalIndex < n) {
				TimeUnit nextArrival = processes[nextArrivalIndex].arrivalTime;
				SchedulerContext::advanceTime(nextArrival - currentTime);
			}
			continue;
		}

		int idx = readyQueue.front();
		readyQueue.pop();

		TimeUnit execTime = std::min((TimeUnit)timeQuantum, processes[idx].remainingTime);

		TimeUnit startTime = SchedulerContext::getCurrentTime();
		TimeUnit endTime = startTime + execTime;

		// Record execution slice
		TimelineManager::addEntry(
			processes[idx].pid,
			startTime,
			endTime
		);


		SchedulerContext::advanceTime(execTime);
		processes[idx].remainingTime -= execTime;

		// Enqueue any process that arrived during this slice
		currentTime = SchedulerContext::getCurrentTime();
		while (nextArrivalIndex < n && processes[nextArrivalIndex].arrivalTime <= currentTime) {
			readyQueue.push(nextArrivalIndex);
			nextArrivalIndex++;
		}

		// If process not finished, re-enqueue
		if (processes[idx].remainingTime > 0) {
			readyQueue.push(idx);
		}
		else {
			completedCount++;
		}
	}
	
}