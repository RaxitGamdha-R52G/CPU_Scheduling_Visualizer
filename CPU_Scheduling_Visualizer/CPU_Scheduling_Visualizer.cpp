#include <iostream>

#include "api/SchedulerAPI.h"
#include "api/ProcessAPI.h"

#include "core/SchedulerEngine/FCFS/FCFSScheduler.h"
#include "core/SchedulerEngine/SJF/SJFScheduler.h"
#include "core/SchedulerEngine/Priority/PriorityScheduler.h"
#include "core/SchedulerEngine/RoundRobin/RoundRobinScheduler.h"
#include "core/SchedulerEngine/SRTF/SRTFScheduler.h"
#include "core/SchedulerEngine/PriorityPreemptive/PriorityPreemptiveScheduler.h"

#include "visualization/TableFormatter/TableFormatter.h"
#include "visualization/GanttChartASCII/GanttChartASCII.h"

int main()
{
    // FCFS
    std::cout << "\n=== FCFS Scheduling ===\n";

    SchedulerAPI::initialize();

    ProcessAPI::addProcess(0, 8);
    ProcessAPI::addProcess(1, 4);
    ProcessAPI::addProcess(2, 9);
    ProcessAPI::addProcess(3, 5);
    ProcessAPI::addProcess(6, 2);

    FCFSScheduler::run();

    TableFormatter::printProcessTable();
    GanttChartASCII::print();


    // SJF (Non-Preemptive)

    std::cout << "\n=== SJF Scheduling (Non-Preemptive) ===\n";

    SchedulerAPI::initialize();

    ProcessAPI::addProcess(0, 8);
    ProcessAPI::addProcess(1, 4);
    ProcessAPI::addProcess(2, 9);
    ProcessAPI::addProcess(3, 5);
    ProcessAPI::addProcess(6, 2);

    SJFScheduler::run();

    TableFormatter::printProcessTable();
    GanttChartASCII::print();


    // Priority Scheduling (Non-Preemptive)

    std::cout << "\n=== Priority Scheduling (Non-Preemptive) ===\n";

    SchedulerAPI::initialize();

    ProcessAPI::addProcess(0, 8, 2);
    ProcessAPI::addProcess(1, 4, 1);
    ProcessAPI::addProcess(2, 9, 3);
    ProcessAPI::addProcess(3, 5, 0);
    ProcessAPI::addProcess(6, 2, 1);

    PriorityScheduler::run();

    TableFormatter::printProcessTable();
    GanttChartASCII::print();

    // Round Robin

    std::cout << "\n=== Round Robin Scheduling ===\n";

    SchedulerAPI::initialize();

    ProcessAPI::addProcess(0, 8);
    ProcessAPI::addProcess(1, 4);
    ProcessAPI::addProcess(2, 9);
    ProcessAPI::addProcess(3, 5);
    ProcessAPI::addProcess(6, 2);

    RoundRobinScheduler::run(3);

    TableFormatter::printProcessTable();
    GanttChartASCII::print();

    // SRTF (SJF preemptive)
    std::cout << "\n=== SRTF Scheduling ===\n";

    SchedulerAPI::initialize();

    ProcessAPI::addProcess(0, 8);
    ProcessAPI::addProcess(1, 4);
    ProcessAPI::addProcess(2, 9);
    ProcessAPI::addProcess(3, 5);
    ProcessAPI::addProcess(6, 2);

    SRTFScheduler::run();

    TableFormatter::printProcessTable();
    GanttChartASCII::print();

    // Preemptive Priority Scheduling (NO Aging)
    std::cout << "\n=== Preemptive Priority Scheduling (No Aging) ===\n";

    SchedulerAPI::initialize();

    ProcessAPI::addProcess(0, 8, 2);
    ProcessAPI::addProcess(1, 4, 1);
    ProcessAPI::addProcess(2, 9, 3);
    ProcessAPI::addProcess(3, 5, 0);
    ProcessAPI::addProcess(6, 2, 1);

    PriorityPreemptiveOptions noAging;
    noAging.enableAging = false;

    PriorityPreemptiveScheduler::run(noAging);

    TableFormatter::printProcessTable();
    GanttChartASCII::print();

    // Preemptive Priority Scheduling (WITH Aging)
    std::cout << "\n=== Preemptive Priority Scheduling (With Aging) ===\n";

    SchedulerAPI::initialize();

    ProcessAPI::addProcess(0, 8, 2);
    ProcessAPI::addProcess(1, 4, 1);
    ProcessAPI::addProcess(2, 9, 3);
    ProcessAPI::addProcess(3, 5, 0);
    ProcessAPI::addProcess(6, 2, 1);

    PriorityPreemptiveOptions withAging;
    withAging.enableAging = true;
    withAging.agingInterval = 5;
    withAging.agingStep = 1;

    PriorityPreemptiveScheduler::run(withAging);

    TableFormatter::printProcessTable();
    GanttChartASCII::print();

    return 0;
}
