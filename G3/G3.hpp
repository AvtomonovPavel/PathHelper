#pragma once

#include <vector>
#include <map>

#include "../XPSHelper/XPSHelper.hpp"

class G3 {
public:
	G3(const XPSHelper& hlp, int k);
	const int GetK() const;
	const XPSHelper& GetXPSHelper() const;

private:
	
	const XPSHelper& xpsHlp_;
	const int K_;
};