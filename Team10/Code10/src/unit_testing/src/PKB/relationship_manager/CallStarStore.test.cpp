#include "relationship_manager/CallStarStore.h"

#include <algorithm>
#include <vector>

#include "catch.hpp"

TEST_CASE("CallStarStore::insert") {
  CallStarStore<std::string, std::string> store;
  store.insert("First", "Second");
  store.insert("Second", "Third");
  store.insert("Second", "Seventh");
  store.insert("Third", "Fourth");
  store.insert("Fourth", "Fifth");

  SECTION("CallStarStore::getAllPairs") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash> actual =
        store.getAllPairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"First", "Second"},  {"First", "Third"},   {"First", "Fourth"},
         {"First", "Fifth"},   {"First", "Seventh"}, {"Second", "Third"},
         {"Second", "Fourth"}, {"Second", "Fifth"},  {"Second", "Seventh"},
         {"Third", "Fourth"},  {"Third", "Fifth"},   {"Fourth", "Fifth"}};
    REQUIRE(actual == expected);
  }
}