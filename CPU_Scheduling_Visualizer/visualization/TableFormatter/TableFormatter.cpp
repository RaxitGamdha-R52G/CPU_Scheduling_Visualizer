#include "TableFormatter.h"

#include <iostream>
#include <iomanip>

#include "../../core/ProcessManager/ProcessManager.h"
#include "../../api/MetricsAPI.h"
#include "../../utils/TimeCalculator.h"

void TableFormatter::printProcessTable() {
    const auto& processes = ProcessManager::getAllProcesses();
    auto metrics = TimeCalculator::computeProcessMetrics();

    std::cout << "+-----+-----+-----+-----+-----+-----+-----+\n";
    std::cout << "| PID | AT  | BT  | ST  | CT  | WT  | TAT |\n";
    std::cout << "+-----+-----+-----+-----+-----+-----+-----+\n";

    for (const auto& pcb : processes) {
        const auto& m = metrics[pcb.pid];

        std::cout << "| "
            << std::setw(3) << pcb.pid << " | "
            << std::setw(3) << pcb.arrivalTime << " | "
            << std::setw(3) << pcb.burstTime << " | "
            << std::setw(3) << m.startTime << " | "
            << std::setw(3) << m.completionTime << " | "
            << std::setw(3) << m.waitingTime << " | "
            << std::setw(3) << m.turnaroundTime << " |\n";
    }

    std::cout << "+-----+-----+-----+-----+-----+-----+-----+\n\n";

    std::cout << "Average Waiting Time    : "
        << MetricsAPI::averageWaitingTime() << "\n";

    std::cout << "Average Turnaround Time : "
        << MetricsAPI::averageTurnaroundTime() << "\n";

    std::cout << "CPU Utilization         : "
        << MetricsAPI::cpuUtilization() << "\n";

    std::cout << "Throughput              : "
        << MetricsAPI::throughput() << "\n";
}
