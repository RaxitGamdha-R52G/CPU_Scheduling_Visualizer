#pragma once

#include <vector>
#include "ProcessControlBlock.h"

class ProcessManager {
public:
	static void reset();

	static int registerProcess(
		TimeUnit arrivalTime,
		TimeUnit burstTime,
		int priority
	);

	static const std::vector<ProcessControlBlock>& getAllProcesses();

private:
	static std::vector<ProcessControlBlock> processes;
	static int nextPid;
};