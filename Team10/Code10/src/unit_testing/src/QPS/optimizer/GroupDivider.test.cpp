#include "optimizer/GroupDivider.h"

#include <memory>
#include <string>
#include <vector>

#include "../fixtures/TestStrategies.h"
#include "catch.hpp"

using namespace QPS;

const std::unordered_set<std::shared_ptr<Strategy>> EXPECTED_GROUP_1 = {
    TestStrategies::uses1,
};
const std::unordered_set<std::shared_ptr<Strategy>> EXPECTED_GROUP_2 = {
    TestStrategies::affects,
    TestStrategies::pattern1,
    TestStrategies::with,
};
const std::unordered_set<std::shared_ptr<Strategy>> EXPECTED_GROUP_3 = {
    TestStrategies::uses2, TestStrategies::parent,    TestStrategies::modifies1,
    TestStrategies::next,  TestStrategies::modifies2, TestStrategies::pattern2,
};

TEST_CASE("Divide constraint strategies correctly",
          "[QPS][GroupDivider.test]") {
  // such that Uses (5, "y") and
  // Uses (s1, v1) and
  // TestStrategies::affects (a1, a2)
  // TestStrategies::with a1.stmt = 20
  // such that TestStrategies::parent (s1, s2)
  // pattern a2 ("a", _)
  // such that TestStrategies::next (s2, s3) and
  // Modifies (s1, "x") and
  // Modifies (a, v2)
  // pattern a (v1, "x")
  std::vector<std::shared_ptr<Strategy>> strategies = {
      TestStrategies::uses1,     TestStrategies::uses2,
      TestStrategies::affects,   TestStrategies::with,
      TestStrategies::parent,    TestStrategies::pattern1,
      TestStrategies::next,      TestStrategies::modifies1,
      TestStrategies::modifies2, TestStrategies::pattern2,
  };
  std::vector<std::vector<std::shared_ptr<Strategy>>> groups;
  GroupDivider::divide(strategies, groups);
  REQUIRE(groups.size() == 3);

  std::unordered_set<std::shared_ptr<Strategy>> actual_group_1;
  std::unordered_set<std::shared_ptr<Strategy>> actual_group_2;
  std::unordered_set<std::shared_ptr<Strategy>> actual_group_3;

  for (const auto& group : groups) {
    if (group.size() == 1) {
      actual_group_1.insert(group[0]);
    } else if (group.size() == 3) {
      actual_group_2.insert(group.begin(), group.end());
    } else if (group.size() == 6) {
      actual_group_3.insert(group.begin(), group.end());
    } else {
      FAIL("Unexpected group size");
    }
  }

  REQUIRE(actual_group_1 == EXPECTED_GROUP_1);
  REQUIRE(actual_group_2 == EXPECTED_GROUP_2);
  REQUIRE(actual_group_3 == EXPECTED_GROUP_3);
}