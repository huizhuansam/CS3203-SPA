#pragma once

#include <list>
#include <string>

class TestUtil {
 public:
  static bool removeDuplicatesAndCompare(std::list<std::string>& result,
                                         std::list<std::string>& expected);
};
