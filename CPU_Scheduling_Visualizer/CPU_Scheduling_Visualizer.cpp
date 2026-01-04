#include <iostream>
#include "api/SchedulerAPI.h"

int main()
{
    SchedulerAPI::initialize();
    std::cout << "CPU Scheduling Visualizer - Scheduler Initialized" << std::endl;
}
