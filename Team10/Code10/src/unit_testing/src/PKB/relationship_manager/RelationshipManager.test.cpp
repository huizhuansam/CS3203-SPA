#include "RelationshipManager.h"

#include <algorithm>

#include "catch.hpp"

TEST_CASE("Parent Test") {
  RelationshipManager manager;
  int parent = 1;
  int child = 2;
  manager.insertDirectParentChildRelationship(parent, child);
  SECTION("Left to Right") {
    auto actual = manager.getChildren(parent);
    std::unordered_set<int> expected;
    expected.insert(child);
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    auto actual = manager.getParent(child);
    int expected = parent;
    REQUIRE(actual == expected);
  }
  manager.insertParentStarRelationship(1, 2);
  manager.insertParentStarRelationship(1, 3);
  manager.insertParentStarRelationship(1, 4);
  manager.insertParentStarRelationship(1, 5);
  manager.insertParentStarRelationship(1, 6);
  manager.insertParentStarRelationship(1, 7);
  manager.insertParentStarRelationship(2, 3);
  manager.insertParentStarRelationship(2, 4);
  manager.insertParentStarRelationship(2, 5);
  manager.insertParentStarRelationship(2, 6);
  manager.insertParentStarRelationship(2, 7);
  manager.insertParentStarRelationship(2, 7);
  manager.insertParentStarRelationship(2, 7);

  manager.insertDirectParentChildRelationship(2, 3);
  manager.insertDirectParentChildRelationship(2, 4);
  manager.insertDirectParentChildRelationship(2, 5);
  manager.insertDirectParentChildRelationship(2, 6);
  manager.insertDirectParentChildRelationship(2, 7);

  SECTION("getAllParentPairs") {
    std::unordered_set<std::pair<int, int>, PairHash> actual =
        manager.getAllParentPairs();
    std::unordered_set<std::pair<int, int>, PairHash> expected = {
        {1, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}};
    REQUIRE(actual == expected);
  }

  SECTION("getAllParentStarPairs") {
    auto actual = manager.getAllParentStarPairs();
    std::unordered_set<std::pair<int, int>, PairHash> expected = {
        {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7},
        {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}};
    REQUIRE(actual == expected);
  }

  SECTION("getChildrenStar") {
    auto actual = manager.getChildrenStar(1);
    std::unordered_set<int> expected = {2, 3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }

  SECTION("getParentsStar") {
    auto actual = manager.getParentStar(3);
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }

  SECTION("getAllParents") {
    std::unordered_set<int> actual = manager.getAllParents();
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }

  SECTION("getAllChildren") {
    std::unordered_set<int> actual = manager.getAllChildren();
    std::unordered_set<int> expected = {2, 3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Follows Test") {
  RelationshipManager manager;
  manager.insertFollowsStarRelationship(1, 3);
  manager.insertFollowsStarRelationship(1, 2);
  manager.insertFollowsStarRelationship(1, 7);
  manager.insertFollowsStarRelationship(1, 4);
  manager.insertFollowsStarRelationship(1, 5);
  manager.insertFollowsStarRelationship(1, 6);
  manager.insertFollowsStarRelationship(2, 6);
  manager.insertFollowsStarRelationship(2, 3);
  manager.insertFollowsStarRelationship(2, 7);
  manager.insertFollowsStarRelationship(2, 4);
  manager.insertFollowsStarRelationship(2, 5);

  manager.insertDirectFollowsRelationship(1, 2);
  manager.insertDirectFollowsRelationship(2, 3);

  SECTION("expect direct follows relationship values") {
    REQUIRE(manager.getStmtThatFollowsBefore(2) == 1);
    REQUIRE(manager.getStmtThatFollowsAfter(1) == 2);
    REQUIRE(manager.getStmtThatFollowsBefore(1) != 2);
  }

  SECTION("expect all follows pairs") {
    std::unordered_set<std::pair<int, int>, PairHash> actual =
        manager.getAllFollowPairs();

    std::unordered_set<std::pair<int, int>, PairHash> expected = {{1, 2},
                                                                  {2, 3}};
    REQUIRE(actual == expected);
  }

  SECTION("expect all follows star pairs") {
    auto actual = manager.getAllFollowStarPairs();

    std::unordered_set<std::pair<int, int>, PairHash> expected = {
        {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7},
        {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}};
    REQUIRE(actual == expected);
  }

  SECTION("before to after follows star") {
    auto actual = manager.getAllStmtsThatFollowAfter(1);
    std::unordered_set<int> expected = {2, 3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }

  SECTION("after to before follows star") {
    auto actual = manager.getAllStmtsThatFollowBefore(3);
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }

  SECTION("getAllStmtsThatFollowAfterOtherStmts") {
    std::unordered_set<int> actual =
        manager.getAllStmtsThatFollowBeforeOtherStmts();
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }

  SECTION("getAllStmtsThatFollowAfterOtherStmts") {
    std::unordered_set<int> actual =
        manager.getAllStmtsThatFollowAfterOtherStmts();
    std::unordered_set<int> expected = {2, 3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Next Test") {
  RelationshipManager manager;
  manager.insertNextRelationship(1, 2);
  manager.insertNextRelationship(2, 3);
  manager.insertNextRelationship(3, 4);
  manager.insertNextRelationship(4, 5);
  manager.insertNextRelationship(5, 6);
  manager.insertNextRelationship(6, 7);

  SECTION("expect previous and next values") {
    std::unordered_set<int> expectedSet1 = {1};
    std::unordered_set<int> expectedSet2 = {2};
    std::unordered_set<int> expectedSet3 = {3};

    REQUIRE(manager.getStmtsPreviousOf(2) == expectedSet1);
    REQUIRE(manager.getStmtsNextOf(1) == expectedSet2);
    REQUIRE(manager.getStmtsNextOf(1) != expectedSet3);
    REQUIRE(manager.getStmtsPreviousOf(1) != expectedSet2);
  }

  SECTION("expect all next pairs") {
    std::unordered_set<std::pair<int, int>, PairHash> actual =
        manager.getAllNextPairs();

    std::unordered_set<std::pair<int, int>, PairHash> expected = {
        {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}};
    REQUIRE(actual == expected);
  }

  SECTION("getAllStmtsThatAreNextOfOtherStmts") {
    std::unordered_set<int> actual =
        manager.getAllStmtsThatAreNextOfOtherStmts();
    std::unordered_set<int> expected = {2, 3, 4, 5, 6, 7};
    REQUIRE(actual == expected);
  }

  SECTION("getAllStmtsThatArePreviousOfOtherStmts") {
    std::unordered_set<int> actual =
        manager.getAllStmtsThatArePreviousOfOtherStmts();
    std::unordered_set<int> expected = {1, 2, 3, 4, 5, 6};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Call Test") {
  RelationshipManager manager;
  std::string source = "First";
  std::string target = "Second";
  manager.insertCallsRelationship(source, target);

  SECTION("Left to Right") {
    auto actual = manager.getProcsThatIsCalledBy(source);
    std::unordered_set<std::string> expected;
    expected.insert(target);
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    auto actual = manager.getProcsThatCalls(target);
    std::unordered_set<std::string> expected;
    expected.insert(source);
    REQUIRE(actual == expected);
  }

  manager.insertCallsRelationship("First", "Second");
  manager.insertCallsRelationship("Second", "Third");
  manager.insertCallsRelationship("Second", "Fourth");
  manager.insertCallsRelationship("Second", "Fifth");
  manager.insertCallsRelationship("Second", "Sixth");
  manager.insertCallsRelationship("Second", "Seventh");
  manager.insertCallsRelationship("Second", "Seventh");
  manager.insertCallsRelationship("Second", "Seventh");

  SECTION("getAllCallPairs") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash> actual =
        manager.getAllCallPairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"First", "Second"}, {"Second", "Third"}, {"Second", "Fourth"},
         {"Second", "Fifth"}, {"Second", "Sixth"}, {"Second", "Seventh"}};

    REQUIRE(actual == expected);
  }

  SECTION("getAllCallStarPairs") {
    auto actual = manager.getAllCallStarPairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"First", "Second"}, {"First", "Third"},   {"First", "Fourth"},
         {"First", "Fifth"},  {"First", "Sixth"},   {"First", "Seventh"},
         {"Second", "Third"}, {"Second", "Fourth"}, {"Second", "Fifth"},
         {"Second", "Sixth"}, {"Second", "Seventh"}};

    REQUIRE(actual == expected);
  }

  SECTION("getProcsThatIsCalledByStar") {
    std::string first = "First";
    auto actual = manager.getProcsThatIsCalledByStar(first);
    std::unordered_set<std::string> expected = {"Second", "Third", "Fourth",
                                                "Fifth",  "Sixth", "Seventh"};
    REQUIRE(actual == expected);
  }

  SECTION("getProcsThatCallsStar") {
    std::string third = "Third";
    auto actual = manager.getProcsThatCallsStar(third);
    std::unordered_set<std::string> expected = {"First", "Second"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllProcsThatCallOtherProcs") {
    std::unordered_set<std::string> actual =
        manager.getAllProcsThatCallOtherProcs();
    std::unordered_set<std::string> expected = {"First", "Second"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllProcsThatGetCalledByOtherProcs") {
    std::unordered_set<std::string> actual =
        manager.getAllProcsThatGetCalledByOtherProcs();
    std::unordered_set<std::string> expected = {"Second", "Third", "Fourth",
                                                "Fifth",  "Sixth", "Seventh"};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Updated Call Test") {
  RelationshipManager manager;
  std::string source = "First";
  std::string target = "Second";
  manager.insertCallsRelationship(source, target);

  SECTION("Left to Right") {
    auto actual = manager.getProcsThatIsCalledBy(source);
    std::unordered_set<std::string> expected;
    expected.insert(target);
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    auto actual = manager.getProcsThatCalls(target);
    std::unordered_set<std::string> expected;
    expected.insert(source);
    REQUIRE(actual == expected);
  }

  manager.insertCallsRelationship("Second", "Third");
  manager.insertCallsRelationship("Second", "Fourth");
  manager.insertCallsRelationship("Second", "Fifth");
  manager.insertCallsRelationship("Second", "Sixth");
  manager.insertCallsRelationship("Second", "Seventh");
  manager.insertCallsRelationship("Second", "Seventh");
  manager.insertCallsRelationship("Second", "Seventh");

  SECTION("getAllCallPairs") {
    std::unordered_set<std::pair<std::string, std::string>, PairHash> actual =
        manager.getAllCallPairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"First", "Second"}, {"Second", "Third"}, {"Second", "Fourth"},
         {"Second", "Fifth"}, {"Second", "Sixth"}, {"Second", "Seventh"}};

    REQUIRE(actual == expected);
  }

  SECTION("getAllCallStarPairs") {
    auto actual = manager.getAllCallStarPairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"First", "Second"}, {"First", "Third"},   {"First", "Fourth"},
         {"First", "Fifth"},  {"First", "Sixth"},   {"First", "Seventh"},
         {"Second", "Third"}, {"Second", "Fourth"}, {"Second", "Fifth"},
         {"Second", "Sixth"}, {"Second", "Seventh"}};

    REQUIRE(actual == expected);
  }

  SECTION("getProcsThatIsCalledByStar") {
    std::string first = "First";
    auto actual = manager.getProcsThatIsCalledByStar(first);
    std::unordered_set<std::string> expected = {"Second", "Third", "Fourth",
                                                "Fifth",  "Sixth", "Seventh"};
    REQUIRE(actual == expected);
  }

  SECTION("getProcsThatCallsStar") {
    std::string third = "Third";
    auto actual = manager.getProcsThatCallsStar(third);
    std::unordered_set<std::string> expected = {"First", "Second"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllProcsThatCallOtherProcs") {
    std::unordered_set<std::string> actual =
        manager.getAllProcsThatCallOtherProcs();
    std::unordered_set<std::string> expected = {"First", "Second"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllProcsThatGetCalledByOtherProcs") {
    std::unordered_set<std::string> actual =
        manager.getAllProcsThatGetCalledByOtherProcs();
    std::unordered_set<std::string> expected = {"Second", "Third", "Fourth",
                                                "Fifth",  "Sixth", "Seventh"};
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Modifies Test") {
  RelationshipManager manager;
  manager.insertModifies(1, "a");
  manager.insertModifies(1, "b");
  manager.insertModifies(1, "c");
  manager.insertModifies(1, "d");
  manager.insertModifies(1, "ef");
  manager.insertModifies(2, "a");
  manager.insertModifies(2, "b");
  manager.insertModifies(2, "c");
  manager.insertModifies(2, "d");
  manager.insertModifies(2, "ef");
  manager.insertModifies(2, "ef");

  SECTION("Left to Right") {
    auto actual = manager.getVarsModifiedByStmt(1);
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    std::string right = "a";
    auto actual = manager.getStmtsThatModifyVar(right);
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }

  SECTION("getAllPairs") {
    auto actual = manager.getAllVarModifiedByStmtPairs();
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "a"}, {1, "b"}, {1, "c"}, {1, "d"}, {1, "ef"},
        {2, "a"}, {2, "b"}, {2, "c"}, {2, "d"}, {2, "ef"}};
    REQUIRE(actual == expected);
  }

  SECTION("getAllStmtsThatModifyVars") {
    std::unordered_set<int> expected = {1, 2};
    std::unordered_set<int> actual = manager.getAllStmtsThatModifyVars();
    REQUIRE(actual == expected);
  }
  SECTION("getAllVarsModifiedByProcedures") {
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    std::unordered_set<std::string> actual =
        manager.getAllVarsModifiedByStmts();
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Modifies Procedure Test") {
  RelationshipManager manager;
  manager.insertModifiesProcedure("main", "a");
  manager.insertModifiesProcedure("main", "b");
  manager.insertModifiesProcedure("main", "c");
  manager.insertModifiesProcedure("main", "d");
  manager.insertModifiesProcedure("main", "ef");
  manager.insertModifiesProcedure("call", "a");
  manager.insertModifiesProcedure("call", "b");
  manager.insertModifiesProcedure("call", "c");
  manager.insertModifiesProcedure("call", "d");
  manager.insertModifiesProcedure("call", "ef");
  manager.insertModifiesProcedure("call", "ef");

  SECTION("Left to Right") {
    std::string left = "main";
    auto actual = manager.getVarsModifiedByProcedure(left);
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    std::string right = "ef";
    auto actual = manager.getProceduresThatModifyVar(right);
    std::unordered_set<std::string> expected = {"main", "call"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllPairs") {
    auto actual = manager.getAllVarModifiedByProcedurePairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"main", "a"},  {"main", "b"}, {"main", "c"}, {"main", "d"},
         {"main", "ef"}, {"call", "a"}, {"call", "b"}, {"call", "c"},
         {"call", "d"},  {"call", "ef"}};
    REQUIRE(actual == expected);
  }

  SECTION("getAllProceduresThatModifyVars") {
    std::unordered_set<std::string> expected = {"main", "call"};
    std::unordered_set<std::string> actual =
        manager.getAllProceduresThatModifyVars();
    REQUIRE(actual == expected);
  }
  SECTION("getAllVarsModifiedByProcedures") {
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    std::unordered_set<std::string> actual =
        manager.getAllVarsModifiedByProcedures();
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Uses Test") {
  RelationshipManager manager;
  manager.insertUses(1, "a");
  manager.insertUses(1, "b");
  manager.insertUses(1, "c");
  manager.insertUses(1, "d");
  manager.insertUses(1, "ef");
  manager.insertUses(2, "a");
  manager.insertUses(2, "b");
  manager.insertUses(2, "c");
  manager.insertUses(2, "d");
  manager.insertUses(2, "ef");
  manager.insertUses(2, "ef");

  SECTION("Left to Right") {
    auto actual = manager.getVarsUsedByStmt(1);
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    std::string right = "a";
    auto actual = manager.getStmtsThatUseVar(right);
    std::unordered_set<int> expected = {1, 2};
    REQUIRE(actual == expected);
  }

  SECTION("getAllPairs") {
    auto actual = manager.getAllVarsUsedByStmtPairs();
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "a"}, {1, "b"}, {1, "c"}, {1, "d"}, {1, "ef"},
        {2, "a"}, {2, "b"}, {2, "c"}, {2, "d"}, {2, "ef"}};
    REQUIRE(actual == expected);
  }

  SECTION("getAllStmtsThatUseVars") {
    std::unordered_set<int> expected = {1, 2};
    std::unordered_set<int> actual = manager.getAllStmtsThatUseVars();
    REQUIRE(actual == expected);
  }
  SECTION("getAllVarsUsedByStmts") {
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    std::unordered_set<std::string> actual = manager.getAllVarsUsedByStmts();
    REQUIRE(actual == expected);
  }
}

TEST_CASE("Uses Procedure Test") {
  RelationshipManager manager;
  manager.insertUsesProcedure("main", "a");
  manager.insertUsesProcedure("main", "b");
  manager.insertUsesProcedure("main", "c");
  manager.insertUsesProcedure("main", "d");
  manager.insertUsesProcedure("main", "ef");
  manager.insertUsesProcedure("call", "a");
  manager.insertUsesProcedure("call", "b");
  manager.insertUsesProcedure("call", "c");
  manager.insertUsesProcedure("call", "d");
  manager.insertUsesProcedure("call", "ef");
  manager.insertUsesProcedure("call", "ef");

  SECTION("Left to Right") {
    std::string left = "main";
    auto actual = manager.getVarsUsedByProcedure(left);
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    REQUIRE(actual == expected);
  }

  SECTION("Right to Left") {
    std::string right = "ef";
    auto actual = manager.getProceduresThatUseVar(right);
    std::unordered_set<std::string> expected = {"main", "call"};
    REQUIRE(actual == expected);
  }

  SECTION("getAllPairs") {
    auto actual = manager.getAllVarUsedByProcedurePairs();
    std::unordered_set<std::pair<std::string, std::string>, PairHash> expected =
        {{"main", "a"},  {"main", "b"}, {"main", "c"}, {"main", "d"},
         {"main", "ef"}, {"call", "a"}, {"call", "b"}, {"call", "c"},
         {"call", "d"},  {"call", "ef"}};
    REQUIRE(actual == expected);
  }

  SECTION("getAllProceduresThatUseVars") {
    std::unordered_set<std::string> expected = {"main", "call"};
    std::unordered_set<std::string> actual =
        manager.getAllProceduresThatUseVars();
    REQUIRE(actual == expected);
  }
  SECTION("getAllVarsUsedByProcedures") {
    std::unordered_set<std::string> expected = {"a", "b", "c", "d", "ef"};
    std::unordered_set<std::string> actual =
        manager.getAllVarsUsedByProcedures();
    REQUIRE(actual == expected);
  }
}
