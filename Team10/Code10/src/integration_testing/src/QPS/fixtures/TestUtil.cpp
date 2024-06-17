#include "TestUtil.h"

#include <unordered_set>

bool TestUtil::removeDuplicatesAndCompare(std::list<std::string>& result,
                                          std::list<std::string>& expected) {
  std::unordered_set<std::string> res(result.begin(), result.end());
  std::unordered_set<std::string> exp(expected.begin(), expected.end());
  return res == exp;
}
