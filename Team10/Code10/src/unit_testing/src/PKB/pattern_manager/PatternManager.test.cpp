#include "PatternManager.h"

#include "catch.hpp"

TEST_CASE("Pattern Manager : Assign Expression Store check") {
  PatternManager patternManager;
  patternManager.addAssignExpPattern(1, "test", {"y", "*", "5"});
  patternManager.addAssignExpPattern(2, "Yishun", {"Serangoon", "*", "2"});
  patternManager.addAssignExpPattern(4, "philo", {"a", "/", "2"});
  patternManager.addAssignExpPattern(5, "this_mod", {"time", "*", "0"});
  patternManager.addAssignExpPattern(6, "test",
                                     {
                                         "x",
                                         "+",
                                         "y",
                                         "*",
                                         "5",
                                         "-",
                                         "z",
                                         "+",
                                         "(",
                                         "a",
                                         "/",
                                         "2",
                                         ")",
                                         "*",
                                         "b",
                                     });
  patternManager.addAssignExpPattern(7, "test", {"x", "*", "y"});

  SECTION("Check getAllExpPairs()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {{"1", "test"},     {"2", "Yishun"}, {"4", "philo"},
                          {"5", "this_mod"}, {"6", "test"},   {"7", "test"}};
    auto actualVector = patternManager.getAllAssignExpPairs();

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getAssignExpPairsPartialMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {{"1", "test"}, {"6", "test"}};

    auto actualVector =
        patternManager.getAssignExpPairsPartialMatch("test", {"y", "*", "5"});

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getAssignExpPairsSynonymPartialMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {
            {"4", "philo"},
            {"6", "test"},
        };

    auto actualVector =
        patternManager.getAssignExpPairsSynonymPartialMatch({"a", "/", "2"});

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getAssignExpPairsExactMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {{"1", "test"}};

    auto actualVector =
        patternManager.getAssignExpPairsExactMatch("test", {"y", "*", "5"});

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getAssignExpPairsSynonymExactMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {{"4", "philo"}};

    auto actualVector =
        patternManager.getAssignExpPairsSynonymExactMatch({"a", "/", "2"});

    REQUIRE(actualVector == expectedVector);
  }
}

TEST_CASE("Pattern Manager: Check While Pattern Store") {
  PatternManager patternManager;
  patternManager.addWhileControlVariable(1, "a");
  patternManager.addWhileControlVariable(1, "b");
  patternManager.addWhileControlVariable(2, "a");
  patternManager.addWhileControlVariable(3, "a");
  patternManager.addWhileControlVariable(4, "A");
  patternManager.addWhileControlVariable(5, "b");
  patternManager.addWhileControlVariable(6, "c");

  SECTION("Check getControlVariableOfWhileStmt()") {
    std::unordered_set<std::string> expected = {"a", "b"};
    std::unordered_set<std::string> actual =
        patternManager.getControlVariableOfWhileStmt(1);

    REQUIRE(actual == expected);
  }

  SECTION("Check getWhileStmtsThatUseControlVariable()") {
    std::unordered_set<int> expected = {1, 2, 3};
    std::unordered_set<int> actual =
        patternManager.getWhileStmtsThatUseControlVariable("a");

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllWhileControlVariablePairs()") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "a"}, {1, "b"}, {2, "a"}, {3, "a"}, {4, "A"}, {5, "b"}, {6, "c"}};
    std::unordered_set<std::pair<int, std::string>, PairHash> actual =
        patternManager.getAllWhileControlVariablePairs();

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllWhileStmtsThatUseControlVariables()") {
    std::unordered_set<int> expected = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> actual =
        patternManager.getAllWhileStmtsThatUseControlVariables();

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllWhileControlVariables()") {
    std::unordered_set<std::string> expected = {"a", "A", "b", "c"};
    std::unordered_set<std::string> actual =
        patternManager.getAllWhileControlVariables();

    REQUIRE(actual == expected);
  }
}

TEST_CASE("Pattern Manager: Check If Pattern Store") {
  PatternManager patternManager;
  patternManager.addIfControlVariable(1, "a");
  patternManager.addIfControlVariable(1, "c");
  patternManager.addIfControlVariable(2, "a");
  patternManager.addIfControlVariable(3, "a");
  patternManager.addIfControlVariable(4, "A");
  patternManager.addIfControlVariable(5, "b");
  patternManager.addIfControlVariable(6, "c");

  SECTION("Check getControlVariableOfIfStmt()") {
    std::unordered_set<std::string> expected = {"a", "c"};
    std::unordered_set<std::string> actual =
        patternManager.getControlVariableOfIfStmt(1);

    REQUIRE(actual == expected);
  }

  SECTION("Check getIfStmtsThatUseControlVariable()") {
    std::unordered_set<int> expected = {1, 2, 3};
    std::unordered_set<int> actual =
        patternManager.getIfStmtsThatUseControlVariable("a");

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllIfControlVariablePairs()") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "a"}, {1, "c"}, {2, "a"}, {3, "a"}, {4, "A"}, {5, "b"}, {6, "c"}};
    std::unordered_set<std::pair<int, std::string>, PairHash> actual =
        patternManager.getAllIfControlVariablePairs();

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllIfStmtsThatUseControlVariables()") {
    std::unordered_set<int> expected = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> actual =
        patternManager.getAllIfStmtsThatUseControlVariables();

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllIfControlVariables()") {
    std::unordered_set<std::string> expected = {"a", "A", "b", "c"};
    std::unordered_set<std::string> actual =
        patternManager.getAllIfControlVariables();

    REQUIRE(actual == expected);
  }
}
