#pragma once

#include <stdexcept>
#include <string>
#include <vector>

namespace akame {
namespace utilities {
namespace pystrings {
std::string Strip(std::string istr);
std::string Replace(std::string istr, std::string oldval, std::string newval);
std::vector<std::string> Split(std::string istr, char delim);
std::string PadNLeadingZeros(std::string istr, unsigned int target_string_size);
long ParseLong(std::string istr);
double ParseDouble(std::string istr);
int StrDateToInt(std::string istr, char delim = '/', int yy_pos = 2,
                 int mm_pos = 0, int dd_pos = 1);
} // namespace pystrings
} // namespace utilities
} // namespace akame
