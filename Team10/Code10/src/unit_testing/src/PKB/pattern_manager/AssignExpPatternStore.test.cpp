#include "pattern_manager/AssignExpPatternStore.h"

#include "catch.hpp"

TEST_CASE("Check isAlphanumeric") {
  AssignExpPatternStore assignExpStore;
  REQUIRE(assignExpStore.isAlphanumeric("1") == true);
  REQUIRE(assignExpStore.isAlphanumeric("a") == true);
  REQUIRE(assignExpStore.isAlphanumeric("elephant") == true);

  REQUIRE(assignExpStore.isAlphanumeric("/") == false);
  REQUIRE(assignExpStore.isAlphanumeric("+") == false);
  REQUIRE(assignExpStore.isAlphanumeric("?") == false);
}

TEST_CASE("Check isArithmeticOperator") {
  AssignExpPatternStore assignExpStore;
  REQUIRE(assignExpStore.isArithmeticOperator("+") == true);
  REQUIRE(assignExpStore.isArithmeticOperator("-") == true);
  REQUIRE(assignExpStore.isArithmeticOperator("/") == true);
  REQUIRE(assignExpStore.isArithmeticOperator("*") == true);
  REQUIRE(assignExpStore.isArithmeticOperator("%") == true);

  REQUIRE(assignExpStore.isArithmeticOperator("1") == false);
  REQUIRE(assignExpStore.isArithmeticOperator("elephant") == false);
  REQUIRE(assignExpStore.isArithmeticOperator("?") == false);
}

TEST_CASE("Check precedence") {
  AssignExpPatternStore assignExpStore;
  REQUIRE(assignExpStore.precedence("*") == 2);
  REQUIRE(assignExpStore.precedence("/") == 2);
  REQUIRE(assignExpStore.precedence("%") == 2);

  REQUIRE(assignExpStore.precedence("+") == 1);
  REQUIRE(assignExpStore.precedence("-") == 1);

  REQUIRE(assignExpStore.precedence("1") == 0);
  REQUIRE(assignExpStore.precedence("a") == 0);
  REQUIRE(assignExpStore.precedence("elephant") == 0);
}

TEST_CASE("Check infixToPostfix") {
  AssignExpPatternStore assignExpStore;
  std::vector<std::string> testVector = {"x", "+", "y"};
  std::vector<std::string> expectedVector = {"x", "y", "+"};

  REQUIRE(assignExpStore.infixToPostfix(testVector) == expectedVector);

  testVector = {
      "x", "+", "y", "*", "5", "-", "z", "+", "(", "a", "/", "2", ")", "*", "b",
  };

  expectedVector = {"x", "y", "5", "*", "+", "z", "-",
                    "a", "2", "/", "b", "*", "+"};

  REQUIRE(assignExpStore.infixToPostfix(testVector) == expectedVector);
}

TEST_CASE("Assign Expression Store check") {
  AssignExpPatternStore assignExpStore;
  assignExpStore.addExp(1, "test", {"y", "*", "5"});
  assignExpStore.addExp(2, "Yishun", {"Serangoon", "*", "2"});
  assignExpStore.addExp(4, "philo", {"a", "/", "2"});
  assignExpStore.addExp(5, "this_mod", {"time", "*", "0"});
  assignExpStore.addExp(6, "test",
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
  assignExpStore.addExp(7, "test", {"x", "*", "y"});

  SECTION("Check getAllExpPairs()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {{"1", "test"},     {"2", "Yishun"}, {"4", "philo"},
                          {"5", "this_mod"}, {"6", "test"},   {"7", "test"}};
    auto actualVector = assignExpStore.getAllExpPairs();

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getExpPairsPartialMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {{"1", "test"}, {"6", "test"}};

    auto actualVector =
        assignExpStore.getExpPairsPartialMatch("test", {"y", "*", "5"});

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getExpPairsSynonymPartialMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {
            {"4", "philo"},
            {"6", "test"},
        };

    auto actualVector =
        assignExpStore.getExpPairsSynonymPartialMatch({"a", "/", "2"});

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getExpPairsExactMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {{"1", "test"}};

    auto actualVector =
        assignExpStore.getExpPairsExactMatch("test", {"y", "*", "5"});

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getExpPairsSynonymExactMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {{"4", "philo"}};

    auto actualVector =
        assignExpStore.getExpPairsSynonymExactMatch({"a", "/", "2"});

    REQUIRE(actualVector == expectedVector);
  }
}