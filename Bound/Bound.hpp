#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <set>

class Bound{
public:
	Bound(bool type, int coord);
	bool IsVertical() const;
	int GetCoordinate() const;

private:
	bool is_vertical_;
	int coord_;
};