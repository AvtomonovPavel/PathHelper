#include "Block.hpp"

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <set>
#include <windows.h>
#include <cmath>

Block::Block(const std::vector<std::vector<int>>& points, const XPSHelper& xps_) : points_(points), xps_(xps_) {
	std::cout << "block constructor ok\n";
}

const std::vector<std::vector<int>>& Block::GetPoints() const {
	return points_;
}

std::pair<int, int> Block::Size() const {
	if(points_.empty()) {
		return {0, 0};
	}
	return  {points_.size(), points_[0].size()};
}

int Block::GetUpperBound() const {
	if(Size() == std::make_pair(0, 0)) {
		return -1;
	}
	for(int i = 0; i < Size().first; ++i) {
		if(points_[i][Size().second - 1] != -1) {
			return xps_.GetPointCoords(points_[i][Size().second - 1]).second;
		}
	}
	return -1;
}

int Block::GetLowerBound() const {
	if(Size() == std::make_pair(0, 0)) {
		return -1;
	}
	for(int i = 0; i < Size().first; ++i) {
		if(points_[i][0] != -1) {
			return xps_.GetPointCoords(points_[i][0]).second;
		}
	}
	return -1;
}

int Block::GetLeftBound() const {
	if(Size() == std::make_pair(0, 0)) {
		return -1;
	}
	for(int i = 0; i < Size().second; ++i) {
		if(points_[0][i] != -1) {
			return xps_.GetPointCoords(points_[0][i]).first;
		}
	}
	return -1;
}

int Block::GetRightBound() const {
	if(Size() == std::make_pair(0, 0)) {
		return -1;
	}
	for(int i = 0; i < Size().second; ++i) {
		if(points_[Size().first - 1][i] != -1) {
			return xps_.GetPointCoords(points_[Size().first - 1][i]).first;
		}
	}
	return -1;
}

PointType Block::GetPointType(int point_num) const {
	if(Size() == std::make_pair(0, 0)) {
		return EXTPOINT;
	}
	else if(xps_.GetPointCoords(point_num).first == GetLeftBound() &&
		xps_.GetPointCoords(point_num).second == GetLowerBound()) {
		return DLCORNER;
	}
	else if(xps_.GetPointCoords(point_num).first == GetRightBound() &&
		xps_.GetPointCoords(point_num).second == GetLowerBound()) {
		return DRCORNER;
	}
	else if(xps_.GetPointCoords(point_num).first == GetLeftBound() &&
		xps_.GetPointCoords(point_num).second == GetUpperBound()) {
		return ULCORNER;
	}
	else if(xps_.GetPointCoords(point_num).first == GetRightBound() &&
		xps_.GetPointCoords(point_num).second == GetUpperBound()) {
		return URCORNER;
	}
	else if(xps_.GetPointCoords(point_num).first < GetLeftBound() ||
		xps_.GetPointCoords(point_num).first > GetRightBound() || 
		xps_.GetPointCoords(point_num).second > GetUpperBound() ||
		xps_.GetPointCoords(point_num).second < GetLowerBound()) {
		return EXTPOINT;
	}
	return INTPOINT;
}

bool Block::IsCorner(int point_num) const {
	PointType type = GetPointType(point_num);
	//std::cout << "type "<< type << "\n";
	return type == ULCORNER || type == URCORNER || type == DLCORNER || type == DRCORNER;
}