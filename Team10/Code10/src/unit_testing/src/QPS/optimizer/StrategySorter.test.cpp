#include "optimizer/StrategySorter.h"

#include <memory>
#include <vector>

#include "../fixtures/TestStrategies.h"
#include "catch.hpp"

TEST_CASE("Sort strategies within group correctly", "[QPS][StrategySorter]") {
  std::vector<std::shared_ptr<Strategy>> group1 = {
      TestStrategies::with,
      TestStrategies::affects,
      TestStrategies::pattern1,
  };

  std::vector<std::shared_ptr<Strategy>> group2 = {
      TestStrategies::uses2,     TestStrategies::parent,
      TestStrategies::modifies1, TestStrategies::next,
      TestStrategies::modifies2, TestStrategies::pattern2,
  };

  SECTION("Sort group 1 correctly") {
    StrategySorter::sort(group1);

    // should be in the order of:
    // with a1.stmt# = 20
    // Affects (a1, a2)
    // pattern a2 ("a", _)
    REQUIRE(group1[0] == TestStrategies::with);
    REQUIRE(group1[1] == TestStrategies::affects);
    REQUIRE(group1[2] == TestStrategies::pattern1);
  }

  SECTION("Sort group 2 correctly") {
    StrategySorter::sort(group2);

    // should be in the order of:
    // Modifies (s1, "x")
    // Uses (s1, v1)
    // Parent (s1, s2)
    // Next (s2, s3)
    // pattern a (v1, "x")
    // Modifies (a, v2)
    REQUIRE(group2[0] == TestStrategies::modifies1);
    REQUIRE(group2[1] == TestStrategies::uses2);
    REQUIRE(group2[2] == TestStrategies::parent);
    REQUIRE(group2[3] == TestStrategies::next);
    REQUIRE(group2[4] == TestStrategies::pattern2);
    REQUIRE(group2[5] == TestStrategies::modifies2);
  }
}