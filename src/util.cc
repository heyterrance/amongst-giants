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

void dbprintf(const char *fmt, ...) {
#ifdef DEBUG
  char buffer[256];
  va_list args;
  va_start (args, fmt);
  vsprintf(buffer, fmt, args);
  printf("%s", buffer);
  va_end(args);
#endif
  if (fmt) return;
}
