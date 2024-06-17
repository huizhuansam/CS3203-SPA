#include <unordered_set>

#include "ReadFacade.h"
#include "WriteFacade.h"
#include "catch.hpp"

TEST_CASE("Facade: Insert and Retrieve Entities") {
  ReadFacade rf = ReadFacade();
  WriteFacade wf = WriteFacade();
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  SECTION("Constants") {
    std::string str1 = "x";
    std::string str2 = "1";
    std::string str3 = "TESTING!@#";

    wf.addConstant(str1);
    wf.addConstant(str2);
    wf.addConstant(str3);

    std::unordered_set<std::string> test = {"x", "1", "TESTING!@#"};

    REQUIRE(rf.getAllConstants() == test);
  }

  SECTION("Variables") {
    std::string str1 = "Yishun";
    std::string str2 = "count";
    std::string str3 = "Mario";

    wf.addVariable(str1);
    wf.addVariable(str2);
    wf.addVariable(str3);

    std::unordered_set<std::string> test = {"Yishun", "count", "Mario"};
    REQUIRE(rf.getAllVariables() == test);
  }

  SECTION("Procedures") {
    std::string str1 = "computeCentroids";
    std::string str2 = "printCentrals";
    std::string str3 = "deleteAll";

    wf.addProcedure(str1);
    wf.addProcedure(str2);
    wf.addProcedure(str3);

    std::unordered_set<std::string> test = {"computeCentroids", "printCentrals",
                                            "deleteAll"};
    REQUIRE(rf.getAllProcedures() == test);
  }
}

TEST_CASE("Facade: Stmt Mapped to Ident") {
  ReadFacade rf = ReadFacade();
  WriteFacade wf = WriteFacade();
  wf.clearPKB();

  wf.insertStmtCallsProc(1, "first");
  wf.insertStmtCallsProc(2, "second");
  wf.insertStmtCallsProc(3, "second");
  wf.insertStmtCallsProc(4, "third");

  wf.insertStmtPrintsVar(5, "v");
  wf.insertStmtPrintsVar(6, "x");
  wf.insertStmtPrintsVar(7, "y");

  wf.insertStmtReadsVar(8, "v");
  wf.insertStmtReadsVar(9, "x");
  wf.insertStmtReadsVar(10, "z");

  SECTION("Check Stmt Number Mapped to Call") {
    std::string expected = "first";
    REQUIRE(expected == rf.getProcCalledByStmt(1));
  }

  SECTION("getAllStmtsThatCallProc") {
    std::unordered_set<int> expected = {2, 3};
    std::string input = "second";
    REQUIRE(expected == rf.getAllStmtsThatCallProc(input));
  }

  SECTION("getAllCallsProcPairs") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "first"}, {2, "second"}, {3, "second"}, {4, "third"}};
    REQUIRE(expected == rf.getAllCallsProcPairs());
  }

  SECTION("getAllProceduresCalledByStmts") {
    std::unordered_set<std::string> expected = {"first", "second", "third"};
    REQUIRE(expected == rf.getAllProceduresCalledByStmts());
  }

  SECTION("Check Stmt Number Mapped to Print") {
    std::string expected = "v";
    REQUIRE(expected == rf.getVarPrintedByStmt(5));
  }

  SECTION("getAllStmtsThatPrintVar") {
    std::unordered_set<int> expected = {5};
    std::string input = "v";
    REQUIRE(expected == rf.getAllStmtsThatPrintVar(input));
  }

  SECTION("getAllPrintVarPairs") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {5, "v"}, {6, "x"}, {7, "y"}};
    REQUIRE(expected == rf.getAllPrintVarPairs());
  }

  SECTION("getAllRights()") {
    std::unordered_set<std::string> expected = {"v", "x", "y"};
    REQUIRE(expected == rf.getAllVarsPrintByStmts());
  }

  SECTION("Check Stmt Number Mapped to Read") {
    std::string expected = "v";
    REQUIRE(expected == rf.getVarReadByStmt(8));
  }

  SECTION("getAllStmtsThatReadVar") {
    std::unordered_set<int> expected = {9};
    std::string input = "x";
    REQUIRE(expected == rf.getAllStmtsThatReadVar(input));
  }

  SECTION("getAllReadVarPairs") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {8, "v"}, {9, "x"}, {10, "z"}};
    REQUIRE(expected == rf.getAllReadVarPairs());
  }

  SECTION("getAllVarsReadByStmts") {
    std::unordered_set<std::string> expected = {"v", "x", "z"};
    REQUIRE(expected == rf.getAllVarsReadByStmts());
  }
}

