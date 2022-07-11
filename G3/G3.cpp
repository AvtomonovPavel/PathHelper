#include "G3.hpp"

#include <set>
#include <iostream>

G3::G3(const XPSHelper& hlp, int k) :
	xpsHlp_(hlp),
	K_(k)
{}

const int G3::GetK() const {
	return K_;
}

const XPSHelper& G3::GetXPSHelper() const {
	return xpsHlp_;
}
