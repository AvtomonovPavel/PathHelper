#include "../XPSHelper/XPSHelper.hpp"
#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <set>

enum PointType {
	URCORNER,
	ULCORNER,
	DRCORNER,
	DLCORNER,
	EXTPOINT,
	INTPOINT
};

class Block{
public:
	Block(const std::vector<std::vector<int>>& points, const XPSHelper& xps_);

	const std::vector<std::vector<int>>& GetPoints() const;
	std::pair<int, int> Size() const;
	PointType GetPointType(int point_num) const;
	bool IsCorner(int point_num) const;
	int GetUpperBound() const;
	int GetLowerBound() const;
	int GetLeftBound() const;
	int GetRightBound() const;

private:
	std::vector<std::vector<int>> points_;
	const XPSHelper& xps_;
};