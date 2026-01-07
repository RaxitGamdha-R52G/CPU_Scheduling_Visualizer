#pragma once

namespace cpu {

struct SchedulerOptions {
    // Round Robin
    int timeQuantum = 0;

    // Priority scheduling
    bool enableAging = false;
    int agingInterval = 5;
    int agingStep = 1;
};

} // namespace cpu
