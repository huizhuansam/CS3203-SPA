#include "ReadFacade.h"
#include "WriteFacade.h"
#include "catch.hpp"
#include "evaluator/Evaluator.h"
#include "fixtures/Strategies.h"
#include "strategy/strategy_types/StmtStmtArgStrategy.h"

using namespace QPS;

// QPS::Evaluator integration with PKB ReadFacade for Next/* relationship

TEST_CASE("QPS::Evaluator integration with ReadFacade for Next",
          "[Next][Next*]") {
  // Setup
  WriteFacade writer{};
  writer.clearPKB();
  ReadFacade reader{};

  // Write data to PKB
  /*
   * procedure main {
   *   a = 23;              #1
   *   if (a < 100) then {  #2
   *      b = a + c;        #3
   *   } else {
   *      c = a - b;        #4
   *      while (x < a) {   #5
   *        x = a + 45;     #6
   *        a = b - 45;     #7
   *      }
   *      v = d;            #8
   *   }
   * }
   */
  writer.addProcedure("main");
  writer.addStatement(StatementType::STATEMENT, 1);
  writer.addStatement(StatementType::STATEMENT, 2);
  writer.addStatement(StatementType::STATEMENT, 3);
  writer.addStatement(StatementType::STATEMENT, 4);
  writer.addStatement(StatementType::STATEMENT, 5);
  writer.addStatement(StatementType::STATEMENT, 6);
  writer.addStatement(StatementType::STATEMENT, 7);
  writer.addStatement(StatementType::STATEMENT, 8);

  writer.addVariable("a");
  writer.addVariable("b");
  writer.addVariable("c");
  writer.addVariable("d");
  writer.addVariable("x");
  writer.addVariable("v");

  writer.addConstant("23");
  writer.addConstant("45");
  writer.addConstant("100");

  writer.insertNextRelationship(1, 2);
  writer.insertNextRelationship(2, 3);
  writer.insertNextRelationship(2, 4);
  writer.insertNextRelationship(2, 5);
  writer.insertNextRelationship(4, 5);
  writer.insertNextRelationship(5, 6);
  writer.insertNextRelationship(5, 8);
  writer.insertNextRelationship(6, 7);
  writer.insertNextRelationship(7, 5);

  std::list<std::string> EMPTY_RESULT;

  // Next

  SECTION("Select s such that Next(wildcard,wildcard)") {
    // Select s such that Next(_,_)
    auto nextStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "_", StmtRefType::WILDCARD, "_",
        StmtRefType::WILDCARD);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextStrategy}});
    REQUIRE(result.size() == 8);
  }

  SECTION("Select s such that Next(wildcard,synonym)") {
    // Select s such that Next(_,p)
    auto nextStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "_", StmtRefType::WILDCARD, "s", StmtRefType::STMT);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"2", "3", "4", "5", "6", "7", "8"};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that Next(synonym,wildcard)") {
    // Select s such that Next(p,_)
    auto nextStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "s", StmtRefType::STMT, "_", StmtRefType::WILDCARD);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextStrategy}});
    std::list<std::string> expected = {"1", "2", "4", "5", "6", "7"};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that Next(wildcard,int)") {
    // Select s such that Next(_,"2")
    auto nextStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "_", StmtRefType::WILDCARD, "2",
        StmtRefType::INTEGER);
    std::list<std::string> expected = {"1", "2", "3", "4", "5", "6", "7", "8"};
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextStrategy}});
    REQUIRE(result == expected);
  }

  SECTION(
      "Select s such that Next(wildcard,int) - Next clause evaluates to "
      "false") {
    // Select s such that Next(_,"2")
    auto nextStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "s", StmtRefType::STMT, "5", StmtRefType::INTEGER);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextStrategy}});
    std::list<std::string> expected = {"2", "4", "7"};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that Next(int,wildcard)") {
    // Select s such that Next("5",_)
    auto nextStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "5", StmtRefType::INTEGER, "_",
        StmtRefType::WILDCARD);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextStrategy}});
    REQUIRE(result.size() == 8);
  }

  SECTION(
      "Select s such that Next(int,wildcard) - Next clause evaluates to "
      "8") {
    // Select s such that Next("ProcE",_)
    auto nextStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "8", StmtRefType::INTEGER, "_",
        StmtRefType::WILDCARD);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextStrategy}});

    REQUIRE(result == EMPTY_RESULT);
  }

  SECTION("Select s such that Next(int,int)") {
    // Select s such that Next("2","5")
    auto nextStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "2", StmtRefType::INTEGER, "5",
        StmtRefType::INTEGER);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextStrategy}});
    REQUIRE(result.size() == 8);
  }

  SECTION(
      "Select s such that Next(int,int) - Next clause evaluates to "
      "false") {
    // Select s such that Next("2","8")
    auto nextStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "2", StmtRefType::INTEGER, "8",
        StmtRefType::INTEGER);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextStrategy}});

    REQUIRE(result == EMPTY_RESULT);
  }

  SECTION("Select s such that Next(int,synonym)") {
    // Select s such that Next("2",s)
    auto nextStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "2", StmtRefType::INTEGER, "s", StmtRefType::STMT);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"3", "4", "5"};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that Next(synonym,int)") {
    // Select s such that Next(s, "8")
    auto nextStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "s", StmtRefType::STMT, "8", StmtRefType::INTEGER);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextStrategy}});
    std::list<std::string> expected = {"5"};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that Next(synonym,synonym)") {
    // Select s such that Next(s, s2)
    auto nextStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "s", StmtRefType::STMT, "s2", StmtRefType::STMT);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"1", "2", "4", "5", "6", "7"};
    REQUIRE(result == expected);
  }

  // Next*

  SECTION("Select s such that Next*(wildcard,wildcard)") {
    // Select s such that Next*(_,_)
    auto nextTStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "_", StmtRefType::WILDCARD, "_",
        StmtRefType::WILDCARD);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextTStrategy}});
    REQUIRE(result.size() == 8);
  }

  SECTION("Select s such that Next*(wildcard,synonym)") {
    // Select s such that Next*(_,s)
    auto nextTStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "_", StmtRefType::WILDCARD, "s", StmtRefType::STMT);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextTStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"2", "3", "4", "5", "6", "7", "8"};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that Next*(synonym,wildcard)") {
    // Select s such that Next*(s,_)
    auto nextTStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "s", StmtRefType::STMT, "_", StmtRefType::WILDCARD);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextTStrategy}});
    std::list<std::string> expected = {"1", "2", "4", "5", "6", "7"};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that Next*(wildcard,int)") {
    // Select s such that Next*(_,"2")
    auto nextTStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "_", StmtRefType::WILDCARD, "2",
        StmtRefType::INTEGER);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextTStrategy}});
    REQUIRE(result.size() == 8);
  }

  SECTION(
      "Select s such that Next*(wildcard,int) - Next clause evaluates to "
      "false") {
    // Select s such that Next*(_,"1")
    auto nextTStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "s", StmtRefType::STMT, "1", StmtRefType::INTEGER);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextTStrategy}});
    REQUIRE(result.empty() == true);
  }

  SECTION("Select s such that Next*(int,wildcard)") {
    // Select s such that Next*("1",_)
    auto nextTStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "1", StmtRefType::INTEGER, "_",
        StmtRefType::WILDCARD);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextTStrategy}});
    REQUIRE(result.size() == 8);
  }

  SECTION(
      "Select s such that Next*(int,wildcard) - Next clause evaluates to "
      "false") {
    // Select s such that Next*("8",_)
    auto nextTStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "8", StmtRefType::INTEGER, "_",
        StmtRefType::WILDCARD);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextTStrategy}});

    REQUIRE(result == EMPTY_RESULT);
  }

  SECTION("Select s such that Next*(int,int)") {
    // Select s such that Next*("ProcA","ProcD")
    auto nextTStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "1", StmtRefType::INTEGER, "2",
        StmtRefType::INTEGER);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextTStrategy}});
    REQUIRE(result.size() == 8);
  }

  SECTION(
      "Select s such that Next*(int,int) - Next clause evaluates to "
      "false") {
    // Select s such that Next*("8","7")
    auto nextTStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT, "8", StmtRefType::INTEGER, "7",
        StmtRefType::INTEGER);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextTStrategy}});

    REQUIRE(result == EMPTY_RESULT);
  }

  SECTION("Select s such that Next*(int,synonym)") {
    // Select s such that Next*("1",s)
    auto nextTStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT_T, "1", StmtRefType::INTEGER, "s",
        StmtRefType::STMT);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextTStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"2", "3", "4", "5", "6", "7", "8"};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that Next*(synonym,int)") {
    // Select s such that Next*(s, "5")
    auto nextTStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT_T, "s", StmtRefType::STMT, "5",
        StmtRefType::INTEGER);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextTStrategy}});
    std::list<std::string> expected = {"1", "2", "4", "5", "6", "7"};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that Next*(synonym,synonym)") {
    // Select s such that Next*(p1, p)
    auto nextTStrategy = std::make_shared<StmtStmtArgStrategy>(
        StrategyType::NEXT_T, "s1", StmtRefType::STMT, "s", StmtRefType::STMT);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{nextTStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"2", "3", "4", "5", "6", "7", "8"};
    REQUIRE(result == expected);
  }

  // Cleanup
  writer.clearPKB();
}