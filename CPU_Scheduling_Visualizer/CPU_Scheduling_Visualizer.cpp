#include <iostream>
#include "api/SchedulerAPI.h"
#include "api/ProcessAPI.h"
#include "core/SchedulerEngine/FCFS/FCFSScheduler.h"
#include "visualization/TableFormatter/TableFormatter.h"
#include "visualization/GanttChartASCII/GanttChartASCII.h"

int main()
{
	SchedulerAPI::initialize();

	ProcessAPI::addProcess(8, 4);
	ProcessAPI::addProcess(2, 3);
	ProcessAPI::addProcess(6, 3);

	FCFSScheduler::run();

	TableFormatter::printProcessTable();

	GanttChartASCII::print();
	return 0;
}
