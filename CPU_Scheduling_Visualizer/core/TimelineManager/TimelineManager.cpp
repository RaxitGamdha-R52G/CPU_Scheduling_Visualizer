#include "TimelineManager.h"
#include <stdexcept>

std::vector<TimelineEntry> TimelineManager::timeline;

void TimelineManager::reset() {
	timeline.clear();
}

void TimelineManager::addEntry(
	int pid,
	TimeUnit startTime,
	TimeUnit endTime
) {
	if (endTime <= startTime) throw std::invalid_argument("Invalid timeline entry duration");

	// Sanity check: No overlap
	if (!timeline.empty()) {
		const TimelineEntry& last = timeline.back();
		if (startTime < last.endTime) throw std::logic_error("Timeline overlap detected");
	}

	timeline.emplace_back(pid, startTime, endTime);
}

const std::vector<TimelineEntry>& TimelineManager::getTimeline() {
	return timeline;
}