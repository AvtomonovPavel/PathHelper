#include "Snake.hpp"

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <set>
#include <windows.h>
#include <cmath>

Snake::Snake(const Block& block, SnakeType type) : 
	block_(block), 
	type_(type) {}

std::vector<int> Snake::SnakeRun(int start_point) {
	std::vector<int> snake_path;

	if(block_.IsCorner(start_point) || type_ == NONETYPE) {
		std::cout << "corner ok\n";
		auto point_type = block_.GetPointType(start_point);

		int main_step = (point_type == DLCORNER || point_type == DRCORNER && type_ == VERTICAL ||
			point_type == ULCORNER && type_ == HORISONTAL) ? 1 : -1;
		int side_step = (point_type == DLCORNER || point_type == DRCORNER && type_ == HORISONTAL ||
			point_type == ULCORNER && type_ == VERTICAL) ? 1 : -1;

		int x_start = (point_type == DLCORNER || point_type == ULCORNER) ? 0 : block_.Size().first - 1;
		int y_start = (point_type == DLCORNER || point_type == DRCORNER) ? 0 : block_.Size().second - 1;
		int main_start = (type_ == VERTICAL) ? y_start : x_start;
		int side_start = (type_ == VERTICAL) ? x_start : y_start;

		int main_limit = (type_ == VERTICAL) ? block_.Size().second : block_.Size().first;
		int side_limit = (type_ == VERTICAL) ? block_.Size().first : block_.Size().second;

		for(int side_coord = side_start; side_coord >= 0 && side_coord < side_limit; side_coord += side_step) {
			for(int main_coord = main_start; main_coord >= 0 && main_coord < main_limit; main_coord += main_step) {
				snake_path.push_back(block_.GetPoints()[(type_ == VERTICAL) ? 
					side_coord : main_coord][(type_ == VERTICAL) ? main_coord : side_coord]);
			}
			main_start = main_limit - 1 - main_start;
			main_step *= -1;
		}
	}
	else {
		std::cout << "snake error\n";
	}
	return snake_path;
}