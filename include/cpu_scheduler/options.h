#pragma once

namespace cpu {

struct SchedulerOptions {
    // Time quantum for Round Robin scheduling.
    // Ignored by other algorithms.
    int timeQuantum = 0;

    // Enable aging for priority-based scheduling.
    bool enableAging = false;

    // Number of time units after which aging is applied.
    int agingInterval = 5;

    // Priority improvement applied during aging.
    int agingStep = 1;
};

} // namespace cpu
