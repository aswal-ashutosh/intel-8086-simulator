#pragma once
#include<chrono>

class TimeManager
{
	static const std::chrono::milliseconds MAX_EXPECTED_TIME; //in milliseconds
	static std::chrono::steady_clock::time_point start;
public:
	static void Reset();
	static bool TLE();
};

std::chrono::steady_clock::time_point TimeManager::start;
const std::chrono::milliseconds TimeManager::MAX_EXPECTED_TIME(3000);

void TimeManager::Reset()
{
	start = std::chrono::high_resolution_clock::now();
}

bool TimeManager::TLE()
{
	std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	return duration > MAX_EXPECTED_TIME;
}
