#include "entity_manager/StatementStore.h"

#include <unordered_set>

#include "catch.hpp"

TEST_CASE("Statement Store test") {
  StatementStore stmtStore;

  stmtStore.addStatement(StatementType::ASSIGN, 1);

  stmtStore.addStatement(StatementType::READ, 2);
  stmtStore.addStatement(StatementType::READ, 3);

  stmtStore.addStatement(StatementType::PRINT, 4);
  stmtStore.addStatement(StatementType::PRINT, 5);
  stmtStore.addStatement(StatementType::PRINT, 6);

  stmtStore.addStatement(StatementType::CALL, 7);

  stmtStore.addStatement(StatementType::WHILE, 8);

  stmtStore.addStatement(StatementType::IF, 9);

  stmtStore.addStatement(StatementType::IF, 10);

  SECTION("Check statements") {
    std::unordered_set<int> testSet = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    REQUIRE(testSet == stmtStore.getStatements());
  }
  SECTION("Check Reads") {
    std::unordered_set<int> testSet = {2, 3};

    REQUIRE(testSet == stmtStore.getReads());
  }
  SECTION("Check Prints") {
    std::unordered_set<int> testSet = {4, 5, 6};

    REQUIRE(testSet == stmtStore.getPrints());
  }
  SECTION("Check Calls") {
    std::unordered_set<int> testSet = {7};

    REQUIRE(testSet == stmtStore.getCalls());
  }
  SECTION("Check Whiles") {
    std::unordered_set<int> testSet = {8};

    REQUIRE(testSet == stmtStore.getWhiles());
  }
  SECTION("Check Ifs") {
    std::unordered_set<int> testSet = {9, 10};

    REQUIRE(testSet == stmtStore.getIfs());
  }
}
