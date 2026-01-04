#pragma once

using TimeUnit = int;

enum class ProcessState {
	NEW,
	READY,
	RUNNING,
	TERMINATED
};

struct ProcessControlBlock {
	int pid;					// Unique process ID
	TimeUnit arrivalTime;		// When process arrives
	TimeUnit burstTime;			// Total CPU time required
	int priority;				// Lower value = higher priority

	// Runtime fields
	TimeUnit remainingTime;
	ProcessState state;

	ProcessControlBlock(
		int pid_,
		TimeUnit arrival_,
		TimeUnit burst_,
		int priority_ = 0
	)
		: pid(pid_),
		arrivalTime(arrival_),
		burstTime(burst_),
		priority(priority_),
		remainingTime(burst_),
		state(ProcessState::NEW)
	{}
};

