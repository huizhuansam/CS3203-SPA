#include "ReadFacade.h"
#include "WriteFacade.h"
#include "catch.hpp"
#include "evaluator/Evaluator.h"
#include "fixtures/Strategies.h"
#include "fixtures/TestUtil.h"
#include "strategy/strategy_types/StmtStmtArgStrategy.h"

using namespace QPS;

TEST_CASE("QPS::Evaluator integration with ReadFacade for Parent relationship",
          "[Parent][Parent*]") {
  // Setup
  WriteFacade writer{};
  writer.clearPKB();
  ReadFacade reader{};

  // Write data to PKB
  /*
     procedure main {
       a = 23;              #1
       if (a < 100) then {  #2
          b = a + c;        #3
       } else {
          c = a - b;        #4
          while (x < a) {   #5
            x = a + 45;     #6
            a = b - 45;     #7
          }
          v = d;            #8
       }
     }
  */
  writer.addProcedure("main");
  writer.addStatement(StatementType::ASSIGN, 1);
  writer.addStatement(StatementType::IF, 2);
  writer.addStatement(StatementType::ASSIGN, 3);
  writer.addStatement(StatementType::ASSIGN, 4);
  writer.addStatement(StatementType::WHILE, 5);
  writer.addStatement(StatementType::ASSIGN, 6);
  writer.addStatement(StatementType::ASSIGN, 7);
  writer.addStatement(StatementType::ASSIGN, 8);

  writer.insertDirectParentChildRelationship(2, 3);
  writer.insertDirectParentChildRelationship(2, 4);
  writer.insertDirectParentChildRelationship(2, 5);
  writer.insertDirectParentChildRelationship(2, 8);
  writer.insertDirectParentChildRelationship(5, 6);
  writer.insertDirectParentChildRelationship(5, 7);

  writer.insertParentStarRelationship(2, 3);
  writer.insertParentStarRelationship(2, 4);
  writer.insertParentStarRelationship(2, 5);
  writer.insertParentStarRelationship(2, 6);
  writer.insertParentStarRelationship(2, 7);
  writer.insertParentStarRelationship(2, 8);
  writer.insertParentStarRelationship(5, 6);
  writer.insertParentStarRelationship(5, 7);

  // Parent: Parent(stmtRef, stmtRef)

  SECTION("Parent(int, synonym)") {
    // Select s such that Parent(2, s)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT, "2",
                                              StmtRefType::INTEGER, "s",
                                              StmtRefType::STMT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{parentStrategy}});
    std::list<std::string> expected = {"3", "4", "5", "8"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Parent(int, int)") {
    // Select a such that Parent(2, 5)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT, "2",
                                              StmtRefType::INTEGER, "5",
                                              StmtRefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{parentStrategy}});
    std::list<std::string> expected = {"1", "3", "4", "6", "7", "8"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Parent(int, wildcard)") {
    // Select w such that Parent(5, _)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT, "5",
                                              StmtRefType::INTEGER, "_",
                                              StmtRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_w, {{parentStrategy}});
    std::list<std::string> expected = {"5"};
    REQUIRE(result == expected);
  }

  SECTION("Parent(wildcard, synonym)") {
    // Select a such that Parent(_, a)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT, "_",
                                              StmtRefType::WILDCARD, "a",
                                              StmtRefType::ASSIGN);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{parentStrategy}});
    std::list<std::string> expected = {"3", "4", "6", "7", "8"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Parent(wildcard, wildcard)") {
    // Select i such that Parent(_, _)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT, "_",
                                              StmtRefType::WILDCARD, "_",
                                              StmtRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_i, {{parentStrategy}});
    std::list<std::string> expected = {"2"};
    REQUIRE(result == expected);
  }

  SECTION("Parent(synonym, synonym), different synonyms") {
    // Select s such that Parent(i, s)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(
            StrategyType::PARENT, "i", StmtRefType::IF, "s", StmtRefType::STMT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{parentStrategy}});
    std::list<std::string> expected = {"3", "4", "5", "8"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Parent(synonym, synonym), same synonyms") {
    // Select w such that Parent(w, w)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT, "w",
                                              StmtRefType::WHILE, "w",
                                              StmtRefType::WHILE);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_w, {{parentStrategy}});
    std::list<std::string> expected = {};
    REQUIRE(result == expected);
  }

  SECTION("Parent(synonym, integer)") {
    // Select w such that Parent(w, 6)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT, "w",
                                              StmtRefType::WHILE, "6",
                                              StmtRefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_w, {{parentStrategy}});
    std::list<std::string> expected = {"5"};
    REQUIRE(result == expected);
  }

  SECTION("Parent(synonym, wildcard)") {
    // Select i such that Parent(i, _)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT, "i",
                                              StmtRefType::IF, "_",
                                              StmtRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_i, {{parentStrategy}});
    std::list<std::string> expected = {"2"};
    REQUIRE(result == expected);
  }

  // ParentT: Parent*(stmtRef, stmtRef)

  SECTION("Parent*(int, synonym)") {
    // Select s such that Parent*(2, s)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT_T, "2",
                                              StmtRefType::INTEGER, "s",
                                              StmtRefType::STMT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{parentStrategy}});
    std::list<std::string> expected = {"3", "4", "5", "6", "7", "8"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Parent*(int, int)") {
    // Select a such that Parent*(1, 6) -> evaluates to false
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT_T, "1",
                                              StmtRefType::INTEGER, "6",
                                              StmtRefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{parentStrategy}});
    std::list<std::string> expected = {};
    REQUIRE(result == expected);
  }

  SECTION("Parent*(int, wildcard)") {
    // Select a such that Parent*(2, _)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT_T, "2",
                                              StmtRefType::INTEGER, "_",
                                              StmtRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{parentStrategy}});
    std::list<std::string> expected = {"1", "3", "4", "6", "7", "8"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Parent*(wildcard, synonym)") {
    // Select a such that Parent*(_, a)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT_T, "_",
                                              StmtRefType::WILDCARD, "a",
                                              StmtRefType::ASSIGN);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{parentStrategy}});
    std::list<std::string> expected = {"3", "4", "6", "7", "8"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Parent*(wildcard, int)") {
    // Select i such that Parent*(_, 7)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT_T, "_",
                                              StmtRefType::WILDCARD, "7",
                                              StmtRefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_i, {{parentStrategy}});
    std::list<std::string> expected = {"2"};
    REQUIRE(result == expected);
  }

  SECTION("Parent*(wildcard, wildcard)") {
    // Select s such that Parent*(_, _)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT_T, "_",
                                              StmtRefType::WILDCARD, "_",
                                              StmtRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{parentStrategy}});
    std::list<std::string> expected = {"1", "2", "3", "4", "5", "6", "7", "8"};
    REQUIRE(result == expected);
  }

  SECTION("Parent*(synonym, synonym), different synonyms") {
    // Select s such that Parent*(s1, s)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT_T, "s1",
                                              StmtRefType::STMT, "s",
                                              StmtRefType::STMT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{parentStrategy}});
    std::list<std::string> expected = {"3", "4", "5", "6", "7", "8"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Parent*(synonym, synonym), same synonym") {
    // Select s such that Parent*(s, s)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT_T, "s",
                                              StmtRefType::STMT, "s",
                                              StmtRefType::STMT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{parentStrategy}});
    std::list<std::string> expected = {};
    REQUIRE(result == expected);
  }

  SECTION("Parent*(synonym, int)") {
    // Select s such that Parent*(s, 7)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT_T, "s",
                                              StmtRefType::STMT, "7",
                                              StmtRefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{parentStrategy}});
    std::list<std::string> expected = {"2", "5"};
    REQUIRE(result == expected);
  }

  SECTION("Parent*(synonym, wildcard)") {
    // Select s such that Parent*(s, _)
    std::shared_ptr<Strategy> parentStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT_T, "s",
                                              StmtRefType::STMT, "_",
                                              StmtRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{parentStrategy}});
    std::list<std::string> expected = {"2", "5"};
    REQUIRE(result == expected);
  }

  // Cleanup
  writer.clearPKB();
}
