#pragma once

namespace cpu {

enum class Algorithm {
    FCFS,
    SJF,
    SRTF,
    Priority,
    PriorityPreemptive,
    PriorityPreemptiveAging,
    RoundRobin
};

} // namespace cpu
