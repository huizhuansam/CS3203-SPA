#include "ReadFacade.h"
#include "WriteFacade.h"
#include "catch.hpp"
#include "evaluator/Evaluator.h"
#include "fixtures/Strategies.h"
#include "strategy/strategy_types/StmtStmtArgStrategy.h"

using namespace QPS;

// QPS::Evaluator integration with PKB ReadFacade for Affects/* relationship

TEST_CASE("QPS::Evaluator integration with ReadFacade for Affects",
          "[Affects][Affects*]") {
  // Setup
  WriteFacade writer{};
  writer.clearPKB();
  ReadFacade reader{};

  // Write data to PKB
  /*
   * procedure main {
   *   a = 23;              #1
   *   if (b < 100) then {  #2
   *      b = a + c;        #3
   *   } else {
   *      c = a - b;        #4
   *      while (x < a) {   #5
   *        x = a + x;      #6
   *        read a;         #7
   *        x = x - 45;     #8
   *      }
   *      v = d;            #9
   *   }
   * }
   */
  // Affects(1, 3), Affects(1, 4), Affects(1, 6), Affects(6, 8), Affects(8, 6)
  writer.addProcedure("main");
  writer.addStatement(StatementType::STATEMENT, 1);
  writer.addStatement(StatementType::STATEMENT, 2);
  writer.addStatement(StatementType::STATEMENT, 3);
  writer.addStatement(StatementType::STATEMENT, 4);
  writer.addStatement(StatementType::STATEMENT, 5);
  writer.addStatement(StatementType::STATEMENT, 6);
  writer.addStatement(StatementType::STATEMENT, 7);
  writer.addStatement(StatementType::STATEMENT, 8);
  writer.addStatement(StatementType::STATEMENT, 9);

  writer.addStatement(StatementType::ASSIGN, 1);
  writer.addStatement(StatementType::IF, 2);
  writer.addStatement(StatementType::ASSIGN, 3);
  writer.addStatement(StatementType::ASSIGN, 4);
  writer.addStatement(StatementType::WHILE, 5);
  writer.addStatement(StatementType::ASSIGN, 6);
  writer.addStatement(StatementType::READ, 7);
  writer.addStatement(StatementType::ASSIGN, 8);
  writer.addStatement(StatementType::ASSIGN, 9);

  writer.addVariable("a");
  writer.addVariable("b");
  writer.addVariable("c");
  writer.addVariable("d");
  writer.addVariable("x");
  writer.addVariable("v");

  writer.addConstant("23");
  writer.addConstant("45");
  writer.addConstant("100");

  writer.insertStmtReadsVar(7, "a");

  writer.addAssignExpPattern(1, "a", {"23"});
  writer.addAssignExpPattern(3, "b", {"a", "+", "c"});
  writer.addAssignExpPattern(4, "c", {"a", "-", "b"});
  writer.addAssignExpPattern(6, "x", {"a", "+", "x"});
  writer.addAssignExpPattern(8, "x", {"x", "-", "45"});
  writer.addAssignExpPattern(9, "v", {"d"});

  writer.insertNextRelationship(1, 2);
  writer.insertNextRelationship(2, 3);
  writer.insertNextRelationship(2, 4);
  writer.insertNextRelationship(4, 5);
  writer.insertNextRelationship(5, 6);
  writer.insertNextRelationship(5, 9);
  writer.insertNextRelationship(6, 7);
  writer.insertNextRelationship(7, 8);
  writer.insertNextRelationship(8, 5);

  writer.insertModifies(1, "a");
  writer.insertModifies(2, "b");
  writer.insertModifies(2, "c");
  writer.insertModifies(2, "x");
  writer.insertModifies(2, "v");

  writer.insertModifies(3, "b");
  writer.insertModifies(4, "c");
  writer.insertModifies(5, "x");

  writer.insertModifies(6, "x");
  writer.insertModifies(8, "x");
  writer.insertModifies(9, "v");

  writer.insertUses(2, "a");
  writer.insertUses(2, "b");
  writer.insertUses(2, "c");
  writer.insertUses(2, "d");
  writer.insertUses(2, "x");
  writer.insertUses(3, "a");
  writer.insertUses(3, "c");
  writer.insertUses(4, "a");
  writer.insertUses(4, "b");
  writer.insertUses(5, "x");
  writer.insertUses(5, "a");
  writer.insertUses(6, "a");
  writer.insertUses(6, "x");
  writer.insertUses(8, "x");
  writer.insertUses(9, "d");

  writer.addIfControlVariable(2, "b");
  writer.addWhileControlVariable(5, "x");
  writer.addWhileControlVariable(5, "a");
  std::list<std::string> EMPTY_RESULT;

  // Affects

  SECTION("Select s such that Affects(wildcard,wildcard)") {
    // Select s such that Affects(_,_)
    auto AffectsStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::AFFECTS, "_", StmtRefType::WILDCARD, "_",
        StmtRefType::WILDCARD);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{AffectsStrategy}});
    REQUIRE(result.size() == 9);
  }

  SECTION("Select s such that Affects(wildcard,synonym)") {
    // Select s such that Affects(_,p)
    auto AffectsStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::AFFECTS, "_", StmtRefType::WILDCARD, "s",
        StmtRefType::STMT);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{AffectsStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"3", "4", "6", "8"};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that Affects(synonym,wildcard)") {
    // Select s such that Affects(p,_)
    auto AffectsStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::AFFECTS, "s", StmtRefType::STMT, "_",
        StmtRefType::WILDCARD);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{AffectsStrategy}});
    std::list<std::string> expected = {"1", "6", "8"};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that Affects(wildcard,int)") {
    // Select s such that Affects(_,"2")
    auto AffectsStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::AFFECTS, "_", StmtRefType::WILDCARD, "6",
        StmtRefType::INTEGER);
    std::list<std::string> expected = {"1", "2", "3", "4", "5",
                                       "6", "7", "8", "9"};
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{AffectsStrategy}});
    REQUIRE(result == expected);
  }

  SECTION(
      "Select s such that Affects(wildcard,int) - Affects clause evaluates to "
      "false") {
    // Select s such that Affects(_,"2")
    auto AffectsStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::AFFECTS, "s", StmtRefType::STMT, "5",
        StmtRefType::INTEGER);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{AffectsStrategy}});
    std::list<std::string> expected = {};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that Affects(int,wildcard)") {
    // Select s such that Affects("5",_)
    auto AffectsStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::AFFECTS, "1", StmtRefType::INTEGER, "_",
        StmtRefType::WILDCARD);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{AffectsStrategy}});
    REQUIRE(result.size() == 9);
  }

  SECTION(
      "Select s such that Affects(int,wildcard) - Affects clause evaluates to "
      "8") {
    // Select s such that Affects("ProcE",_)
    auto AffectsStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::AFFECTS, "5", StmtRefType::INTEGER, "_",
        StmtRefType::WILDCARD);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{AffectsStrategy}});

    REQUIRE(result == EMPTY_RESULT);
  }

  SECTION("Select s such that Affects(int,int)") {
    // Select s such that Affects("2","5")
    auto AffectsStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::AFFECTS, "8", StmtRefType::INTEGER, "6",
        StmtRefType::INTEGER);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{AffectsStrategy}});
    REQUIRE(result.size() == 9);
  }

  SECTION(
      "Select s such that Affects(int,int) - Affects clause evaluates to "
      "false") {
    // Select s such that Affects("2","8")
    auto AffectsStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::AFFECTS, "2", StmtRefType::INTEGER, "8",
        StmtRefType::INTEGER);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{AffectsStrategy}});

    REQUIRE(result == EMPTY_RESULT);
  }

  SECTION("Select s such that Affects(int,synonym)") {
    // Select s such that Affects("2",s)
    auto AffectsStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::AFFECTS, "1", StmtRefType::INTEGER, "s",
        StmtRefType::STMT);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{AffectsStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"3", "4", "6"};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that Affects(synonym,int)") {
    // Select s such that Affects(s, "8")
    auto AffectsStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::AFFECTS, "s", StmtRefType::STMT, "6",
        StmtRefType::INTEGER);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{AffectsStrategy}});
    std::list<std::string> expected = {"1", "8"};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that Affects(synonym,synonym)") {
    // Select s such that Affects(s, s2)
    auto AffectsStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::AFFECTS, "s", StmtRefType::STMT, "s2", StmtRefType::STMT);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{AffectsStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"1", "6", "8"};
    REQUIRE(result == expected);
  }
  // Cleanup
  writer.clearPKB();
}