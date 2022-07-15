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

	if(block_.IsCorner(start_point)) {
		std::cout << "corner ok\n";
		auto point_type = block_.GetPointType(start_point);
		int x_step = (point_type == DLCORNER || point_type == ULCORNER) ? 1 : -1;
		int y_step = (point_type == DLCORNER || point_type == DRCORNER) ? 1 : -1;;
		int x_start = (point_type == DLCORNER || point_type == ULCORNER) ? 0 : block_.Size().first - 1;
		int y_start = (point_type == DLCORNER || point_type == DRCORNER) ? 0 : block_.Size().second - 1;

		if(type_ == VERTICAL) {
			std::cout << "vertical ok\n";
			for(int x = x_start; x >= 0 && x < block_.Size().first; x += x_step) {
				for(int y = y_start; y >= 0 && y < block_.Size().second; y += y_step) {
					snake_path.push_back(block_.GetPoints()[x][y]);
				}
				y_start = block_.Size().second - 1 - y_start;
				y_step *= -1;
			}
		}
		else if(type_ == HORISONTAL) {
			std::cout << "horisontal ok\n";
			for(int y = y_start; y >= 0 && y < block_.Size().second; y += y_step) {
				for(int x = x_start; x >= 0 && x < block_.Size().first; x += x_step) {
					snake_path.push_back(block_.GetPoints()[x][y]);
				}
				x_start = block_.Size().first - 1 - x_start;
				x_step *= -1;
			}
		}
		else {
			std::cout << "snake error1\n";
		}
	}
	else {
		std::cout << "snake error2\n";
	}
	return snake_path;
}