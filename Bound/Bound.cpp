#include "Bound.hpp"

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <set>
#include <windows.h>
#include <cmath>

Bound::Bound(bool type, int coord) :
	is_vertical_(type),
	coord_(coord) {}

bool Bound::IsVertical() const {
	return is_vertical_;
}

int Bound::GetCoordinate() const {
	return coord_;
}