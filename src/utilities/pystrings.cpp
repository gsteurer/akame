#include "utilities/pystrings.h"

namespace akame {
namespace utilities {
namespace pystrings {
std::string Strip(std::string istr) {
  std::string retstr = "";
  unsigned int start_pos = 0;
  while (istr[start_pos] == ' ' || istr[start_pos] == '\n' ||
         istr[start_pos] == '\r' || istr[start_pos] == '\t') {
    start_pos++;
  }
  unsigned int end_pos = istr.length() - 1;
  while (istr[end_pos] == ' ' || istr[end_pos] == '\n' ||
         istr[end_pos] == '\r' || istr[end_pos] == '\t') {
    end_pos--;
  }

  for (unsigned int pos = start_pos; pos <= end_pos; pos++) {
    retstr += istr[pos];
  }

  return retstr;
}
std::string Replace(std::string istr, std::string oldval, std::string newval) {
  std::string newstr = istr;
  size_t pos = newstr.find(oldval);
  while (pos != std::string::npos) {
    newstr.replace(pos, oldval.length(), newval);
    pos = newstr.find(oldval);
  }

  return newstr;
}
std::vector<std::string> Split(std::string istr, char delim) {
  std::vector<std::string> ret;
  std::string tok;
  for (unsigned int idx = 0; idx < istr.length(); idx++) {

    if (delim == istr[idx]) {
      ret.push_back(tok);
      tok = "";
      idx++;
    }

    tok += istr[idx];
  }
  if (tok.length() != 0) {
    ret.push_back(tok);
  }
  return ret;
}

std::string PadNLeadingZeros(std::string istr,
                             unsigned int target_string_size) {
  unsigned int idx = istr.length();
  for (; idx < target_string_size; idx++) {
    istr = "0" + istr;
  }
  return istr;
}
long ParseLong(std::string istr) {
  if (istr.length() < 1) {
    return 0;
  }
  long ret = 0;
  long sign = 1;
  int start_pos = 0;
  if (istr[0] == '-') {
    sign = -1;
    start_pos = 1;
  }
  long mult = 1;

  int end_pos = istr.length() - 1;
  for (unsigned int idx = 0; idx < istr.length(); idx++) {
    if (istr[idx] == '.') {
      end_pos = idx - 1;
      break;
    }
  }
  for (; end_pos >= start_pos; end_pos--) {

    char search = istr[end_pos];
    if (search < 48 || search > 57) {
      throw std::range_error("Value out of range.");
    }
    ret += (search - 48) * mult;
    mult *= 10;
  }

  return ret * sign;
}
double ParseDouble(std::string istr) {
  if (istr.length() < 1) {
    return 0;
  }
  double ret = 0.0;
  double sign = 1;
  int start_pos = 0;
  if (istr[0] == '-') {
    sign = -1;
    start_pos = 1;
  }
  int period_pos = istr.length();
  for (int idx = 0; idx < (int)istr.length(); idx++) {
    if (istr[idx] == '.') {
      period_pos = idx;
      break;
    }
  }

  double mult = 1;
  for (int idx = period_pos - 1; idx >= start_pos; idx--) {
    char search = istr[idx];
    if (search < 48 || search > 57) {
      throw std::range_error("Value out of range.");
    }
    ret += (double)(search - 48) * mult;
    mult *= 10;
  }

  if (period_pos != (int)istr.length()) {
    double div = 10;
    for (int idx = period_pos + 1; idx < (int)istr.length(); idx++) {
      char search = istr[idx];
      if (search < 48 || search > 57) {
        throw std::range_error("Value out of range.");
      }
      ret += (double)(search - 48) / div;
      div *= 10;
    }
  }

  return ret * sign;
}
int StrDateToInt(std::string istr, char delim, int yy_pos,
                 int mm_pos, int dd_pos) {
  std::vector<std::string> splitdt = Split(istr, delim);
  if (splitdt.size() != 3) {
    throw std::range_error("Value out of range.");
  }

  long mm = ParseLong(splitdt[mm_pos]);
  long dd = ParseLong(splitdt[dd_pos]);
  long yyyy = ParseLong(splitdt[yy_pos]);

  return dd + (mm * 100) + (yyyy * 10000);
}

} // namespace pystrings
} // namespace utilities
} // namespace akame