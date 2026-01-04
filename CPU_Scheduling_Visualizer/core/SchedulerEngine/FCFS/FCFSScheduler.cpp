#include "FCFSScheduler.h"

#include "../../ProcessManager/ProcessManager.h"
#include "../../TimelineManager/TimelineManager.h"
#include "../SchedulerContext.h"

#include <algorithm>
#include <vector>

void FCFSScheduler::run() {
	// Copy processes for sorting to avoid mutating the manager
	std::vector<ProcessControlBlock> processes = ProcessManager::getAllProcesses();

	// Sort by arrival time, then by PID
	std::sort(processes.begin(), processes.end(),
		[](const ProcessControlBlock& a, const ProcessControlBlock& b) {
			if (a.arrivalTime != b.arrivalTime) return a.arrivalTime < b.arrivalTime;
			return a.pid < b.pid;
		});

	for (auto& pcb : processes) {
		TimeUnit currentTime = SchedulerContext::getCurrentTime();

		// Skip time if CPU is idle
		if (currentTime < pcb.arrivalTime) {
			SchedulerContext::advanceTime(pcb.arrivalTime - currentTime);
			currentTime = pcb.arrivalTime;
		}

		// Execute process
		TimeUnit startTime = currentTime;
		TimeUnit endTime = startTime + pcb.burstTime;

		TimelineManager::addEntry(pcb.pid, startTime, endTime);
		SchedulerContext::advanceTime(pcb.burstTime);

		
	}

}