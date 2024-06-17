#include "ReadFacade.h"
#include "WriteFacade.h"
#include "catch.hpp"
#include "evaluator/Evaluator.h"
#include "fixtures/Strategies.h"
#include "fixtures/TestUtil.h"
#include "strategy/strategy_types/StmtStmtArgStrategy.h"

using namespace QPS;

TEST_CASE("QPS::Evaluator integration with ReadFacade for Follows",
          "[Follows][Follows*]") {
  // Setup
  WriteFacade writer{};
  writer.clearPKB();
  ReadFacade reader{};

  // Write data to PKB
  /*
     procedure main {
       a = 23;           #1
       c = a - b;        #2
       while (x < a) {   #3
         x = a + 45;     #4
         a = b - 45;     #5
       }
       b = 100;          #6
     }
  */
  writer.addProcedure("main");
  writer.addStatement(StatementType::ASSIGN, 1);
  writer.addStatement(StatementType::ASSIGN, 2);
  writer.addStatement(StatementType::WHILE, 3);
  writer.addStatement(StatementType::ASSIGN, 4);
  writer.addStatement(StatementType::ASSIGN, 5);
  writer.addStatement(StatementType::ASSIGN, 6);

  writer.insertDirectFollowsRelationship(1, 2);
  writer.insertDirectFollowsRelationship(2, 3);
  writer.insertDirectFollowsRelationship(3, 6);
  writer.insertDirectFollowsRelationship(4, 5);

  writer.insertFollowsStarRelationship(1, 2);
  writer.insertFollowsStarRelationship(1, 3);
  writer.insertFollowsStarRelationship(1, 6);
  writer.insertFollowsStarRelationship(2, 3);
  writer.insertFollowsStarRelationship(2, 6);
  writer.insertFollowsStarRelationship(3, 6);
  writer.insertFollowsStarRelationship(4, 5);

  // Follows: Follows(stmtRef, stmtRef)

  SECTION("Follows(int, synonym)") {
    // Select s such that Follows(2, s)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS, "2",
                                              StmtRefType::INTEGER, "s",
                                              StmtRefType::STMT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{followsStrategy}});
    std::list<std::string> expected = {"3"};
    REQUIRE(result == expected);
  }

  SECTION("Follows(int, int)") {
    // Select a such that Follows(3, 6)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS, "3",
                                              StmtRefType::INTEGER, "6",
                                              StmtRefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{followsStrategy}});
    std::list<std::string> expected = {"1", "2", "4", "5", "6"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Follows(int, wildcard)") {
    // Select w such that Follows(1, _)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS, "1",
                                              StmtRefType::INTEGER, "_",
                                              StmtRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_w, {{followsStrategy}});
    std::list<std::string> expected = {"3"};
    REQUIRE(result == expected);
  }

  SECTION("Follows(wildcard, synonym)") {
    // Select a such that Follows(_, a)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS, "_",
                                              StmtRefType::WILDCARD, "a",
                                              StmtRefType::ASSIGN);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{followsStrategy}});
    std::list<std::string> expected = {"2", "5", "6"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Follows(wildcard, int)") {
    // Select a such that Follows(_, 5)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS, "_",
                                              StmtRefType::WILDCARD, "5",
                                              StmtRefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{followsStrategy}});
    std::list<std::string> expected = {"1", "2", "4", "5", "6"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Follows(wildcard, wildcard)") {
    // Select w such that Follows(_, _)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS, "_",
                                              StmtRefType::WILDCARD, "_",
                                              StmtRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_w, {{followsStrategy}});
    std::list<std::string> expected = {"3"};
    REQUIRE(result == expected);
  }

  SECTION("Follows(synonym, synonym), different synonyms") {
    // Select a such that Follows(a, a1)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS, "a",
                                              StmtRefType::ASSIGN, "a1",
                                              StmtRefType::ASSIGN);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{followsStrategy}});
    std::list<std::string> expected = {"1", "4"};
    REQUIRE(result == expected);
  }

  SECTION("Follows(synonym, synonym), same synonym") {
    // Select a such that Follows(a, a)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS, "a",
                                              StmtRefType::ASSIGN, "a",
                                              StmtRefType::ASSIGN);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{followsStrategy}});
    std::list<std::string> expected = {};
    REQUIRE(result == expected);
  }

  SECTION("Follows(synonym, int)") {
    // Select w such that Follows(w, 6)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS, "w",
                                              StmtRefType::WHILE, "6",
                                              StmtRefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_w, {{followsStrategy}});
    std::list<std::string> expected = {"3"};
    REQUIRE(result == expected);
  }

  SECTION("Follows(synonym, wildcard)") {
    // Select a such that Follows(a, _)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS, "a",
                                              StmtRefType::ASSIGN, "_",
                                              StmtRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{followsStrategy}});
    std::list<std::string> expected = {"1", "2", "4"};
    REQUIRE(result == expected);
  }

  // FollowsT: Follows*(stmtRef, stmtRef)

  SECTION("Follows*(int, synonym)") {
    // Select s such that Follows*(1, s)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS_T, "1",
                                              StmtRefType::INTEGER, "s",
                                              StmtRefType::STMT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{followsStrategy}});
    std::list<std::string> expected = {"2", "3", "6"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Follows*(int, int)") {
    // Select a such that Follows*(1, 3)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS_T, "1",
                                              StmtRefType::INTEGER, "3",
                                              StmtRefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{followsStrategy}});
    std::list<std::string> expected = {"1", "2", "4", "5", "6"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Follows*(int, wildcard)") {
    // Select s such that Follows*(6, _) --> evaluates to false
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS_T, "6",
                                              StmtRefType::INTEGER, "_",
                                              StmtRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{followsStrategy}});
    std::list<std::string> expected = {};
    REQUIRE(result == expected);
  }

  SECTION("Follows*(wildcard, synonym)") {
    // Select a such that Follows*(_, a)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS_T, "_",
                                              StmtRefType::WILDCARD, "a",
                                              StmtRefType::ASSIGN);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{followsStrategy}});
    std::list<std::string> expected = {"2", "5", "6"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Follows*(wildcard, int)") {
    // Select a such that Follows*(_, 5)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS_T, "_",
                                              StmtRefType::WILDCARD, "5",
                                              StmtRefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{followsStrategy}});
    std::list<std::string> expected = {"1", "2", "4", "5", "6"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Follows*(wildcard, wildcard)") {
    // Select s such that Follows*(_, _)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS_T, "_",
                                              StmtRefType::WILDCARD, "_",
                                              StmtRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{followsStrategy}});
    std::list<std::string> expected = {"1", "2", "3", "4", "5", "6"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Follows*(synonym, synonym), different synonyms") {
    // Select a such that Follows*(a, a1)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS_T, "a",
                                              StmtRefType::ASSIGN, "a1",
                                              StmtRefType::ASSIGN);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{followsStrategy}});
    std::list<std::string> expected = {"1", "2", "4"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("Follows*(synonym, synonym), same synonym") {
    // Select a such that Follows*(a, a)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS_T, "a",
                                              StmtRefType::ASSIGN, "a",
                                              StmtRefType::ASSIGN);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{followsStrategy}});
    std::list<std::string> expected = {};
    REQUIRE(result == expected);
  }

  SECTION("Follows*(synonym, int)") {
    // Select s such that Follows*(s, 6)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS_T, "s",
                                              StmtRefType::STMT, "6",
                                              StmtRefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{followsStrategy}});
    std::list<std::string> expected = {"1", "2", "3"};
    REQUIRE(result == expected);
  }

  SECTION("Follows*(synonym, wildcard)") {
    // Select a such that Follows*(a, _)
    std::shared_ptr<Strategy> followsStrategy =
        std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS_T, "a",
                                              StmtRefType::ASSIGN, "_",
                                              StmtRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{followsStrategy}});
    std::list<std::string> expected = {"1", "2", "4"};
    REQUIRE(result == expected);
  }

  // Cleanup
  writer.clearPKB();
}
