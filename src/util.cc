// util.cc
// Terrance Howard (heyterrance@gmail.com)

#include "util.h"

std::string toupper(const std::string& str) {
	std::stringstream ss;
	for (const char& c : str)
		ss << (char) std::toupper(c);
	return ss.str();
}

std::string tolower(const std::string& str) {
	std::stringstream ss;
	for (const char& c : str)
		ss << (char) std::tolower(c);
	return ss.str();
}
	
bool int3::operator<(const int3& a) const {
	if (x == a.x) {
		if (y == a.y)
			return z < a.z;
		return y < a.y;
	}
	return x < a.x;
}

bool float3::operator<(const float3& a) const {
	if (x == a.x) {
		if (y == a.y)
			return z < a.z;
		return y < a.y;
	}
	return x < a.x;
}
