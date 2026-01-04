#pragma once

class MetricsAPI {
public:
	static double averageWaitingTime();
	static double averageTurnaroundTime();
	static double cpuUtilization();
	static double throughput();
};