TEST_CASE("Facade : Assign Expression Store check") {
  ReadFacade rf = ReadFacade();
  WriteFacade wf = WriteFacade();
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  wf.addAssignExpPattern(1, "test", {"y", "*", "5"});
  wf.addAssignExpPattern(2, "Yishun", {"Serangoon", "*", "2"});
  wf.addAssignExpPattern(4, "philo", {"a", "/", "2"});
  wf.addAssignExpPattern(5, "this_mod", {"time", "*", "0"});
  wf.addAssignExpPattern(6, "test",
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
  wf.addAssignExpPattern(7, "test", {"x", "*", "y"});

  SECTION("Check getAllExpPairs()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {{"1", "test"},     {"2", "Yishun"}, {"4", "philo"},
                          {"5", "this_mod"}, {"6", "test"},   {"7", "test"}};
    auto actualVector = rf.getAllAssignExpPairs();

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getAssignExpPairsPartialMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {{"1", "test"}, {"6", "test"}};

    auto actualVector =
        rf.getAssignExpPairsPartialMatch("test", {"y", "*", "5"});

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getAssignExpPairsSynonymPartialMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {
            {"4", "philo"},
            {"6", "test"},
        };

    auto actualVector =
        rf.getAssignExpPairsSynonymPartialMatch({"a", "/", "2"});

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getAssignExpPairsExactMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {{"1", "test"}};

    auto actualVector = rf.getAssignExpPairsExactMatch("test", {"y", "*", "5"});

    REQUIRE(actualVector == expectedVector);
  }

  SECTION("Check getAssignExpPairsSynonymExactMatch()") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash>
        expectedVector = {
            {"4", "philo"},
        };

    auto actualVector = rf.getAssignExpPairsSynonymExactMatch({"a", "/", "2"});

    REQUIRE(actualVector == expectedVector);
  }
}

TEST_CASE("Facade: Check While Pattern Store") {
  ReadFacade rf = ReadFacade();
  WriteFacade wf = WriteFacade();
  PKB& pkb = PKB::getPKB();
  pkb.clear();

  wf.addWhileControlVariable(1, "a");
  wf.addWhileControlVariable(1, "c");
  wf.addWhileControlVariable(2, "a");
  wf.addWhileControlVariable(3, "a");
  wf.addWhileControlVariable(4, "A");
  wf.addWhileControlVariable(5, "b");
  wf.addWhileControlVariable(6, "c");

  SECTION("Check getControlVariableOfWhileStmt()") {
    std::unordered_set<std::string> expected = {"a", "c"};
    std::unordered_set<std::string> actual =
        rf.getControlVariableOfWhileStmt(1);

    REQUIRE(actual == expected);
  }

  SECTION("Check getWhileStmtsThatUseControlVariable()") {
    std::unordered_set<int> expected = {1, 2, 3};
    std::unordered_set<int> actual =
        rf.getWhileStmtsThatUseControlVariable("a");

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllWhileControlVariablePairs()") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "a"}, {1, "c"}, {2, "a"}, {3, "a"}, {4, "A"}, {5, "b"}, {6, "c"}};
    std::unordered_set<std::pair<int, std::string>, PairHash> actual =
        rf.getAllWhileControlVariablePairs();

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllWhileStmtsThatUseControlVariables()") {
    std::unordered_set<int> expected = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> actual =
        rf.getAllWhileStmtsThatUseControlVariables();

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllWhileControlVariables()") {
    std::unordered_set<std::string> expected = {"a", "A", "b", "c"};
    std::unordered_set<std::string> actual = rf.getAllWhileControlVariables();

    REQUIRE(actual == expected);
  }
}

