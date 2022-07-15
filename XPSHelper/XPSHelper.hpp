#pragma once

#include <vector>
#include <map>

class XPSHelper {
public:
	XPSHelper(const char* XPSFilePath);

	int GetPointsCount() const;
	int GetPointNum(std::pair<int, int> coords) const;
	std::pair<int, int> GetPointCoords(int num) const;
	std::pair<int, int> GetOldCoords(int num) const;
	bool IsNeighbours(int lhs, int rhs) const;

private:
	std::vector<std::pair<int, int>> geometry_;
	std::vector<std::pair<int, int>> oldGeometry_;
	std::map<std::pair<int, int>, int> geomToNum_;
};