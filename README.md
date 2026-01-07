# CPU Scheduling Visualizer

A modular, API-first CPU scheduling simulator written in C++, designed for learning, experimentation, and future reuse as a library.

This project simulates classic and advanced CPU scheduling algorithms, computes detailed performance metrics, and visualizes execution using CLI-based tables and ASCII Gantt charts.

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
- Idle time visualization
- Supports preemptive and non-preemptive timelines

---

## 🏗️ Architecture Highlights

- **API-first design** with clear separation of concerns
- Core scheduling logic decoupled from visualization
- Timeline-driven execution model
- Extensible scheduler framework
- Optional policy configuration (e.g., aging)
- Designed to evolve into a reusable C++ library

---

## 🧑‍💻 Usage (Current)

The project currently runs via a comparison-style `main.cpp` that executes multiple scheduling algorithms on the same workload and prints:

- Process tables
- Performance metrics
- Gantt charts

This entry point is used for testing and demonstration purposes.  
A clean public library API is planned as the next development step.

---

## 📌 Status

✅ Core scheduling framework complete  
🚧 Refactoring in progress to expose a reusable C++ library interface
