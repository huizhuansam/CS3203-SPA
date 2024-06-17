#include "ReadFacade.h"
#include "WriteFacade.h"
#include "catch.hpp"
#include "evaluator/Evaluator.h"
#include "fixtures/Strategies.h"
#include "strategy/strategy_types/PatternStrategy.h"

using namespace QPS;

// QPS::Evaluator integration with PKB ReadFacade for If/* relationship

TEST_CASE("QPS::Evaluator integration with ReadFacade for If", "[If][If*]") {
  // Setup
  WriteFacade writer{};
  writer.clearPKB();
  ReadFacade reader{};

  // Write data to PKB
  /*
   * procedure main {
   *   a = 23;                      #1
   *   if (b < 100) then {          #2
   *      b = a + c;                #3
   *   } else {
   *      if (c < 100) then {       #4
   *        c = a - b;              #5
   *        read x;                 #6
   *      } else {
   *        if (b < c) then {       #7
   *              b = c;              #8
   *        } else {
   *            c = b;              #9
   *        }
   *      }
   *   }
   * }
   */
  // If(1, 3), If(1, 4), If(1, 6), If(6, 8), If(8, 6)
  writer.addProcedure("main");

  writer.addStatement(StatementType::ASSIGN, 1);
  writer.addStatement(StatementType::IF, 2);
  writer.addStatement(StatementType::ASSIGN, 3);
  writer.addStatement(StatementType::IF, 4);
  writer.addStatement(StatementType::ASSIGN, 5);
  writer.addStatement(StatementType::READ, 6);
  writer.addStatement(StatementType::IF, 7);
  writer.addStatement(StatementType::ASSIGN, 8);
  writer.addStatement(StatementType::ASSIGN, 9);

  writer.addVariable("a");
  writer.addVariable("b");
  writer.addVariable("c");
  writer.addVariable("x");

  writer.addConstant("23");
  writer.addConstant("100");

  writer.insertStmtReadsVar(7, "a");

  writer.addIfControlVariable(2, "b");
  writer.addIfControlVariable(4, "c");
  writer.addIfControlVariable(7, "b");
  writer.addIfControlVariable(7, "c");
  std::list<std::string> EMPTY_RESULT;

  // If
  SECTION("Select s such that If(wildcard,wildcard,wildcard)") {
    // Select s such that If(_,_,_)
    auto IfStrategy = std::make_shared<PatternStrategy>(
        StrategyType::IF_PATTERN, "v", "_", EntRefType::WILDCARD,
        std::vector<std::string>{}, ExprSpecType::INVALID);
    auto result =
        Evaluator::getResultList(reader, Strategies::select_s, {{IfStrategy}});
    REQUIRE(result.size() == 9);
  }

  SECTION("Select s such that If(synonym,wildcard,wildcard)") {
    // Select s such that If(v,_,_)
    auto IfStrategy = std::make_shared<PatternStrategy>(
        StrategyType::IF_PATTERN, "v", "v", EntRefType::VARIABLE,
        std::vector<std::string>{}, ExprSpecType::INVALID);
    auto result =
        Evaluator::getResultList(reader, Strategies::select_s, {{IfStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"1", "2", "3", "4", "5",
                                       "6", "7", "8", "9"};
    REQUIRE(result == expected);
  }

  SECTION("Select s such that If(ident,wildcard,wildcard)") {
    // Select s such that If("a",_,_)
    auto IfStrategy = std::make_shared<PatternStrategy>(
        StrategyType::IF_PATTERN, "s", "b", EntRefType::IDENT,
        std::vector<std::string>{}, ExprSpecType::INVALID);
    auto result =
        Evaluator::getResultList(reader, Strategies::select_s, {{IfStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"2", "7"};
    REQUIRE(result == expected);
  }

  SECTION(
      "Select s such that If(ident,wildcard,wildcard) - If clause does not "
      "exist") {
    // Select s such that If(_,"2")
    auto IfStrategy = std::make_shared<PatternStrategy>(
        StrategyType::IF_PATTERN, "p", "a", EntRefType::IDENT,
        std::vector<std::string>{}, ExprSpecType::INVALID);
    auto result =
        Evaluator::getResultList(reader, Strategies::select_s, {{IfStrategy}});
    REQUIRE(result == EMPTY_RESULT);
  }

  // Cleanup
  writer.clearPKB();
}