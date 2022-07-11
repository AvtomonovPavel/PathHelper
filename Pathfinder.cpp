#include <iostream>

#include "TimeChecker\TimeChecker.hpp"
#include "PathHelper\PathHelper.hpp"
#include "XPSHelper\XPSHelper.hpp"

int main(int argc, char* argv[]) {
	TimeChecker checkTime;
	XPSHelper xps(argv[1]);

	std::ofstream out("vis.txt", std::ios::out);
	std::ofstream out_new("x_way.txt", std::ios::out);
	PathHelper ph(xps);

	//out << g3.GetXPSHelper().GetWellCount() << "\n";
	//for (int i = 0; i < g3.GetXPSHelper().GetWellCount(); ++i)
	//	out << g3.GetXPSHelper().GetWellCoords(i).first << " " << g3.GetXPSHelper().GetWellCoords(i).second << "\n";
	//out << "\n";
	//ph.FindPath(std::vector<int>{4120, 4121, 4122, 4123, 4124, 4125, 4126, 4127, 4128, 4129});
	//ph.Optimize();

	//ph.WritePath(out);
	ph.WriteXPSPath();
	out.close();

	return 0;
}