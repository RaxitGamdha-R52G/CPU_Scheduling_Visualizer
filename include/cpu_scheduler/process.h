#pragma once

namespace cpu {

struct Process {
    int arrivalTime;   // Time at which the process arrives
    int burstTime;     // CPU burst duration
    int priority = 0;  // Lower value = higher priority
};

} // namespace cpu