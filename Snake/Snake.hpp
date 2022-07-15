#include "../Block/Block.hpp"
#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <set>

enum SnakeType {
	VERTICAL,
	HORISONTAL,
	NONETYPE
};

class Snake{
public:
	Snake(const Block& block, SnakeType type);
	std::vector<int> SnakeRun(int start_point);

private:
	SnakeType type_;
	const Block& block_;
};