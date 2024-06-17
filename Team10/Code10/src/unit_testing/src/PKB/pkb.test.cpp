#include "PKB.h"

#include <unordered_set>

#include "catch.hpp"

TEST_CASE("Singleton test") {
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  SECTION("Facades reference same instance of PKB") {
    PKB& facade1 = PKB::getPKB();
    PKB& facade2 = PKB::getPKB();

    REQUIRE(&facade1 == &facade2);
  }
}

TEST_CASE("PKB: Insert and Retrieve Entities") {
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  SECTION("Constants") {
    std::string str1 = "x";
    std::string str2 = "1";
    std::string str3 = "TESTING!@#";

    pkb.addConstant(str1);
    pkb.addConstant(str2);
    pkb.addConstant(str3);

    std::unordered_set<std::string> test = {"x", "1", "TESTING!@#"};
    REQUIRE(pkb.getAllConstants() == test);
  }

  SECTION("Variables") {
    std::string str1 = "Yishun";
    std::string str2 = "count";
    std::string str3 = "Mario";

    pkb.addVariable(str1);
    pkb.addVariable(str2);
    pkb.addVariable(str3);

    std::unordered_set<std::string> test = {"Yishun", "count", "Mario"};
    REQUIRE(pkb.getAllVariables() == test);
  }

  SECTION("Procedures") {
    std::string str1 = "computeCentroids";
    std::string str2 = "printCentrals";
    std::string str3 = "deleteAll";

    pkb.addProcedure(str1);
    pkb.addProcedure(str2);
    pkb.addProcedure(str3);

    std::unordered_set<std::string> test = {"computeCentroids", "printCentrals",
                                            "deleteAll"};
    REQUIRE(pkb.getAllProcedures() == test);
  }
}

TEST_CASE("PKB: Stmt Mapped to Ident") {
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  pkb.insertStmtCallsProc(1, "first");
  pkb.insertStmtCallsProc(2, "second");
  pkb.insertStmtCallsProc(3, "second");
  pkb.insertStmtCallsProc(4, "third");

  pkb.insertStmtPrintsVar(5, "v");
  pkb.insertStmtPrintsVar(6, "x");
  pkb.insertStmtPrintsVar(7, "y");

  pkb.insertStmtReadsVar(8, "v");
  pkb.insertStmtReadsVar(9, "x");
  pkb.insertStmtReadsVar(10, "z");

  SECTION("Check Stmt Number Mapped to Call") {
    std::string expected = "first";
    REQUIRE(expected == pkb.getProcCalledByStmt(1));
  }

  SECTION("getAllStmtsThatCallProc") {
    std::unordered_set<int> expected = {2, 3};
    std::string input = "second";
    REQUIRE(expected == pkb.getAllStmtsThatCallProc(input));
  }

  SECTION("getAllCallsProcPairs") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "first"}, {2, "second"}, {3, "second"}, {4, "third"}};
    REQUIRE(expected == pkb.getAllCallsProcPairs());
  }

  SECTION("getAllProceduresCalledByStmts") {
    std::unordered_set<std::string> expected = {"first", "second", "third"};
    REQUIRE(expected == pkb.getAllProceduresCalledByStmts());
  }

  SECTION("Check Stmt Number Mapped to Print") {
    std::string expected = "v";
    REQUIRE(expected == pkb.getVarPrintedByStmt(5));
  }

  SECTION("getAllStmtsThatPrintVar") {
    std::unordered_set<int> expected = {5};
    std::string input = "v";
    REQUIRE(expected == pkb.getAllStmtsThatPrintVar(input));
  }

  SECTION("getAllPrintVarPairs") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {5, "v"}, {6, "x"}, {7, "y"}};
    REQUIRE(expected == pkb.getAllPrintVarPairs());
  }

  SECTION("getAllRights()") {
    std::unordered_set<std::string> expected = {"v", "x", "y"};
    REQUIRE(expected == pkb.getAllVarsPrintByStmts());
  }

  SECTION("Check Stmt Number Mapped to Read") {
    std::string expected = "v";
    REQUIRE(expected == pkb.getVarReadByStmt(8));
  }

  SECTION("getAllStmtsThatReadVar") {
    std::unordered_set<int> expected = {9};
    std::string input = "x";
    REQUIRE(expected == pkb.getAllStmtsThatReadVar(input));
  }

  SECTION("getAllReadVarPairs") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {8, "v"}, {9, "x"}, {10, "z"}};
    REQUIRE(expected == pkb.getAllReadVarPairs());
  }

  SECTION("getAllVarsReadByStmts") {
    std::unordered_set<std::string> expected = {"v", "x", "z"};
    REQUIRE(expected == pkb.getAllVarsReadByStmts());
  }
}

