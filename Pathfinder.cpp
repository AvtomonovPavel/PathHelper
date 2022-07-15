#include <iostream>

#include "TimeChecker\TimeChecker.hpp"
#include "PathHelper\PathHelper.hpp"
#include "XPSHelper\XPSHelper.hpp"

int main(int argc, char* argv[]) {
	TimeChecker checkTime;
	XPSHelper xps(argv[1]);

	std::vector<std::vector<int>> block = {{0, 1, 2, 3, 4}, {32, 33, 34, 35, 36}, {64, 65, 66, 67, 68}};
	Block b(block, xps);

	std::cout << b.IsCorner(0)<<"\n";
	std::cout << b.GetPointType(0)<<"\n";



	return 0;
	Snake s(b, HORISONTAL);
	auto snake_p = s.SnakeRun(64);
	for(auto p : snake_p) {
		std::cout << p << " ";
	}

	return 0;
}