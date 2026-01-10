#include <iostream>

#include <cpu_scheduler/scheduler.h>
#include <cpu_scheduler/process.h>
#include <cpu_scheduler/algorithm.h>
#include <cpu_scheduler/options.h>

int main() {
	using namespace cpu;

	Scheduler scheduler;

	// Add process (arrival, burst, priority)
	scheduler.addProcess({ 0, 8, 2 });
	scheduler.addProcess({ 1, 4, 1 });
	scheduler.addProcess({ 2, 9, 3 });
	scheduler.addProcess({ 3, 5, 0 });
	scheduler.addProcess({ 6, 2, 1 });

	std::cout << "\n=== FCFS ===\n";
	scheduler.run(Algorithm::FCFS);
	scheduler.result().printProcessTable();
	scheduler.result().printGanttChart();

    std::cout << "\n=== SJF ===\n";
    scheduler.run(Algorithm::SJF);
    scheduler.result().printProcessTable();
    scheduler.result().printGanttChart();

    std::cout << "\n=== SRTF ===\n";
    scheduler.run(Algorithm::SRTF);
    scheduler.result().printProcessTable();
    scheduler.result().printGanttChart();

    std::cout << "\n=== Priority (Non-Preemptive) ===\n";
    scheduler.run(Algorithm::Priority);
    scheduler.result().printProcessTable();
    scheduler.result().printGanttChart();

    std::cout << "\n=== Priority (Preemptive + Aging) ===\n";
    SchedulerOptions opt;
    opt.enableAging = true;
    opt.agingInterval = 2;

    scheduler.run(Algorithm::PriorityPreemptiveAging, opt);
    scheduler.result().printProcessTable();
    scheduler.result().printGanttChart();

    std::cout << "\n=== Round Robin (q=3) ===\n";
    SchedulerOptions rr;
    rr.timeQuantum = 3;

    scheduler.run(Algorithm::RoundRobin, rr);
    scheduler.result().printProcessTable();
    scheduler.result().printGanttChart();

    return 0;
}