TEST_CASE("Facade: Check If Pattern Store") {
  ReadFacade rf = ReadFacade();
  WriteFacade wf = WriteFacade();
  PKB& pkb = PKB::getPKB();
  pkb.clear();

  wf.addIfControlVariable(1, "a");
  wf.addIfControlVariable(1, "b");
  wf.addIfControlVariable(2, "a");
  wf.addIfControlVariable(3, "a");
  wf.addIfControlVariable(4, "A");
  wf.addIfControlVariable(5, "b");
  wf.addIfControlVariable(6, "c");

  SECTION("Check getControlVariableOfIfStmt()") {
    std::unordered_set<std::string> expected = {"a", "b"};
    std::unordered_set<std::string> actual = rf.getControlVariableOfIfStmt(1);

    REQUIRE(actual == expected);
  }

  SECTION("Check getIfStmtsThatUseControlVariable()") {
    std::unordered_set<int> expected = {1, 2, 3};
    std::unordered_set<int> actual = rf.getIfStmtsThatUseControlVariable("a");

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllIfControlVariablePairs()") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "a"}, {1, "b"}, {2, "a"}, {3, "a"}, {4, "A"}, {5, "b"}, {6, "c"}};
    std::unordered_set<std::pair<int, std::string>, PairHash> actual =
        rf.getAllIfControlVariablePairs();

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllIfStmtsThatUseControlVariables()") {
    std::unordered_set<int> expected = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> actual = rf.getAllIfStmtsThatUseControlVariables();

    REQUIRE(actual == expected);
  }

  SECTION("Check getAllIfControlVariables()") {
    std::unordered_set<std::string> expected = {"a", "A", "b", "c"};
    std::unordered_set<std::string> actual = rf.getAllIfControlVariables();

    REQUIRE(actual == expected);
  }
}

