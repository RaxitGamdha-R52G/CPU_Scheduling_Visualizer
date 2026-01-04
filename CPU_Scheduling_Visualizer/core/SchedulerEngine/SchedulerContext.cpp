#include "SchedulerContext.h"

TimeUnit SchedulerContext::currentTime = 0;

void SchedulerContext::reset() {
	currentTime = 0;
}

TimeUnit SchedulerContext::getCurrentTime() {
	return currentTime;
}

void SchedulerContext::advanceTime(TimeUnit delta) {
	currentTime += delta;
}