TEST_CASE("PKB : Assign Expression Store check") {
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  pkb.addAssignExpPattern(1, "test", {"y", "*", "5"});
  pkb.addAssignExpPattern(2, "Yishun", {"Serangoon", "*", "2"});
  pkb.addAssignExpPattern(4, "philo", {"a", "/", "2"});
  pkb.addAssignExpPattern(5, "this_mod", {"time", "*", "0"});
  pkb.addAssignExpPattern(6, "test",
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
  pkb.addAssignExpPattern(7, "test", {"x", "*", "y"});

  SECTION("Check getAllExpPairs()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {{"1", "test"},     {"2", "Yishun"}, {"4", "philo"},
                          {"5", "this_mod"}, {"6", "test"},   {"7", "test"}};
    auto actualVector = pkb.getAllAssignExpPairs();

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getAssignExpPairsPartialMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {{"1", "test"}, {"6", "test"}};

    auto actualVector =
        pkb.getAssignExpPairsPartialMatch("test", {"y", "*", "5"});

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getAssignExpPairsSynonymPartialMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {
            {"4", "philo"},
            {"6", "test"},
        };

    auto actualVector =
        pkb.getAssignExpPairsSynonymPartialMatch({"a", "/", "2"});

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getAssignExpPairsExactMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {{"1", "test"}};

    auto actualVector =
        pkb.getAssignExpPairsExactMatch("test", {"y", "*", "5"});

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getAssignExpPairsSynonymExactMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {{"4", "philo"}};

    auto actualVector = pkb.getAssignExpPairsSynonymExactMatch({"a", "/", "2"});

    REQUIRE(actualVector == expectedVector);
  }
}

TEST_CASE("PKB: Check While Pattern Store") {
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  pkb.addWhileControlVariable(1, "a");
  pkb.addWhileControlVariable(1, "b");
  pkb.addWhileControlVariable(2, "a");
  pkb.addWhileControlVariable(3, "a");
  pkb.addWhileControlVariable(4, "A");
  pkb.addWhileControlVariable(5, "b");
  pkb.addWhileControlVariable(6, "c");

  SECTION("Check getControlVariableOfWhileStmt()") {
    std::unordered_set<std::string> expected = {"a", "b"};
    std::unordered_set<std::string> actual =
        pkb.getControlVariableOfWhileStmt(1);

    REQUIRE(actual == expected);
  }

  SECTION("Check getWhileStmtsThatUseControlVariable()") {
    std::unordered_set<int> expected = {1, 2, 3};
    std::unordered_set<int> actual =
        pkb.getWhileStmtsThatUseControlVariable("a");

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllWhileControlVariablePairs()") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "a"}, {1, "b"}, {2, "a"}, {3, "a"}, {4, "A"}, {5, "b"}, {6, "c"}};
    std::unordered_set<std::pair<int, std::string>, PairHash> actual =
        pkb.getAllWhileControlVariablePairs();

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllWhileStmtsThatUseControlVariables()") {
    std::unordered_set<int> expected = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> actual =
        pkb.getAllWhileStmtsThatUseControlVariables();

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllWhileControlVariables()") {
    std::unordered_set<std::string> expected = {"a", "A", "b", "c"};
    std::unordered_set<std::string> actual = pkb.getAllWhileControlVariables();

    REQUIRE(actual == expected);
  }
}

