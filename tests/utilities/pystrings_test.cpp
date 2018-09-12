#include "gtest/gtest.h"
#include <cmath>
#include <limits>
#include <string>

#include "utilities/pystrings.h"
using namespace akame;
TEST(PyStringsTest, Strip) {
  std::string input1 = " a b c ";
  const std::string expected1 = "a b c";
  auto result1 = utilities::pystrings::Strip(input1);
  ASSERT_STREQ(expected1.c_str(), result1.c_str());
}

TEST(PyStringsTest, Replace) {
  std::string input1 = "the red owl";
  const std::string expected1 = "the blue owl";
  auto result1 = utilities::pystrings::Replace(input1, std::string("red"),
                                               std::string("blue"));
  ASSERT_STREQ(expected1.c_str(), result1.c_str());
}

TEST(PyStringsTest, Split) {
  std::string input1 = " a b c ";
  auto result1 = utilities::pystrings::Split(input1, ' ');
  std::vector<std::string> expected1;
  expected1.push_back(std::string(""));
  expected1.push_back(std::string("a"));
  expected1.push_back(std::string("b"));
  expected1.push_back(std::string("c"));
  expected1.push_back(std::string(""));
  ASSERT_EQ(expected1.size(), result1.size());
  auto idx = 0;
  for (auto it = result1.begin(); it != result1.end(); it++) {
    ASSERT_STREQ(it->c_str(), (expected1[idx]).c_str());
    idx++;
  }
}

TEST(PyStringsTest, ParseDouble) {
  auto ulp = 2;
  auto result1 = utilities::pystrings::ParseDouble(std::string("420.69"));
  const double expected = 420.69;
  // ASSERT_LE(fabs(result1 - expected), std::numeric_limits<double>::epsilon()
  // * fabs(result1 + expected) * ulp);
  ASSERT_LE(std::abs(result1 - expected),
            std::numeric_limits<double>::epsilon());
  const double close = 420.70;
  ASSERT_FALSE(std::abs(result1 - close) <=
               std::numeric_limits<double>::epsilon());
  const double closer = 420.6999999999;
  ASSERT_FALSE(std::abs(result1 - closer) <=
               std::numeric_limits<double>::epsilon());
}

TEST(PyStringsTest, ParseDoubleNeg) {
  auto ulp = 2;
  auto result1 = utilities::pystrings::ParseDouble(std::string("-420.69"));
  const double expected = -420.69;
  // ASSERT_LE(fabs(result1 - expected), std::numeric_limits<double>::epsilon()
  // * fabs(result1 + expected) * ulp);
  ASSERT_LE(std::abs(result1 - expected),
            std::numeric_limits<double>::epsilon());
  const double close = -420.70;
  ASSERT_FALSE(std::abs(result1 - close) <=
               std::numeric_limits<double>::epsilon());
  const double closer = -420.6999999999;
  ASSERT_FALSE(std::abs(result1 - closer) <=
               std::numeric_limits<double>::epsilon());
}

TEST(PyStringsTest, ParseLong) {
  auto result1 = utilities::pystrings::ParseDouble(std::string("1337"));
  ASSERT_EQ(result1, 1337);
}
