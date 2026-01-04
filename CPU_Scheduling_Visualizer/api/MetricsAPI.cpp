#include "MetricsAPI.h"

#include "../utils/TimeCalculator.h"
#include "../core/TimelineManager/TimelineManager.h"
#include "../core/ProcessManager/ProcessManager.h"

double MetricsAPI::averageWaitingTime() {
	auto metrics = TimeCalculator::computeProcessMetrics();

	double sum = 0;
	for (const auto& [_, m] : metrics) {
		sum += m.waitingTime;
	}

	return sum / metrics.size();
}

double MetricsAPI::averageTurnaroundTime() {
	auto metrics = TimeCalculator::computeProcessMetrics();

	double sum = 0;
	for (const auto& [_, m] : metrics) {
		sum += m.turnaroundTime;
	}

	return sum / metrics.size();
}

double MetricsAPI::cpuUtilization() {
	const auto& timeline = TimelineManager::getTimeline();

	if (timeline.empty()) return 0.0;

	TimeUnit busyTime = 0;
	for (const auto& entry : timeline) {
		busyTime += entry.endTime - entry.startTime;
	}

	TimeUnit totalTime = timeline.back().endTime;
	return static_cast<double>(busyTime) / totalTime;
}

double MetricsAPI::throughput() {
	const auto& processes = ProcessManager::getAllProcesses();
	const auto& timeline = TimelineManager::getTimeline();

	if (timeline.empty()) return 0.0;
	return static_cast<double>(processes.size()) / timeline.back().endTime;
}