TEST_CASE("Facade: Insert and Retrieve Parents") {
  ReadFacade rf = ReadFacade();
  WriteFacade wf = WriteFacade();
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  int parent = 1;
  int child = 2;
  wf.insertDirectParentChildRelationship(parent, child);
  SECTION("Left to Right") {
    auto actual = rf.getChildren(parent);
    std::unordered_set<int> expected;
    expected.insert(child);
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    auto actual = rf.getParent(child);
    int expected = parent;
    REQUIRE(actual == expected);
  }
  wf.insertParentStarRelationship(1, 2);
  wf.insertParentStarRelationship(1, 3);
  wf.insertParentStarRelationship(1, 4);
  wf.insertParentStarRelationship(1, 5);
  wf.insertParentStarRelationship(1, 6);
  wf.insertParentStarRelationship(1, 7);
  wf.insertParentStarRelationship(2, 3);
  wf.insertParentStarRelationship(2, 4);
  wf.insertParentStarRelationship(2, 5);
  wf.insertParentStarRelationship(2, 6);
  wf.insertParentStarRelationship(2, 7);
  wf.insertParentStarRelationship(2, 7);
  wf.insertParentStarRelationship(2, 7);

  wf.insertDirectParentChildRelationship(2, 3);
  wf.insertDirectParentChildRelationship(2, 4);
  wf.insertDirectParentChildRelationship(2, 5);
  wf.insertDirectParentChildRelationship(2, 6);
  wf.insertDirectParentChildRelationship(2, 7);

  SECTION("getAllParentPairs") {
    std::unordered_set<std::pair<int, int>, PairHash> actual =
        rf.getAllParentPairs();
    std::unordered_set<std::pair<int, int>, PairHash> expected = {
        {1, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}};
    REQUIRE(actual == expected);
  }
  SECTION("getAllParentStarPairs") {
    std::unordered_set<std::pair<int, int>, PairHash> actual =
        rf.getAllParentStarPairs();
    std::unordered_set<std::pair<int, int>, PairHash> expected = {
        {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7},
        {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}};
    REQUIRE(actual == expected);
  }

  SECTION("getChildrenStar") {
    auto actual = rf.getChildrenStar(1);
    std::unordered_set<int> expected = {2, 3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }

  SECTION("getParentsStar") {
    auto actual = rf.getParentStar(3);
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }

  SECTION("getAllParents") {
    std::unordered_set<int> actual = rf.getAllParents();
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }
  SECTION("getAllChildren") {
    std::unordered_set<int> actual = rf.getAllChildren();
    std::unordered_set<int> expected = {2, 3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Facade: Insert and Retrieve Follows") {
  ReadFacade rf = ReadFacade();
  WriteFacade wf = WriteFacade();
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  wf.insertFollowsStarRelationship(1, 3);
  wf.insertFollowsStarRelationship(1, 2);
  wf.insertFollowsStarRelationship(1, 7);
  wf.insertFollowsStarRelationship(1, 4);
  wf.insertFollowsStarRelationship(1, 5);
  wf.insertFollowsStarRelationship(1, 6);
  wf.insertFollowsStarRelationship(2, 6);
  wf.insertFollowsStarRelationship(2, 3);
  wf.insertFollowsStarRelationship(2, 7);
  wf.insertFollowsStarRelationship(2, 4);
  wf.insertFollowsStarRelationship(2, 5);
  wf.insertDirectFollowsRelationship(1, 2);
  wf.insertDirectFollowsRelationship(2, 3);

  SECTION("expect direct follows relationship values") {
    REQUIRE(rf.getStmtThatFollowsBefore(2) == 1);
    REQUIRE(rf.getStmtThatFollowsAfter(1) == 2);
    REQUIRE(rf.getStmtThatFollowsBefore(1) != 2);
  }

  SECTION("expect all follows pairs") {
    std::unordered_set<std::pair<int, int>, PairHash> actual =
        rf.getAllFollowPairs();

    std::unordered_set<std::pair<int, int>, PairHash> expected = {{1, 2},
                                                                  {2, 3}};

    REQUIRE(actual == expected);
  }

  SECTION("expect all follows star pairs") {
    std::unordered_set<std::pair<int, int>, PairHash> actual =
        rf.getAllFollowStarPairs();

    std::unordered_set<std::pair<int, int>, PairHash> expected = {
        {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7},
        {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}};
    REQUIRE(actual == expected);
  }

  SECTION("before to after follows star") {
    auto actual = rf.getAllStmtsThatFollowAfter(1);
    std::unordered_set<int> expected = {2, 3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }

  SECTION("after to before follows star") {
    auto actual = rf.getAllStmtsThatFollowBefore(3);
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }
  SECTION("getAllStmtsThatFollowAfterOtherStmts") {
    std::unordered_set<int> actual = rf.getAllStmtsThatFollowBeforeOtherStmts();
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }
  SECTION("getAllStmtsThatFollowAfterOtherStmts") {
    std::unordered_set<int> actual = rf.getAllStmtsThatFollowAfterOtherStmts();
    std::unordered_set<int> expected = {2, 3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Facade: Insert and Retrieve Relationships - Calls") {
  ReadFacade rf = ReadFacade();
  WriteFacade wf = WriteFacade();
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  std::string source = "First";
  std::string target = "Second";
  wf.insertCallsRelationship(source, target);

  SECTION("Left to Right") {
    auto actual = rf.getProcsThatIsCalledBy(source);
    std::unordered_set<std::string> expected;
    expected.insert(target);
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    auto actual = rf.getProcsThatCalls(target);
    std::unordered_set<std::string> expected;
    expected.insert(source);
    REQUIRE(actual == expected);
  }

  wf.insertCallsRelationship("First", "Second");
  wf.insertCallsRelationship("Second", "Third");
  wf.insertCallsRelationship("Second", "Fourth");
  wf.insertCallsRelationship("Second", "Fifth");
  wf.insertCallsRelationship("Second", "Sixth");
  wf.insertCallsRelationship("Second", "Seventh");
  wf.insertCallsRelationship("Second", "Seventh");
  wf.insertCallsRelationship("Second", "Seventh");

  SECTION("getAllCallPairs") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash> actual =
        rf.getAllCallPairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"First", "Second"}, {"Second", "Third"}, {"Second", "Fourth"},
         {"Second", "Fifth"}, {"Second", "Sixth"}, {"Second", "Seventh"}};

    REQUIRE(actual == expected);
  }

  SECTION("getAllCallStarPairs") {
    auto actual = rf.getAllCallStarPairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"First", "Second"}, {"First", "Third"},   {"First", "Fourth"},
         {"First", "Fifth"},  {"First", "Sixth"},   {"First", "Seventh"},
         {"Second", "Third"}, {"Second", "Fourth"}, {"Second", "Fifth"},
         {"Second", "Sixth"}, {"Second", "Seventh"}};

    REQUIRE(actual == expected);
  }

  SECTION("getProcsThatIsCalledByStar") {
    std::string first = "First";
    auto actual = rf.getProcsThatIsCalledByStar(first);
    std::unordered_set<std::string> expected = {"Second", "Third", "Fourth",
                                                "Fifth",  "Sixth", "Seventh"};
    REQUIRE(actual == expected);
  }

  SECTION("getProcsThatCallsStar") {
    std::string third = "Third";
    auto actual = rf.getProcsThatCallsStar(third);
    std::unordered_set<std::string> expected = {"First", "Second"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllProcsThatCallOtherProcs") {
    std::unordered_set<std::string> actual = rf.getAllProcsThatCallOtherProcs();
    std::unordered_set<std::string> expected = {"First", "Second"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllProcsThatGetCalledByOtherProcs") {
    std::unordered_set<std::string> actual =
        rf.getAllProcsThatGetCalledByOtherProcs();
    std::unordered_set<std::string> expected = {"Second", "Third", "Fourth",
                                                "Fifth",  "Sixth", "Seventh"};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("WriteFacade: Updated Call Test") {
  ReadFacade rf = ReadFacade();
  WriteFacade wf = WriteFacade();
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  std::string source = "First";
  std::string target = "Second";
  wf.insertCallsRelationship(source, target);

  SECTION("Left to Right") {
    auto actual = rf.getProcsThatIsCalledBy(source);
    std::unordered_set<std::string> expected;
    expected.insert(target);
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    auto actual = rf.getProcsThatCalls(target);
    std::unordered_set<std::string> expected;
    expected.insert(source);
    REQUIRE(actual == expected);
  }

  wf.insertCallsRelationship("Second", "Third");
  wf.insertCallsRelationship("Second", "Fourth");
  wf.insertCallsRelationship("Second", "Fifth");
  wf.insertCallsRelationship("Second", "Sixth");
  wf.insertCallsRelationship("Second", "Seventh");
  wf.insertCallsRelationship("Second", "Seventh");
  wf.insertCallsRelationship("Second", "Seventh");

  SECTION("getAllCallPairs") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash> actual =
        rf.getAllCallPairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"First", "Second"}, {"Second", "Third"}, {"Second", "Fourth"},
         {"Second", "Fifth"}, {"Second", "Sixth"}, {"Second", "Seventh"}};

    REQUIRE(actual == expected);
  }

  SECTION("getAllCallStarPairs") {
    auto actual = rf.getAllCallStarPairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"First", "Second"}, {"First", "Third"},   {"First", "Fourth"},
         {"First", "Fifth"},  {"First", "Sixth"},   {"First", "Seventh"},
         {"Second", "Third"}, {"Second", "Fourth"}, {"Second", "Fifth"},
         {"Second", "Sixth"}, {"Second", "Seventh"}};

    REQUIRE(actual == expected);
  }

  SECTION("getProcsThatIsCalledByStar") {
    std::string first = "First";
    auto actual = rf.getProcsThatIsCalledByStar(first);
    std::unordered_set<std::string> expected = {"Second", "Third", "Fourth",
                                                "Fifth",  "Sixth", "Seventh"};
    REQUIRE(actual == expected);
  }

  SECTION("getProcsThatCallsStar") {
    std::string third = "Third";
    auto actual = rf.getProcsThatCallsStar(third);
    std::unordered_set<std::string> expected = {"First", "Second"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllProcsThatCallOtherProcs") {
    std::unordered_set<std::string> actual = rf.getAllProcsThatCallOtherProcs();
    std::unordered_set<std::string> expected = {"First", "Second"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllProcsThatGetCalledByOtherProcs") {
    std::unordered_set<std::string> actual =
        rf.getAllProcsThatGetCalledByOtherProcs();
    std::unordered_set<std::string> expected = {"Second", "Third", "Fourth",
                                                "Fifth",  "Sixth", "Seventh"};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Facade: Insert and Retrieve Modifies") {
  ReadFacade rf = ReadFacade();
  WriteFacade wf = WriteFacade();
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  wf.insertModifies(1, "a");
  wf.insertModifies(1, "b");
  wf.insertModifies(1, "c");
  wf.insertModifies(1, "d");
  wf.insertModifies(1, "ef");
  wf.insertModifies(2, "a");
  wf.insertModifies(2, "b");
  wf.insertModifies(2, "c");
  wf.insertModifies(2, "d");
  wf.insertModifies(2, "ef");
  wf.insertModifies(2, "ef");

  SECTION("Left to Right") {
    auto actual = rf.getVarsModifiedByStmt(1);
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    std::string right = "a";
    auto actual = rf.getStmtsThatModifyVar(right);
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }

  SECTION("getAllPairs") {
    auto actual = rf.getAllVarModifiedByStmtPairs();
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "a"}, {1, "b"}, {1, "c"}, {1, "d"}, {1, "ef"},
        {2, "a"}, {2, "b"}, {2, "c"}, {2, "d"}, {2, "ef"}};
    REQUIRE(actual == expected);
  }
  SECTION("getAllStmtsThatModifyVars") {
    wf.insertModifies(3, "g");
    std::unordered_set<int> actual = rf.getAllStmtsThatModifyVars();
    std::unordered_set<int> expected = {1, 2, 3};
    REQUIRE(actual == expected);
  }
  SECTION("getAllVarsModifiedByStmts") {
    wf.insertModifies(3, "g");
    std::unordered_set<std::string> actual = rf.getAllVarsModifiedByStmts();
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef", "g"};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Facade: Insert and Retrieve Modifies Procedure") {
  ReadFacade rf = ReadFacade();
  WriteFacade wf = WriteFacade();
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  wf.insertModifiesProcedure("main", "a");
  wf.insertModifiesProcedure("main", "b");
  wf.insertModifiesProcedure("main", "c");
  wf.insertModifiesProcedure("main", "d");
  wf.insertModifiesProcedure("main", "ef");
  wf.insertModifiesProcedure("call", "a");
  wf.insertModifiesProcedure("call", "b");
  wf.insertModifiesProcedure("call", "c");
  wf.insertModifiesProcedure("call", "d");
  wf.insertModifiesProcedure("call", "ef");
  wf.insertModifiesProcedure("call", "ef");

  SECTION("Left to Right") {
    std::string left = "main";
    auto actual = rf.getVarsModifiedByProcedure(left);
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    std::string right = "ef";
    auto actual = rf.getProceduresThatModifyVar(right);
    std::unordered_set<std::string> expected = {"main", "call"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllVarModifiedByProcedurePairs") {
    auto actual = rf.getAllVarModifiedByProcedurePairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"main", "a"},  {"main", "b"}, {"main", "c"}, {"main", "d"},
         {"main", "ef"}, {"call", "a"}, {"call", "b"}, {"call", "c"},
         {"call", "d"},  {"call", "ef"}};
    REQUIRE(actual == expected);
  }
  SECTION("getAllProceduresThatModifyVars") {
    wf.insertModifiesProcedure("fun", "g");
    std::unordered_set<std::string> actual =
        rf.getAllProceduresThatModifyVars();
    std::unordered_set<std::string> expected = {"main", "call", "fun"};
    REQUIRE(actual == expected);
  }
  SECTION("getAllVarsModifiedByProcedures") {
    wf.insertModifiesProcedure("fun", "g");
    std::unordered_set<std::string> actual =
        rf.getAllVarsModifiedByProcedures();
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef", "g"};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Facade: Insert and Retrieve Uses") {
  ReadFacade rf = ReadFacade();
  WriteFacade wf = WriteFacade();
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  wf.insertUses(1, "a");
  wf.insertUses(1, "b");
  wf.insertUses(1, "c");
  wf.insertUses(1, "d");
  wf.insertUses(1, "ef");
  wf.insertUses(2, "a");
  wf.insertUses(2, "b");
  wf.insertUses(2, "c");
  wf.insertUses(2, "d");
  wf.insertUses(2, "ef");
  wf.insertUses(2, "ef");

  SECTION("Left to Right") {
    auto actual = rf.getVarsUsedByStmt(1);
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    std::string right = "a";
    auto actual = rf.getStmtsThatUseVar(right);
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }

  SECTION("getAllPairs") {
    auto actual = rf.getAllVarUsedByStmtPairs();
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "a"}, {1, "b"}, {1, "c"}, {1, "d"}, {1, "ef"},
        {2, "a"}, {2, "b"}, {2, "c"}, {2, "d"}, {2, "ef"},
    };
    REQUIRE(actual == expected);
  }
  SECTION("getAllStmtsThatUseVars") {
    wf.insertUses(3, "g");
    std::unordered_set<int> actual = rf.getAllStmtsThatUseVars();
    std::unordered_set<int> expected = {1, 2, 3};
    REQUIRE(actual == expected);
  }
  SECTION("getAllVarsUsedByStmts") {
    wf.insertUses(3, "g");
    std::unordered_set<std::string> actual = rf.getAllVarsUsedByStmts();
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef", "g"};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Facade: Insert and Retrieve Uses Procedure") {
  ReadFacade rf = ReadFacade();
  WriteFacade wf = WriteFacade();
  PKB& pkb = PKB::getPKB();
  pkb.clear();
  wf.insertUsesProcedure("main", "a");
  wf.insertUsesProcedure("main", "b");
  wf.insertUsesProcedure("main", "c");
  wf.insertUsesProcedure("main", "d");
  wf.insertUsesProcedure("main", "ef");
  wf.insertUsesProcedure("call", "a");
  wf.insertUsesProcedure("call", "b");
  wf.insertUsesProcedure("call", "c");
  wf.insertUsesProcedure("call", "d");
  wf.insertUsesProcedure("call", "ef");
  wf.insertUsesProcedure("call", "ef");

  SECTION("Left to Right") {
    std::string left = "main";
    auto actual = rf.getVarsUsedByProcedure(left);
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    std::string right = "ef";
    auto actual = rf.getProceduresThatUseVar(right);
    std::unordered_set<std::string> expected = {"main", "call"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllPairs") {
    auto actual = rf.getAllVarUsedByProcedurePairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"main", "a"},  {"main", "b"}, {"main", "c"}, {"main", "d"},
         {"main", "ef"}, {"call", "a"}, {"call", "b"}, {"call", "c"},
         {"call", "d"},  {"call", "ef"}};
    REQUIRE(actual == expected);
  }

  SECTION("getAllVarsUsedByProcedures") {
    std::unordered_set<std::string> actual = rf.getAllVarsUsedByProcedures();
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    REQUIRE(actual == expected);
  }
  SECTION("getAllProceduresThatUseVars") {
    std::unordered_set<std::string> actual = rf.getAllProceduresThatUseVars();
    std::unordered_set<std::string> expected = {"main", "call"};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Facade:: Next Test") {
  ReadFacade rf = ReadFacade();
  WriteFacade wf = WriteFacade();
  wf.clearPKB();
  wf.insertNextRelationship(1, 2);
  wf.insertNextRelationship(2, 3);
  wf.insertNextRelationship(3, 4);
  wf.insertNextRelationship(4, 5);
  wf.insertNextRelationship(5, 6);
  wf.insertNextRelationship(6, 7);

  SECTION("expect previous and next values") {
    std::unordered_set<int> expectedSet1 = {1};
    std::unordered_set<int> expectedSet2 = {2};
    std::unordered_set<int> expectedSet3 = {3};

    REQUIRE(rf.getStmtsPreviousOf(2) == expectedSet1);
    REQUIRE(rf.getStmtsNextOf(1) == expectedSet2);
    REQUIRE(rf.getStmtsNextOf(1) != expectedSet3);
    REQUIRE(rf.getStmtsPreviousOf(1) != expectedSet2);
  }

  SECTION("expect all next pairs") {
    std::unordered_set<std::pair<int, int>, PairHash> actual =
        rf.getAllNextPairs();

    std::unordered_set<std::pair<int, int>, PairHash> expected = {
        {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}};
    REQUIRE(actual == expected);
  }

  SECTION("getAllStmtsThatAreNextOfOtherStmts") {
    std::unordered_set<int> actual = rf.getAllStmtsThatAreNextOfOtherStmts();
    std::unordered_set<int> expected = {2, 3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }

  SECTION("getAllStmtsThatArePreviousOfOtherStmts") {
    std::unordered_set<int> actual =
        rf.getAllStmtsThatArePreviousOfOtherStmts();
    std::unordered_set<int> expected = {1, 2, 3, 4, 5, 6};
    REQUIRE(actual == expected);
  }
}