// util.h
// Terrance Howard (heyterrance@gmail.com)

#ifndef UTIL_H
#define UTIL_H

#include <string> // std::string
#include <sstream> // std::stringstream
#include <locale> // std::toupper, std::tolower

std::string toupper(const std::string& str);
std::string tolower(const std::string& str);

struct int3 {
	int x, y, z;
	int3(int i, int j, int k) : x(i), y(j), z(k) { }

	bool operator<(const int3& a) const;
};

struct float3 {
	float x, y, z;
	float3(float i, float j, float k) : x(i), y(j), z(k) { }

	bool operator<(const float3& a) const;
};

#endif
