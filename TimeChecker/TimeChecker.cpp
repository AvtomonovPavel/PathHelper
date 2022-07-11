#include "TimeChecker.hpp"

TimeChecker::TimeChecker() {
	start_ = std::chrono::steady_clock::now(); 
}

TimeChecker::~TimeChecker() {
	end_ = std::chrono::steady_clock::now();

	std::cout << "The time: " 
	          << std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_).count() 
	          << " ms\n";
}