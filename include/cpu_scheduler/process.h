#pragma once

namespace cpu {

struct Process {
    int arrivalTime;
    int burstTime;
    int priority = 0;
};

} // namespace cpu
