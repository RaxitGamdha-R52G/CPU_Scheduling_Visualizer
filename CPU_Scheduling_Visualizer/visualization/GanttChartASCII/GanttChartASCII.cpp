#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "GanttChartASCII.h"
#include "../../core/TimelineManager/TimelineManager.h"

namespace {
    // Fixed width for each gantt block
    constexpr int BLOCK_WIDTH = 6;

    // Helper to center text inside a fixed-width block
    std::string centerText(const std::string& text, int width) {
        if ((int)text.size() >= width) {
            return text.substr(0, width);
        }

        int totalPadding = width - static_cast<int>(text.size());
        int leftPadding = totalPadding / 2;
        int rightPadding = totalPadding - leftPadding;

        return std::string(leftPadding, ' ') +
            text +
            std::string(rightPadding, ' ');
    }
}

void GanttChartASCII::print() {
    const auto& timeline = TimelineManager::getTimeline();

    if (timeline.empty()) {
        std::cout << "Gantt Chart: <empty>\n";
        return;
    }

    std::vector<std::string> labels;
    std::vector<int> times;

    int currentTime = 0;

    // Build labels and time markers (timeline is the source of truth)
    for (const auto& entry : timeline) {
        // Handle idle time
        if (currentTime < entry.startTime) {
            labels.push_back("IDLE");
            times.push_back(currentTime);
            currentTime = entry.startTime;
        }

        labels.push_back("P" + std::to_string(entry.pid));
        times.push_back(entry.startTime);
        currentTime = entry.endTime;
    }

    // Final time marker
    times.push_back(currentTime);

    // -------- Print Gantt Chart --------
    std::cout << "\nGantt Chart:\n";

    // Calculate total width for horizontal borders
    int totalWidth = (BLOCK_WIDTH + 1) * static_cast<int>(labels.size()) + 1;

    // Top horizontal line
    std::cout << "+";
    for (int i = 0; i < labels.size(); ++i) {
        std::cout << std::string(BLOCK_WIDTH, '-') << "+";
    }
    std::cout << "\n";

    // Gantt blocks row
    for (const auto& label : labels) {
        std::cout << "|" << centerText(label, BLOCK_WIDTH);
    }
    std::cout << "|\n";

    // Separator line under blocks
    std::cout << "+";
    for (int i = 0; i < labels.size(); ++i) {
        std::cout << std::string(BLOCK_WIDTH, '-') << "+";
    }
    std::cout << "\n";

    // Tick row (visual alignment for time markers)
    for (size_t i = 0; i < labels.size(); ++i) {
        std::cout << "|" << std::string(BLOCK_WIDTH, ' ');
    }
    std::cout << "|\n";

    // Print time markers aligned with block boundaries
    for (int t : times) {
        std::cout << std::left << std::setw(BLOCK_WIDTH + 1) << t;
    }
    std::cout << "\n";
}
