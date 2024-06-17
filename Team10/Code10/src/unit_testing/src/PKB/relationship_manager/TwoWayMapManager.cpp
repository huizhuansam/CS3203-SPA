#include "TwoWayMapManager.h"

#include <algorithm>
#include <vector>

#include "catch.hpp"

TEST_CASE("TwoWayMapManager Test") {
  TwoWayMapManager<int, int> manager;
  SECTION("Empty getAllPairs") {
    std::unordered_set<std::pair<int, int>, PairHash> expected = {};
    REQUIRE(manager.getAllPairs() == expected);
  }

  manager.insert(1, 3);
  manager.insert(1, 4);
  manager.insert(1, 5);
  manager.insert(1, 6);
  manager.insert(1, 7);
  manager.insert(2, 3);
  manager.insert(2, 7);
  manager.insert(2, 4);
  manager.insert(2, 5);
  manager.insert(2, 6);

  SECTION("Left to Right") {
    int left = 1;
    auto actual = manager.getLeftToRight(left);
    std::unordered_set<int> expected = {3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    int right = 3;
    auto actual = manager.getRightToLeft(right);
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }

  SECTION("getAllPairs") {
    std::unordered_set<std::pair<int, int>, PairHash> actual =
        manager.getAllPairs();
    std::unordered_set<std::pair<int, int>, PairHash> expected = {
        {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7},
        {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}};
    REQUIRE(actual == expected);
  }

  SECTION("getAllLefts") {
    std::unordered_set<int> expected = {1, 2};
    std::unordered_set<int> actual = manager.getAllLefts();
    REQUIRE(actual == expected);
  }

  SECTION("getAllRights") {
    std::unordered_set<int> expected = {3, 4, 5, 6, 7};
    std::unordered_set<int> actual = manager.getAllRights();
    REQUIRE(actual == expected);
  }
}

TEST_CASE("TwoWayMapManager<int, string> Test") {
  TwoWayMapManager<int, std::string> manager;
  SECTION("Empty getAllPairs") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {};
    REQUIRE(manager.getAllPairs() == expected);
  }

  manager.insert(1, "b");
  manager.insert(1, "a");
  manager.insert(2, "a");
  manager.insert(2, "c");

  SECTION("Left to Right") {
    int left = 1;
    auto actual = manager.getLeftToRight(left);
    std::unordered_set<std::string> expected = {"b", "a"};
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    std::string right = "a";
    auto actual = manager.getRightToLeft(right);
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }

  SECTION("getAllPairs") {
    auto actual = manager.getAllPairs();
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "a"}, {1, "b"}, {2, "a"}, {2, "c"}};
    REQUIRE(actual == expected);
  }

  SECTION("getAllLefts") {
    std::unordered_set<int> expected = {1, 2};
    std::unordered_set<int> actual = manager.getAllLefts();
    REQUIRE(actual == expected);
  }

  SECTION("getAllRights") {
    std::unordered_set<std::string> expected = {"a", "b", "c"};
    std::unordered_set<std::string> actual = manager.getAllRights();
    REQUIRE(actual == expected);
  }
}
