// util.h
// Terrance Howard (heyterrance@gmail.com)

#ifndef UTIL_H
#define UTIL_H

#include <string> // std::string
#include <sstream> // std::stringstream
#include <locale> // std::toupper, std::tolower

// toupper(string), tolower(string)
std::string toupper(const std::string& str);
std::string tolower(const std::string& str);

// errprintf(fmt, ...)
// Print to stderr
void errprintf(const char* fmt, ...);

// dbprintf(fmt, ...)
// printf(fmt, ...) only when compiled with DEBUG
void dbprintf(const char *fmt, ...);

#endif
