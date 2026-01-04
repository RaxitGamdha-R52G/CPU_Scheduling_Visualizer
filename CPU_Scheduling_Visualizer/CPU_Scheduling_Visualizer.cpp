#include <iostream>
#include "api/SchedulerAPI.h"
#include "api/ProcessAPI.h"
#include "api/MetricsAPI.h"
#include "core/TimelineManager/TimelineManager.h"
#include "core/SchedulerEngine/FCFS/FCFSScheduler.h"
#include "visualization/TableFormatter/TableFormatter.h"

int main()
{
	SchedulerAPI::initialize();

	ProcessAPI::addProcess(8, 4);
	ProcessAPI::addProcess(2, 3);
	ProcessAPI::addProcess(6, 3);

	FCFSScheduler::run();

	TableFormatter::printProcessTable();
	return 0;
}
