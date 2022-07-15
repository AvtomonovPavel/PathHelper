#include "../Board/Board.hpp"
#include "../Snake/Snake.hpp"
#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <set>

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	RANDOM
};

class PathHelper {
public:

private:
	std::vector<int> path_;
};