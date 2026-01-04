#include "SchedulerAPI.h"
#include "../core/SchedulerEngine/SchedulerContext.h"
#include "../core/ProcessManager/ProcessManager.h"
#include "../core/TimelineManager/TimelineManager.h"

void SchedulerAPI::initialize() {
	SchedulerContext::reset();
	ProcessManager::reset();
	TimelineManager::reset();
}