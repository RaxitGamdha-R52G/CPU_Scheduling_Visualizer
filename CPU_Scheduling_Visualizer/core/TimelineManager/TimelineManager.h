#pragma once

#include <vector>
#include "TimelineEntry.h"

class TimelineManager {
public:
	static void reset();

	static void addEntry(
		int pid,
		TimeUnit startTime,
		TimeUnit endTime
	);

	static const std::vector<TimelineEntry>& getTimeline();

private:
	static std::vector<TimelineEntry> timeline;
};