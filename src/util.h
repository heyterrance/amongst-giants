// util.h
// Terrance Howard (heyterrance@gmail.com)

#ifndef UTIL_H
#define UTIL_H

#include <string> // std::string
#include <sstream> // std::stringstream
#include <locale> // std::toupper, std::tolower

std::string toupper(const std::string& str);
std::string tolower(const std::string& str);

// dbprintf(fmt, ...)
// printf(fmt, ...) only when compiled with DEBUG
void dbprintf(const char *fmt, ...);

#endif
