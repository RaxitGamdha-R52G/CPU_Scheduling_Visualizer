#include <iostream>
#include "api/SchedulerAPI.h"
#include "api/ProcessAPI.h"
#include "core/TimelineManager/TimelineManager.h"

int main()
{
	SchedulerAPI::initialize();

	ProcessAPI::addProcess(0, 5);
	ProcessAPI::addProcess(2, 3, 1);

	std::cout << "Processes registered successfully" << std::endl;

	TimelineManager::addEntry(1, 0, 3);
	TimelineManager::addEntry(2, 3, 7);

	std::cout << "Timeline entries recorded" << std::endl;
	return 0;
}
