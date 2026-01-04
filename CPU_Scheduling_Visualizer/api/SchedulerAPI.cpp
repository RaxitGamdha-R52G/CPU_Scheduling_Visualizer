#include "SchedulerAPI.h"
#include "../core/SchedulerEngine/SchedulerContext.h"
#include "../core/ProcessManager/ProcessManager.h"

void SchedulerAPI::initialize() {
	SchedulerContext::reset();
	ProcessManager::reset();
}