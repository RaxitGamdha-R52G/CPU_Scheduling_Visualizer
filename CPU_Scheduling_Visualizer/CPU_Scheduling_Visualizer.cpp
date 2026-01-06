#include <iostream>
#include "api/SchedulerAPI.h"
#include "api/ProcessAPI.h"
#include "core/SchedulerEngine/FCFS/FCFSScheduler.h"
#include "core/SchedulerEngine/SJF/SJFScheduler.h"
#include "visualization/TableFormatter/TableFormatter.h"
#include "visualization/GanttChartASCII/GanttChartASCII.h"

int main()
{
	// FCFS
	SchedulerAPI::initialize();

	ProcessAPI::addProcess(0, 8);
	ProcessAPI::addProcess(1, 4);
	ProcessAPI::addProcess(2, 9);
	ProcessAPI::addProcess(3, 5);
	ProcessAPI::addProcess(6, 2);

	FCFSScheduler::run();

	TableFormatter::printProcessTable();
	GanttChartASCII::print();

	// SJF non-preemptive
	SchedulerAPI::initialize();

	ProcessAPI::addProcess(0, 8);
	ProcessAPI::addProcess(1, 4);
	ProcessAPI::addProcess(2, 9);
	ProcessAPI::addProcess(3, 5);
	ProcessAPI::addProcess(6, 2);

	SJFScheduler::run();

	TableFormatter::printProcessTable();
	GanttChartASCII::print();

	return 0;
}