TEST_CASE("PKB: Check If Pattern Store") {
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  pkb.addIfControlVariable(1, "a");
  pkb.addIfControlVariable(1, "c");
  pkb.addIfControlVariable(2, "a");
  pkb.addIfControlVariable(3, "a");
  pkb.addIfControlVariable(4, "A");
  pkb.addIfControlVariable(5, "b");
  pkb.addIfControlVariable(6, "c");

  SECTION("Check getControlVariableOfIfStmt()") {
    std::unordered_set<std::string> expected = {"a", "c"};
    std::unordered_set<std::string> actual = pkb.getControlVariableOfIfStmt(1);

    REQUIRE(actual == expected);
  }

  SECTION("Check getIfStmtsThatUseControlVariable()") {
    std::unordered_set<int> expected = {1, 2, 3};
    std::unordered_set<int> actual = pkb.getIfStmtsThatUseControlVariable("a");

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllIfControlVariablePairs()") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "a"}, {1, "c"}, {2, "a"}, {3, "a"}, {4, "A"}, {5, "b"}, {6, "c"}};
    std::unordered_set<std::pair<int, std::string>, PairHash> actual =
        pkb.getAllIfControlVariablePairs();

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllIfStmtsThatUseControlVariables()") {
    std::unordered_set<int> expected = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> actual = pkb.getAllIfStmtsThatUseControlVariables();

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllIfControlVariables()") {
    std::unordered_set<std::string> expected = {"a", "A", "b", "c"};
    std::unordered_set<std::string> actual = pkb.getAllIfControlVariables();

    REQUIRE(actual == expected);
  }
}

