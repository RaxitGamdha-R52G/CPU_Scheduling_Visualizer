# CPU Scheduling Visualizer

A **modular, API-first CPU scheduling library** written in C++, designed for learning operating system concepts, experimenting with scheduling policies, and reuse as a standalone C++ library.

The project simulates classic and advanced CPU scheduling algorithms, computes detailed performance metrics, and visualizes execution using CLI-based tables and ASCII Gantt charts. It is structured to cleanly separate **core scheduling logic**, **public APIs**, and **visualization**, making future extensions straightforward.

---

## ✨ Key Features

### 🧠 Scheduling Algorithms

- First Come First Serve (FCFS)
- Shortest Job First (SJF) – Non-preemptive
- Shortest Remaining Time First (SRTF) – Preemptive SJF
- Priority Scheduling – Non-preemptive
- Priority Scheduling – Preemptive
- Priority Scheduling with optional Aging
- Round Robin (configurable time quantum)

---

### 📊 Performance Metrics

- Start Time
- Completion Time
- Waiting Time
- Turnaround Time
- Response Time
- Average Waiting Time
- Average Turnaround Time
- CPU Utilization
- Throughput

---

### 📈 Visualization (CLI)

- Structured process table output
- ASCII-based Gantt chart
- Explicit idle-time visualization
- Supports both preemptive and non-preemptive timelines

---

## 🏗️ Architecture Overview

The project is organized as a **static C++ library** with a clear public interface and an internal implementation.

### High-level structure

```
include/                     # Public API headers (library interface)
  cpu_scheduler/
    algorithm.h
    scheduler.h
    process.h
    options.h
    result.h

CPU_Scheduling_Visualizer/   # Library implementation
  api/                        # Internal APIs and facades
  core/                       # Scheduling engines and core logic
  visualization/              # CLI table and Gantt chart rendering
  utils/                      # Shared utilities

cpu_scheduler_example/       # Example consumer application
examples/                    # Example source files
```

### Design principles

- **API-first design**: consumers interact only via headers in `include/`
- **Separation of concerns**: scheduling logic, metrics, and visualization are decoupled
- **Timeline-driven execution**: all algorithms produce a unified execution timeline
- **Extensibility**: new algorithms or visualizations can be added without rewriting core logic

---

## 🧑‍💻 Using the Library

A consumer project only needs:

1. The compiled static library (`CPU_Scheduling_Visualizer.lib`)
2. The public headers under `include/`

### Minimal example

```cpp
#include <cpu_scheduler/scheduler.h>
#include <cpu_scheduler/process.h>

using namespace cpu;

int main() {
    Scheduler scheduler;

    scheduler.addProcess({0, 8, 2});
    scheduler.addProcess({1, 4, 1});
    scheduler.addProcess({3, 5, 0});

    scheduler.run(Algorithm::PriorityPreemptive);

    const Result& result = scheduler.result();
    result.printProcessTable();
    result.printGanttChart();
}
```

The example project in this repository demonstrates how to link against the library using Visual Studio.

---

## 🧪 Example Application

The `cpu_scheduler_example` project is a standalone executable that:

- Links against the static library
- Uses only the public API
- Serves as a reference for consumers

It is **not** required for using the library and can be excluded in downstream projects.

---

## 🚧 Project Status & Roadmap

### Current status

- ✅ Core scheduling framework complete
- ✅ Static library build
- ✅ Public API exposed
- ✅ Example consumer project

### Planned next steps

- CMake-based cross-platform build system
- Interactive CLI (menu-driven scheduler)
- Comparative algorithm analysis mode
- Unit and regression tests
- Additional scheduling algorithms (e.g., MLFQ, EDF)
