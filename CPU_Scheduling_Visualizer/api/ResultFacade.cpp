#include "cpu_scheduler/result.h"

#include "MetricsAPI.h"
#include "../visualization/TableFormatter/TableFormatter.h"
#include "../visualization/GanttChartASCII/GanttChartASCII.h"

namespace cpu {

    struct Result::Impl {};

    void Result::printProcessTable() const {
        TableFormatter::printProcessTable();
    }

    void Result::printGanttChart() const {
        GanttChartASCII::print();
    }

    double Result::averageWaitingTime() const {
        return MetricsAPI::averageWaitingTime();
    }

    double Result::averageTurnaroundTime() const {
        return MetricsAPI::averageTurnaroundTime();
    }

    double Result::cpuUtilization() const {
        return MetricsAPI::cpuUtilization();
    }

    double Result::throughput() const {
        return MetricsAPI::throughput();
    }

} // namespace cpu