#include "ProcessManager.h"

std::vector<ProcessControlBlock> ProcessManager::processes;
int ProcessManager::nextPid = 1;

void ProcessManager::reset() {
	processes.clear();
	nextPid = 1;
}

int ProcessManager::registerProcess(
	TimeUnit arrivalTime,
	TimeUnit burstTime,
	int priority
) {
	ProcessControlBlock pcb(
		nextPid,
		arrivalTime,
		burstTime,
		priority
	);

	processes.push_back(pcb);
	return nextPid++;
}

const std::vector<ProcessControlBlock>& ProcessManager::getAllProcesses() {
	return processes;
}