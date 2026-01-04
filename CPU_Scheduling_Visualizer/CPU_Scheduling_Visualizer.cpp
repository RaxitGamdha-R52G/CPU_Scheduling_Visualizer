#include <iostream>
#include "api/SchedulerAPI.h"
#include "api/ProcessAPI.h"

int main()
{
	SchedulerAPI::initialize();

	ProcessAPI::addProcess(0, 5);
	ProcessAPI::addProcess(2, 3, 1);

	std::cout << "Processes registered successfully" << std::endl;
	return 0;
}
