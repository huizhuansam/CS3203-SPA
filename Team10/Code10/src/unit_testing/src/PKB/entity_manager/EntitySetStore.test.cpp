#include "entity_manager/EntitySetStore.h"

#include <unordered_set>

#include "catch.hpp"

TEST_CASE("Entity Set Store") {
  EntitySetStore<int> testIntStore;
  EntitySetStore<std::string> testStringStore;

  SECTION("Check insert and getAll()") {
    testIntStore.insert(2);
    testStringStore.insert("test123");

    std::unordered_set<int> intStoreCheck = {2};
    std::unordered_set<std::string> stringStoreCheck = {"test123"};

    REQUIRE(testIntStore.getAll() == intStoreCheck);
    REQUIRE(testStringStore.getAll() == stringStoreCheck);
  }
}
