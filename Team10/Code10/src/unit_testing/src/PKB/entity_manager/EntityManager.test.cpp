#include "entity_manager/EntityManager.h"

#include <unordered_set>

#include "catch.hpp"

TEST_CASE("EntityManager - EntityStore check") {
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

TEST_CASE("EntityManager - StatementStore test") {
  EntityManager testManager;

  std::string const1 = "x";
  std::string const2 = "1";
  std::string const3 = "TESTING!@#";

  testManager.addConstant(const1);
  testManager.addConstant(const2);
  testManager.addConstant(const3);

  std::string var1 = "Yishun";
  std::string var2 = "count";
  std::string var3 = "Mario";

  testManager.addVariable(var1);
  testManager.addVariable(var2);
  testManager.addVariable(var3);

  std::string proc1 = "computeCentroids";
  std::string proc2 = "printCentrals";
  std::string proc3 = "deleteAll";

  testManager.addProcedure(proc1);
  testManager.addProcedure(proc2);
  testManager.addProcedure(proc3);

  testManager.addStatement(StatementType::ASSIGN, 1);
  testManager.addStatement(StatementType::READ, 2);
  testManager.addStatement(StatementType::READ, 3);
  testManager.addStatement(StatementType::PRINT, 4);
  testManager.addStatement(StatementType::PRINT, 5);
  testManager.addStatement(StatementType::PRINT, 6);
  testManager.addStatement(StatementType::CALL, 7);
  testManager.addStatement(StatementType::WHILE, 8);
  testManager.addStatement(StatementType::IF, 9);
  testManager.addStatement(StatementType::IF, 10);

  SECTION("Check constants") {
    std::unordered_set<std::string> test = {"x", "1", "TESTING!@#"};
    REQUIRE(testManager.getAllConstants() == test);
  }

  SECTION("Check variables") {
    std::unordered_set<std::string> test = {"Yishun", "count", "Mario"};
    REQUIRE(testManager.getAllVariables() == test);
  }

  SECTION("Check procedures") {
    std::unordered_set<std::string> test = {"computeCentroids", "printCentrals",
                                            "deleteAll"};
    REQUIRE(testManager.getAllProcedures() == test);
  }

  SECTION("Check statements") {
    std::unordered_set<int> testSet = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    REQUIRE(testSet == testManager.getStatements());
  }
  SECTION("Check Reads") {
    std::unordered_set<int> testSet = {2, 3};

    REQUIRE(testSet == testManager.getReads());
  }
  SECTION("Check Prints") {
    std::unordered_set<int> testSet = {4, 5, 6};

    REQUIRE(testSet == testManager.getPrints());
  }
  SECTION("Check Calls") {
    std::unordered_set<int> testSet = {7};

    REQUIRE(testSet == testManager.getCalls());
  }
  SECTION("Check Whiles") {
    std::unordered_set<int> testSet = {8};

    REQUIRE(testSet == testManager.getWhiles());
  }
  SECTION("Check Ifs") {
    std::unordered_set<int> testSet = {9, 10};

    REQUIRE(testSet == testManager.getIfs());
  }
}

TEST_CASE("EntityManager - RetrieveStore test") {
  EntityManager testManager;
  testManager.insertStmtCallsProc(1, "first");
  testManager.insertStmtCallsProc(2, "second");
  testManager.insertStmtCallsProc(3, "second");
  testManager.insertStmtCallsProc(4, "third");

  testManager.insertStmtPrintsVar(5, "v");
  testManager.insertStmtPrintsVar(6, "x");
  testManager.insertStmtPrintsVar(7, "y");

  testManager.insertStmtReadsVar(8, "v");
  testManager.insertStmtReadsVar(9, "x");
  testManager.insertStmtReadsVar(10, "z");

  SECTION("Check Stmt Number Mapped to Call") {
    std::string expected = "first";
    REQUIRE(expected == testManager.getProcCalledByStmt(1));
  }

  SECTION("getAllStmtsThatCallProc") {
    std::unordered_set<int> expected = {2, 3};
    std::string input = "second";
    REQUIRE(expected == testManager.getAllStmtsThatCallProc(input));
  }

  SECTION("getAllCallsProcPairs") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {1, "first"}, {2, "second"}, {3, "second"}, {4, "third"}};
    REQUIRE(expected == testManager.getAllCallsProcPairs());
  }

  SECTION("getAllProceduresCalledByStmts") {
    std::unordered_set<std::string> expected = {"first", "second", "third"};
    REQUIRE(expected == testManager.getAllProceduresCalledByStmts());
  }

  SECTION("Check Stmt Number Mapped to Print") {
    std::string expected = "v";
    REQUIRE(expected == testManager.getVarPrintedByStmt(5));
  }

  SECTION("getAllStmtsThatPrintVar") {
    std::unordered_set<int> expected = {5};
    std::string input = "v";
    REQUIRE(expected == testManager.getAllStmtsThatPrintVar(input));
  }

  SECTION("getAllPrintVarPairs") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {5, "v"}, {6, "x"}, {7, "y"}};
    REQUIRE(expected == testManager.getAllPrintVarPairs());
  }

  SECTION("getAllRights()") {
    std::unordered_set<std::string> expected = {"v", "x", "y"};
    REQUIRE(expected == testManager.getAllVarsPrintByStmts());
  }

  SECTION("Check Stmt Number Mapped to Read") {
    std::string expected = "v";
    REQUIRE(expected == testManager.getVarReadByStmt(8));
  }

  SECTION("getAllStmtsThatReadVar") {
    std::unordered_set<int> expected = {9};
    std::string input = "x";
    REQUIRE(expected == testManager.getAllStmtsThatReadVar(input));
  }

  SECTION("getAllReadVarPairs") {
    std::unordered_set<std::pair<int, std::string>, PairHash> expected = {
        {8, "v"}, {9, "x"}, {10, "z"}};
    REQUIRE(expected == testManager.getAllReadVarPairs());
  }

  SECTION("getAllVarsReadByStmts") {
    std::unordered_set<std::string> expected = {"v", "x", "z"};
    REQUIRE(expected == testManager.getAllVarsReadByStmts());
  }
}