#include "TimeCalculator.h"

#include "../core/TimelineManager/TimelineManager.h"
#include "../core/ProcessManager/ProcessManager.h"

#include <limits>

std::unordered_map<int, ProcessMetrics> TimeCalculator::computeProcessMetrics() {
	std::unordered_map<int, ProcessMetrics> metrics;

	const auto& timeline = TimelineManager::getTimeline();
	const auto& processes = ProcessManager::getAllProcesses();

	// Initialize completion times
	for (const auto& pcb : processes) {
		metrics[pcb.pid] = {
			std::numeric_limits<TimeUnit>::max(),
			0, 0, 0, 0
		};

	}

	// Process timeline
	for (const auto& entry : timeline) {
		auto& m = metrics[entry.pid];

		// First time the process runs
		if (m.startTime == std::numeric_limits<TimeUnit>::max()) {
			m.startTime = entry.startTime;
			m.responseTime = entry.startTime -
				ProcessManager::getAllProcesses()[entry.pid - 1].arrivalTime;
		}

		m.completionTime = entry.endTime;
	}

	// Compute waiting & turnaround times

	for (const auto& pcb : processes) {
		auto& m = metrics[pcb.pid];
		m.turnaroundTime = m.completionTime - pcb.arrivalTime;
		m.waitingTime = m.turnaroundTime - pcb.burstTime;
	}

	return metrics;
}