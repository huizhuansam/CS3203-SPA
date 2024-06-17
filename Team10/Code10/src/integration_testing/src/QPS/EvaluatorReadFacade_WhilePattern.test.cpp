#include "ReadFacade.h"
#include "WriteFacade.h"
#include "catch.hpp"
#include "evaluator/Evaluator.h"
#include "fixtures/Strategies.h"
#include "strategy/strategy_types/PatternStrategy.h"

using namespace QPS;

// QPS::Evaluator integration with PKB ReadFacade for While/* relationship

TEST_CASE("QPS::Evaluator integration with ReadFacade for While",
          "[While][While*]") {
  // Setup
  WriteFacade writer{};
  writer.clearPKB();
  ReadFacade reader{};

  // Write data to PKB
  /*
   * procedure main {
   *   a = 23;                      #1
   *   while (b < 100) {          #2
   *      b = a + c;                #3
   *   }
   *      while (c < 100) {       #4
   *        c = a - b;              #5
   *        read x;                 #6
   *        while (b < c) {       #7
   *            b = c;              #8
   *            c = b;              #9
   *        }
   *      }
   *   }
   * }
   */
  // While(1, 3), While(1, 4), While(1, 6), While(6, 8), While(8, 6)
  writer.addProcedure("main");

  writer.addStatement(StatementType::ASSIGN, 1);
  writer.addStatement(StatementType::WHILE, 2);
  writer.addStatement(StatementType::ASSIGN, 3);
  writer.addStatement(StatementType::WHILE, 4);
  writer.addStatement(StatementType::ASSIGN, 5);
  writer.addStatement(StatementType::READ, 6);
  writer.addStatement(StatementType::WHILE, 7);
  writer.addStatement(StatementType::ASSIGN, 8);
  writer.addStatement(StatementType::ASSIGN, 9);

  writer.addVariable("a");
  writer.addVariable("b");
  writer.addVariable("c");
  writer.addVariable("x");

  writer.addConstant("23");
  writer.addConstant("100");

  writer.insertStmtReadsVar(7, "a");

  writer.addWhileControlVariable(2, "b");
  writer.addWhileControlVariable(4, "c");
  writer.addWhileControlVariable(7, "b");
  writer.addWhileControlVariable(7, "c");
  std::list<std::string> EMPTY_RESULT;

  // While
  SECTION("Select s such that While(wildcard,wildcard,wildcard)") {
    // Select s such that While(_,_,_)
    auto WhileStrategy = std::make_shared<PatternStrategy>(
        StrategyType::WHILE_PATTERN, "v", "_", EntRefType::WILDCARD,
        std::vector<std::string>{}, ExprSpecType::INVALID);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{WhileStrategy}});
    REQUIRE(result.size() == 9);
  }

  SECTION("Select s such that While(synonym,wildcard,wildcard)") {
    // Select s such that While(v,_,_)
    auto WhileStrategy = std::make_shared<PatternStrategy>(
        StrategyType::WHILE_PATTERN, "v", "v", EntRefType::VARIABLE,
        std::vector<std::string>{}, ExprSpecType::INVALID);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{WhileStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"1", "2", "3", "4", "5",
                                       "6", "7", "8", "9"};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that While(ident,wildcard,wildcard)") {
    // Select s such that While("a",_,_)
    auto WhileStrategy = std::make_shared<PatternStrategy>(
        StrategyType::WHILE_PATTERN, "s", "b", EntRefType::IDENT,
        std::vector<std::string>{}, ExprSpecType::INVALID);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{WhileStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"2", "7"};
    REQUIRE(result == expected);
  }

  SECTION(
      "Select s such that While(ident,wildcard,wildcard) - While clause does "
      "not exist") {
    // Select s such that While(_,"2")
    auto WhileStrategy = std::make_shared<PatternStrategy>(
        StrategyType::WHILE_PATTERN, "p", "a", EntRefType::IDENT,
        std::vector<std::string>{}, ExprSpecType::INVALID);
    auto result = Evaluator::getResultList(reader, Strategies::select_s,
                                           {{WhileStrategy}});
    REQUIRE(result == EMPTY_RESULT);
  }

  // Cleanup
  writer.clearPKB();
}