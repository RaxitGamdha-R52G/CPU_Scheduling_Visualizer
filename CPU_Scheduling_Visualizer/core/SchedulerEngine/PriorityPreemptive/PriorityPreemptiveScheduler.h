#pragma once

#include <cstdint>

struct PriorityPreemptiveOptions {
    bool enableAging = false;
    int agingStep = 1;              // priority improvement
    int agingInterval = 5;          // time units
};

class PriorityPreemptiveScheduler {
public:
    static void run(const PriorityPreemptiveOptions& options);
};