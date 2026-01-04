#pragma once

class ProcessAPI {
public:
	static int addProcess(
		int arrivalTime,
		int burstTime,
		int priority = 0
	);
};