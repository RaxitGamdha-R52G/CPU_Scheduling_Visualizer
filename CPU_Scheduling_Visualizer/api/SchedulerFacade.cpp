#include "cpu_scheduler/scheduler.h"

#include "SchedulerAPI.h"
#include "ProcessAPI.h"
#include "MetricsAPI.h"

#include "../core/SchedulerEngine/FCFS/FCFSScheduler.h"
#include "../core/SchedulerEngine/SJF/SJFScheduler.h"
#include "../core/SchedulerEngine/SRTF/SRTFScheduler.h"
#include "../core/SchedulerEngine/Priority/PriorityScheduler.h"
#include "../core/SchedulerEngine/PriorityPreemptive/PriorityPreemptiveScheduler.h"
#include "../core/SchedulerEngine/RoundRobin/RoundRobinScheduler.h"

#include "../core/SchedulerEngine/SchedulerContext.h"
#include "../core/TimelineManager/TimelineManager.h"

#include <memory>

namespace cpu {

    // ---------------- Impl ----------------
    struct Scheduler::Impl {
        Result result;
    };

    // ---------------- Constructor ----------------
    Scheduler::Scheduler()
        : impl(new Impl()) {
        // Initialize ONCE per scheduler instance
        SchedulerAPI::initialize();
    }

    // ---------------- Process Management ----------------
    void Scheduler::addProcess(const Process& p) {
        ProcessAPI::addProcess(
            p.arrivalTime,
            p.burstTime,
            p.priority
        );
    }

    void Scheduler::clearProcesses() {
        // Explicit full reset (user intent)
        SchedulerAPI::initialize();
    }

    // ---------------- Internal run reset ----------------
    static void resetForRun() {
        TimelineManager::reset();
        SchedulerContext::reset();
    }

    // ---------------- Run Dispatcher ----------------
    void Scheduler::run(Algorithm algorithm,
        const SchedulerOptions& options) {
        // Reset execution artifacts ONLY
        resetForRun();

        switch (algorithm) {
        case Algorithm::FCFS:
            FCFSScheduler::run();
            break;

        case Algorithm::SJF:
            SJFScheduler::run();
            break;

        case Algorithm::SRTF:
            SRTFScheduler::run();
            break;

        case Algorithm::Priority:
            PriorityScheduler::run();
            break;

        case Algorithm::PriorityPreemptive:
        case Algorithm::PriorityPreemptiveAging: {
            PriorityPreemptiveOptions opt;
            opt.enableAging =
                (algorithm == Algorithm::PriorityPreemptiveAging);
            opt.agingInterval = options.agingInterval;
            opt.agingStep = options.agingStep;

            PriorityPreemptiveScheduler::run(opt);
            break;
        }

        case Algorithm::RoundRobin:
            RoundRobinScheduler::run(options.timeQuantum);
            break;
        }
    }

    // ---------------- Result Access ----------------
    const Result& Scheduler::result() const {
        return impl->result;
    }

} // namespace cpu