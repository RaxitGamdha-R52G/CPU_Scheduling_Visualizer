#pragma once

#include <vector>
#include "process.h"
#include "algorithm.h"
#include "options.h"
#include "result.h"

namespace cpu {

class Scheduler {
public:
    Scheduler();

    // Process management
    void addProcess(const Process& process);
    void clearProcesses();

    // Run scheduling
    void run(Algorithm algorithm,
             const SchedulerOptions& options = {});

    // Access results
    const Result& result() const;

private:
    // Hidden implementation
    struct Impl;
    Impl* impl;
};

} // namespace cpu
