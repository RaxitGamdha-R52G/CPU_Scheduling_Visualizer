#include "ProcessAPI.h"
#include "../core/ProcessManager/ProcessManager.h"
#include <stdexcept>


int ProcessAPI::addProcess(
	int arrivalTime,
	int burstTime,
	int priority
) {
	if (arrivalTime < 0) throw std::invalid_argument("Arrival time must be >= 0");

	if (burstTime <= 0) throw std::invalid_argument("Burst time must be > 0");

	return ProcessManager::registerProcess(
		arrivalTime,
		burstTime,
		priority
	);
}