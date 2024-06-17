#include "optimizer/GroupSorter.h"

#include <memory>
#include <string>
#include <vector>

#include "../fixtures/TestStrategies.h"
#include "catch.hpp"

using namespace QPS;

const std::vector<std::shared_ptr<Strategy>> group1 = {
    TestStrategies::uses1,
};
const std::vector<std::shared_ptr<Strategy>> group2 = {
    TestStrategies::affects,
    TestStrategies::pattern1,
    TestStrategies::with,
};
const std::vector<std::shared_ptr<Strategy>> group3 = {
    TestStrategies::uses2, TestStrategies::parent,    TestStrategies::modifies1,
    TestStrategies::next,  TestStrategies::modifies2, TestStrategies::pattern2,
};

TEST_CASE("Sort group correctly", "[QPS][GroupSorter]") {
  std::vector<std::vector<std::shared_ptr<Strategy>>> groups = {
      group1,
      group2,
      group3,
  };

  SECTION("Select synonym only in group 2") {
    std::unordered_set<std::string> selectSynonyms = {"a1", "a2"};

    GroupSorter::sort(selectSynonyms, groups);

    REQUIRE(groups[0] == group1);  // no synonym always come first
    REQUIRE(groups[1] == group3);  // no select synonym
    REQUIRE(groups[2] == group2);  // has select synonym
  }

  SECTION("Select synonym only in group 3") {
    std::unordered_set<std::string> selectSynonyms = {"s1", "s2", "s3", "v1",
                                                      "v2"};

    GroupSorter::sort(selectSynonyms, groups);

    REQUIRE(groups[0] == group1);  // no synonym always come first
    REQUIRE(groups[1] == group2);  // no select synonym
    REQUIRE(groups[2] == group3);  // has select synonym
  }
}