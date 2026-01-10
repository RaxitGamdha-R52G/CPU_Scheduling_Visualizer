#pragma once

namespace cpu {

class Result {
public:
    // Printing helpers (CLI)
    void printProcessTable() const;     // Prints a formatted process table to stdout.
    void printGanttChart() const;       // Prints an ASCII Gantt chart to stdout.

    // Aggregate metrics
    double averageWaitingTime() const;
    double averageTurnaroundTime() const;
    double cpuUtilization() const;
    double throughput() const;

private:
    // Result objects are owned and managed by Scheduler.
    struct Impl;
    Impl* impl = nullptr;

    // Only Scheduler can create Result.
    friend class Scheduler;
};

} // namespace cpu