TEST_CASE("PKB: Insert and Retrieve Relationships - Parent") {
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  int parent = 1;
  int child = 2;
  pkb.insertDirectParentChildRelationship(parent, child);
  SECTION("Left to Right") {
    auto actual = pkb.getChildren(parent);
    std::unordered_set<int> expected;
    expected.insert(child);
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    auto actual = pkb.getParent(child);
    int expected = parent;
    REQUIRE(actual == expected);
  }
  pkb.insertParentStarRelationship(1, 2);
  pkb.insertParentStarRelationship(1, 3);
  pkb.insertParentStarRelationship(1, 4);
  pkb.insertParentStarRelationship(1, 5);
  pkb.insertParentStarRelationship(1, 6);
  pkb.insertParentStarRelationship(1, 7);
  pkb.insertParentStarRelationship(2, 3);
  pkb.insertParentStarRelationship(2, 4);
  pkb.insertParentStarRelationship(2, 5);
  pkb.insertParentStarRelationship(2, 6);
  pkb.insertParentStarRelationship(2, 7);
  pkb.insertParentStarRelationship(2, 7);
  pkb.insertParentStarRelationship(2, 7);

  pkb.insertDirectParentChildRelationship(2, 3);
  pkb.insertDirectParentChildRelationship(2, 4);
  pkb.insertDirectParentChildRelationship(2, 5);
  pkb.insertDirectParentChildRelationship(2, 6);
  pkb.insertDirectParentChildRelationship(2, 7);

  SECTION("getAllParentPairs") {
    std::unordered_set<std::pair<int, int>, PairHash> actual =
        pkb.getAllParentPairs();
    std::unordered_set<std::pair<int, int>, PairHash> expected = {
        {1, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}};
    REQUIRE(actual == expected);
  }

  SECTION("getAllParentStarPairs") {
    auto actual = pkb.getAllParentStarPairs();
    std::unordered_set<std::pair<int, int>, PairHash> expected = {
        {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7},
        {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}};
    REQUIRE(actual == expected);
  }

  SECTION("getChildrenStar") {
    auto actual = pkb.getChildrenStar(1);
    std::unordered_set<int> expected = {2, 3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }

  SECTION("getParentsStar") {
    auto actual = pkb.getParentsStar(3);
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }
  SECTION("getAllParents") {
    std::unordered_set<int> actual = pkb.getAllParents();
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }
  SECTION("getAllChildren") {
    std::unordered_set<int> actual = pkb.getAllChildren();
    std::unordered_set<int> expected = {2, 3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("PKB: Insert and Retrieve Relationships - Follows") {
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  pkb.insertFollowsStarRelationship(1, 3);
  pkb.insertFollowsStarRelationship(1, 2);
  pkb.insertFollowsStarRelationship(1, 7);
  pkb.insertFollowsStarRelationship(1, 4);
  pkb.insertFollowsStarRelationship(1, 5);
  pkb.insertFollowsStarRelationship(1, 6);
  pkb.insertFollowsStarRelationship(2, 6);
  pkb.insertFollowsStarRelationship(2, 3);
  pkb.insertFollowsStarRelationship(2, 7);
  pkb.insertFollowsStarRelationship(2, 4);
  pkb.insertFollowsStarRelationship(2, 5);
  pkb.insertDirectFollowsRelationship(1, 2);
  pkb.insertDirectFollowsRelationship(2, 3);

  SECTION("expect direct follows relationship values") {
    REQUIRE(pkb.getStmtThatFollowsBefore(2) == 1);
    REQUIRE(pkb.getStmtThatFollowsAfter(1) == 2);
    REQUIRE(pkb.getStmtThatFollowsBefore(1) != 2);
  }

  SECTION("expect all follows pairs") {
    std::unordered_set<std::pair<int, int>, PairHash> actual =
        pkb.getAllFollowPairs();

    std::unordered_set<std::pair<int, int>, PairHash> expected = {{1, 2},
                                                                  {2, 3}};
    REQUIRE(actual == expected);
  }

  SECTION("expect all follows star pairs") {
    auto actual = pkb.getAllFollowStarPairs();

    std::unordered_set<std::pair<int, int>, PairHash> expected = {
        {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7},
        {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}};
    REQUIRE(actual == expected);
  }

  SECTION("before to after follows star") {
    auto actual = pkb.getAllStmtsThatFollowAfter(1);
    std::unordered_set<int> expected = {2, 3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }

  SECTION("after to before follows star") {
    auto actual = pkb.getAllStmtsThatFollowBefore(3);
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }

  SECTION("getAllStmtsThatFollowAfterOtherStmts") {
    std::unordered_set<int> actual =
        pkb.getAllStmtsThatFollowBeforeOtherStmts();
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }
  SECTION("getAllStmtsThatFollowAfterOtherStmts") {
    std::unordered_set<int> actual = pkb.getAllStmtsThatFollowAfterOtherStmts();
    std::unordered_set<int> expected = {2, 3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("PKB: Insert and Retrieve Relationships - Calls") {
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  std::string source = "First";
  std::string target = "Second";
  pkb.insertCallsRelationship(source, target);

  SECTION("Left to Right") {
    auto actual = pkb.getProcsThatIsCalledBy(source);
    std::unordered_set<std::string> expected;
    expected.insert(target);
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    auto actual = pkb.getProcsThatCalls(target);
    std::unordered_set<std::string> expected;
    expected.insert(source);
    REQUIRE(actual == expected);
  }

  pkb.insertCallsRelationship("First", "Second");
  pkb.insertCallsRelationship("Second", "Third");
  pkb.insertCallsRelationship("Second", "Fourth");
  pkb.insertCallsRelationship("Second", "Fifth");
  pkb.insertCallsRelationship("Second", "Sixth");
  pkb.insertCallsRelationship("Second", "Seventh");
  pkb.insertCallsRelationship("Second", "Seventh");
  pkb.insertCallsRelationship("Second", "Seventh");

  SECTION("getAllCallPairs") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash> actual =
        pkb.getAllCallPairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"First", "Second"}, {"Second", "Third"}, {"Second", "Fourth"},
         {"Second", "Fifth"}, {"Second", "Sixth"}, {"Second", "Seventh"}};

    REQUIRE(actual == expected);
  }

  SECTION("getAllCallStarPairs") {
    auto actual = pkb.getAllCallStarPairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"First", "Second"}, {"First", "Third"},   {"First", "Fourth"},
         {"First", "Fifth"},  {"First", "Sixth"},   {"First", "Seventh"},
         {"Second", "Third"}, {"Second", "Fourth"}, {"Second", "Fifth"},
         {"Second", "Sixth"}, {"Second", "Seventh"}};

    REQUIRE(actual == expected);
  }

  SECTION("getProcsThatIsCalledByStar") {
    std::string first = "First";
    auto actual = pkb.getProcsThatIsCalledByStar(first);
    std::unordered_set<std::string> expected = {"Second", "Third", "Fourth",
                                                "Fifth",  "Sixth", "Seventh"};
    REQUIRE(actual == expected);
  }

  SECTION("getProcsThatCallsStar") {
    std::string third = "Third";
    auto actual = pkb.getProcsThatCallsStar(third);
    std::unordered_set<std::string> expected = {"First", "Second"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllProcsThatCallOtherProcs") {
    std::unordered_set<std::string> actual =
        pkb.getAllProcsThatCallOtherProcs();
    std::unordered_set<std::string> expected = {"First", "Second"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllProcsThatGetCalledByOtherProcs") {
    std::unordered_set<std::string> actual =
        pkb.getAllProcsThatGetCalledByOtherProcs();
    std::unordered_set<std::string> expected = {"Second", "Third", "Fourth",
                                                "Fifth",  "Sixth", "Seventh"};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("PKB: Updated Call Test") {
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  std::string source = "First";
  std::string target = "Second";
  pkb.insertCallsRelationship(source, target);

  SECTION("Left to Right") {
    auto actual = pkb.getProcsThatIsCalledBy(source);
    std::unordered_set<std::string> expected;
    expected.insert(target);
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    auto actual = pkb.getProcsThatCalls(target);
    std::unordered_set<std::string> expected;
    expected.insert(source);
    REQUIRE(actual == expected);
  }

  pkb.insertCallsRelationship("Second", "Third");
  pkb.insertCallsRelationship("Second", "Fourth");
  pkb.insertCallsRelationship("Second", "Fifth");
  pkb.insertCallsRelationship("Second", "Sixth");
  pkb.insertCallsRelationship("Second", "Seventh");
  pkb.insertCallsRelationship("Second", "Seventh");
  pkb.insertCallsRelationship("Second", "Seventh");

  SECTION("getAllCallPairs") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash> actual =
        pkb.getAllCallPairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"First", "Second"}, {"Second", "Third"}, {"Second", "Fourth"},
         {"Second", "Fifth"}, {"Second", "Sixth"}, {"Second", "Seventh"}};

    REQUIRE(actual == expected);
  }

  SECTION("getAllCallStarPairs") {
    auto actual = pkb.getAllCallStarPairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"First", "Second"}, {"First", "Third"},   {"First", "Fourth"},
         {"First", "Fifth"},  {"First", "Sixth"},   {"First", "Seventh"},
         {"Second", "Third"}, {"Second", "Fourth"}, {"Second", "Fifth"},
         {"Second", "Sixth"}, {"Second", "Seventh"}};

    REQUIRE(actual == expected);
  }

  SECTION("getProcsThatIsCalledByStar") {
    std::string first = "First";
    auto actual = pkb.getProcsThatIsCalledByStar(first);
    std::unordered_set<std::string> expected = {"Second", "Third", "Fourth",
                                                "Fifth",  "Sixth", "Seventh"};
    REQUIRE(actual == expected);
  }

  SECTION("getProcsThatCallsStar") {
    std::string third = "Third";
    auto actual = pkb.getProcsThatCallsStar(third);
    std::unordered_set<std::string> expected = {"First", "Second"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllProcsThatCallOtherProcs") {
    std::unordered_set<std::string> actual =
        pkb.getAllProcsThatCallOtherProcs();
    std::unordered_set<std::string> expected = {"First", "Second"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllProcsThatGetCalledByOtherProcs") {
    std::unordered_set<std::string> actual =
        pkb.getAllProcsThatGetCalledByOtherProcs();
    std::unordered_set<std::string> expected = {"Second", "Third", "Fourth",
                                                "Fifth",  "Sixth", "Seventh"};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("PKB: Insert and Retrieve Relationships - Modifies") {
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  pkb.insertModifies(1, "a");
  pkb.insertModifies(1, "b");
  pkb.insertModifies(1, "c");
  pkb.insertModifies(1, "d");
  pkb.insertModifies(1, "ef");
  pkb.insertModifies(2, "a");
  pkb.insertModifies(2, "b");
  pkb.insertModifies(2, "c");
  pkb.insertModifies(2, "d");
  pkb.insertModifies(2, "ef");
  pkb.insertModifies(2, "ef");

  SECTION("Left to Right") {
    auto actual = pkb.getVarsModifiedByStmt(1);
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    std::string right = "a";
    auto actual = pkb.getStmtsThatModifyVar(right);
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }

  SECTION("getAllPairs") {
    auto actual = pkb.getAllVarModifiedByStmtPairs();
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "a"}, {1, "b"}, {1, "c"}, {1, "d"}, {1, "ef"},
        {2, "a"}, {2, "b"}, {2, "c"}, {2, "d"}, {2, "ef"}};
    REQUIRE(actual == expected);
  }
  SECTION("getAllStmtsThatModifyVars") {
    pkb.insertModifies(3, "g");
    std::unordered_set<int> actual = pkb.getAllStmtsThatModifyVars();
    std::unordered_set<int> expected = {1, 2, 3};
    REQUIRE(actual == expected);
  }
  SECTION("getAllVarsModifiedByStmts") {
    pkb.insertModifies(3, "g");
    std::unordered_set<std::string> actual = pkb.getAllVarsModifiedByStmts();
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef", "g"};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("PKB: Insert and Retrieve Relationships - Modifies Procedure") {
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  pkb.insertModifiesProcedure("main", "a");
  pkb.insertModifiesProcedure("main", "b");
  pkb.insertModifiesProcedure("main", "c");
  pkb.insertModifiesProcedure("main", "d");
  pkb.insertModifiesProcedure("main", "ef");
  pkb.insertModifiesProcedure("call", "a");
  pkb.insertModifiesProcedure("call", "b");
  pkb.insertModifiesProcedure("call", "c");
  pkb.insertModifiesProcedure("call", "d");
  pkb.insertModifiesProcedure("call", "ef");
  pkb.insertModifiesProcedure("call", "ef");

  SECTION("Left to Right") {
    std::string left = "main";
    auto actual = pkb.getVarsModifiedByProcedure(left);
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    std::string right = "ef";
    auto actual = pkb.getProceduresThatModifyVar(right);
    std::unordered_set<std::string> expected = {"main", "call"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllPairs") {
    auto actual = pkb.getAllVarModifiedByProcedurePairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"main", "a"},  {"main", "b"}, {"main", "c"}, {"main", "d"},
         {"main", "ef"}, {"call", "a"}, {"call", "b"}, {"call", "c"},
         {"call", "d"},  {"call", "ef"}};
    REQUIRE(actual == expected);
  }
  SECTION("getAllProceduresThatModifyVars") {
    pkb.insertModifiesProcedure("fun", "g");
    std::unordered_set<std::string> actual =
        pkb.getAllProceduresThatModifyVars();
    std::unordered_set<std::string> expected = {"main", "call", "fun"};
    REQUIRE(actual == expected);
  }
  SECTION("getAllVarsModifiedByProcedures") {
    pkb.insertModifiesProcedure("fun", "g");
    std::unordered_set<std::string> actual =
        pkb.getAllVarsModifiedByProcedures();
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef", "g"};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("PKB: Insert and Retrieve Relationships - Uses") {
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  pkb.insertUses(1, "a");
  pkb.insertUses(1, "b");
  pkb.insertUses(1, "c");
  pkb.insertUses(1, "d");
  pkb.insertUses(1, "ef");
  pkb.insertUses(2, "a");
  pkb.insertUses(2, "b");
  pkb.insertUses(2, "c");
  pkb.insertUses(2, "d");
  pkb.insertUses(2, "ef");
  pkb.insertUses(2, "ef");

  SECTION("Left to Right") {
    auto actual = pkb.getVarsUsedByStmt(1);
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    std::string right = "a";
    auto actual = pkb.getStmtsThatUseVar(right);
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }

  SECTION("getAllPairs") {
    auto actual = pkb.getAllVarUsedByStmtPairs();
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "a"}, {1, "b"}, {1, "c"}, {1, "d"}, {1, "ef"},
        {2, "a"}, {2, "b"}, {2, "c"}, {2, "d"}, {2, "ef"}};
    REQUIRE(actual == expected);
  }
  SECTION("getAllStmtsThatUseVars") {
    pkb.insertUses(3, "g");
    std::unordered_set<int> actual = pkb.getAllStmtsThatUseVars();
    std::unordered_set<int> expected = {1, 2, 3};
    REQUIRE(actual == expected);
  }
  SECTION("getAllVarsUsedByStmts") {
    pkb.insertUses(3, "g");
    std::unordered_set<std::string> actual = pkb.getAllVarsUsedByStmts();
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef", "g"};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("PKB: Insert and Retrieve Relationships - Uses Procedure") {
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  pkb.insertUsesProcedure("main", "a");
  pkb.insertUsesProcedure("main", "b");
  pkb.insertUsesProcedure("main", "c");
  pkb.insertUsesProcedure("main", "d");
  pkb.insertUsesProcedure("main", "ef");
  pkb.insertUsesProcedure("call", "a");
  pkb.insertUsesProcedure("call", "b");
  pkb.insertUsesProcedure("call", "c");
  pkb.insertUsesProcedure("call", "d");
  pkb.insertUsesProcedure("call", "ef");
  pkb.insertUsesProcedure("call", "ef");

  SECTION("Left to Right") {
    std::string left = "main";
    auto actual = pkb.getVarsUsedByProcedure(left);
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    std::string right = "ef";
    auto actual = pkb.getProceduresThatUseVar(right);
    std::unordered_set<std::string> expected = {"main", "call"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllPairs") {
    auto actual = pkb.getAllVarUsedByProcedurePairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"main", "a"},  {"main", "b"}, {"main", "c"}, {"main", "d"},
         {"main", "ef"}, {"call", "a"}, {"call", "b"}, {"call", "c"},
         {"call", "d"},  {"call", "ef"}};
    REQUIRE(actual == expected);
  }
  SECTION("getAllVarsUsedByProcedures") {
    std::unordered_set<std::string> actual = pkb.getAllVarsUsedByProcedures();
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    REQUIRE(actual == expected);
  }
  SECTION("getAllProceduresThatUseVars") {
    std::unordered_set<std::string> actual = pkb.getAllProceduresThatUseVars();
    std::unordered_set<std::string> expected = {"main", "call"};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("PKB:: Next Test") {
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  pkb.insertNextRelationship(1, 2);
  pkb.insertNextRelationship(2, 3);
  pkb.insertNextRelationship(3, 4);
  pkb.insertNextRelationship(4, 5);
  pkb.insertNextRelationship(5, 6);
  pkb.insertNextRelationship(6, 7);

  SECTION("expect previous and next values") {
    std::unordered_set<int> expectedSet1 = {1};
    std::unordered_set<int> expectedSet2 = {2};
    std::unordered_set<int> expectedSet3 = {3};

    REQUIRE(pkb.getStmtsPreviousOf(2) == expectedSet1);
    REQUIRE(pkb.getStmtsNextOf(1) == expectedSet2);
    REQUIRE(pkb.getStmtsNextOf(1) != expectedSet3);
    REQUIRE(pkb.getStmtsPreviousOf(1) != expectedSet2);
  }

  SECTION("expect all next pairs") {
    std::unordered_set<std::pair<int, int>, PairHash> actual =
        pkb.getAllNextPairs();

    std::unordered_set<std::pair<int, int>, PairHash> expected = {
        {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}};
    REQUIRE(actual == expected);
  }

  SECTION("getAllStmtsThatAreNextOfOtherStmts") {
    std::unordered_set<int> actual = pkb.getAllStmtsThatAreNextOfOtherStmts();
    std::unordered_set<int> expected = {2, 3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }

  SECTION("getAllStmtsThatArePreviousOfOtherStmts") {
    std::unordered_set<int> actual =
        pkb.getAllStmtsThatArePreviousOfOtherStmts();
    std::unordered_set<int> expected = {1, 2, 3, 4, 5, 6};
    REQUIRE(actual == expected);
  }
}