#pragma once

#include <iostream>
#include <chrono>

class TimeChecker {
public:
	TimeChecker();
	~TimeChecker();
private:
	std::chrono::time_point<std::chrono::steady_clock> start_;
	std::chrono::time_point<std::chrono::steady_clock> end_;
};