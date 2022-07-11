#include <iostream>

#include "TimeChecker\TimeChecker.hpp"
#include "PathHelper\PathHelper.hpp"
#include "XPSHelper\XPSHelper.hpp"

int main(int argc, char* argv[]) {
	TimeChecker checkTime;
	
	XPSHelper xps(argv[1]);

	PathHelper ph(xps, 40);
	ph.WriteXPSPath();

	return 0;
}