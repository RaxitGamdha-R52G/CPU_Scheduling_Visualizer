#pragma once

#include<cstddef>
#include "../ProcessManager/ProcessControlBlock.h"

class SchedulerContext {
public:
	static void reset();

	static TimeUnit getCurrentTime();
	static void advanceTime(TimeUnit delta);

private:
	static TimeUnit currentTime;
};