#pragma once

namespace cpu {

class Result {
public:
    // Printing helpers (CLI)
    void printProcessTable() const;
    void printGanttChart() const;

    // Aggregate metrics
    double averageWaitingTime() const;
    double averageTurnaroundTime() const;
    double cpuUtilization() const;
    double throughput() const;

private:
    // Implementation hidden (defined in cpp later)
    struct Impl;
    Impl* impl = nullptr;

    // Only Scheduler can create Result
    friend class Scheduler;
};

} // namespace cpu
