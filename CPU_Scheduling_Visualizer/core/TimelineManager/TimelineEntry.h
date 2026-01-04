#pragma once

#include "../ProcessManager/ProcessControlBlock.h"

struct TimelineEntry {
	int pid;				// Process ID
	TimeUnit startTime;		// Inclusive
	TimeUnit endTime;		// Exclusive

	TimelineEntry(
		int pid_,
		TimeUnit startTime_,
		TimeUnit endTime_
	)
		: pid(pid_),
		startTime(startTime_),
		endTime(endTime_)
	{}
};