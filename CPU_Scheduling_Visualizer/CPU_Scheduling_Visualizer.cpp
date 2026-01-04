#include <iostream>
#include "api/SchedulerAPI.h"
#include "api/ProcessAPI.h"
#include "core/TimelineManager/TimelineManager.h"
#include "core/SchedulerEngine/FCFS/FCFSScheduler.h"
#include "api/MetricsAPI.h"

int main()
{
	SchedulerAPI::initialize();

	ProcessAPI::addProcess(8, 4);
	ProcessAPI::addProcess(2, 3);
	ProcessAPI::addProcess(6, 3);

	FCFSScheduler::run();

	for (const auto& entry : TimelineManager::getTimeline()) {
		std::cout << "PID " << entry.pid
			<< " : " << entry.startTime
			<< " -> " << entry.endTime
			<< std::endl;
	}

	std::cout << "Avg Waiting Time: " << MetricsAPI::averageWaitingTime() << "\n";

	std::cout << "Avg Turnaround Time: " << MetricsAPI::averageTurnaroundTime() << "\n";

	std::cout << "CPU Utilization: " << MetricsAPI::cpuUtilization() << "\n";

	std::cout << "Throughput: " << MetricsAPI::throughput() << "\n";
	return 0;
}
