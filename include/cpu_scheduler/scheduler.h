#pragma once

#include <vector>
#include "process.h"
#include "algorithm.h"
#include "options.h"
#include "result.h"

namespace cpu {

class Scheduler {
public:
    // Constructs a new scheduler instance.
    Scheduler();                                // Each instance maintains its own process set and execution timeline.

    // Process management
    void addProcess(const Process& process);    // Adds a process to the scheduler.
    void clearProcesses();                      // Clears all registered processes and internal state.

    // Run scheduling
    void run(Algorithm algorithm, const SchedulerOptions& options = {});

    // Access results of most recent run.
    const Result& result() const;

private:
    struct Impl;
    Impl* impl;
};

} // namespace cpu
