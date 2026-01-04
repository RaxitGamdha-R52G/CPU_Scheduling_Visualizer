#pragma once

#include <unordered_map>
#include "../core/TimelineManager/TimelineEntry.h"

struct ProcessMetrics {
	TimeUnit startTime;
	TimeUnit completionTime;
	TimeUnit waitingTime;
	TimeUnit turnaroundTime;
	TimeUnit responseTime;
};


class TimeCalculator {
public:
	static std::unordered_map<int, ProcessMetrics> computeProcessMetrics();
};