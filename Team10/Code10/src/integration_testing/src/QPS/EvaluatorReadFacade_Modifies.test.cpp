#include "ReadFacade.h"
#include "WriteFacade.h"
#include "catch.hpp"
#include "evaluator/Evaluator.h"
#include "fixtures/Strategies.h"
#include "fixtures/TestUtil.h"
#include "strategy/strategy_types/EntEntArgStrategy.h"
#include "strategy/strategy_types/StmtEntArgStrategy.h"

using namespace QPS;

TEST_CASE(
    "QPS::Evaluator integration with ReadFacade for Modifies relationship",
    "[ModifiesS][ModifiesP]") {
  // Setup
  WriteFacade writer{};
  writer.clearPKB();
  ReadFacade reader{};

  // Write data to PKB
  // procedure main {
  //    one = 1;
  //    read two;
  //    three = 3;
  // }
  // procedure second {
  //    four = 4;
  //    read three;
  // }
  writer.addProcedure("main");
  writer.addProcedure("second");
  writer.addStatement(StatementType::ASSIGN, 1);
  writer.addStatement(StatementType::READ, 2);
  writer.addStatement(StatementType::ASSIGN, 3);
  writer.addStatement(StatementType::ASSIGN, 4);
  writer.addStatement(StatementType::READ, 5);
  writer.addVariable("one");
  writer.addVariable("two");
  writer.addVariable("three");
  writer.addVariable("four");

  writer.insertModifies(1, "one");
  writer.insertModifies(2, "two");
  writer.insertModifies(3, "three");
  writer.insertModifies(4, "four");
  writer.insertModifies(5, "three");

  writer.insertModifiesProcedure("main", "one");
  writer.insertModifiesProcedure("main", "two");
  writer.insertModifiesProcedure("main", "three");
  writer.insertModifiesProcedure("second", "four");
  writer.insertModifiesProcedure("second", "three");

  // ModifiesS: Modifies(stmtRef, entRef)

  SECTION("(int, synonym)") {
    // Select v such that Modifies(2, v)
    std::shared_ptr<Strategy> modifiesStrategy =
        std::make_shared<StmtEntArgStrategy>(StrategyType::MODIFIES_S, "2",
                                             StmtRefType::INTEGER, "v",
                                             EntRefType::VARIABLE);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_v, {{modifiesStrategy}});
    std::list<std::string> expected = {"two"};
    REQUIRE(result == expected);
  }

  SECTION("(int, wildcard)") {
    // Select v such that Modifies(2, _)
    std::shared_ptr<Strategy> modifiesStrategy =
        std::make_shared<StmtEntArgStrategy>(StrategyType::MODIFIES_S, "2",
                                             StmtRefType::INTEGER, "v",
                                             EntRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_v, {{modifiesStrategy}});
    std::list<std::string> expected = {"one", "two", "three", "four"};
    result.sort();
    result.unique();
    expected.sort();
    expected.unique();
    REQUIRE(result == expected);
  }

  SECTION("(int, ident)") {
    // Select v such that Modifies(3, "three")
    std::shared_ptr<Strategy> modifiesStrategy =
        std::make_shared<StmtEntArgStrategy>(StrategyType::MODIFIES_S, "3",
                                             StmtRefType::INTEGER, "three",
                                             EntRefType::IDENT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_v, {{modifiesStrategy}});
    std::list<std::string> expected = {"one", "two", "three", "four"};
    result.sort();
    result.unique();
    expected.sort();
    expected.unique();
    REQUIRE(result == expected);
  }

  SECTION("(synonym, synonym)") {
    // Select v such that Modifies(a, v)
    std::shared_ptr<Strategy> modifiesStrategy =
        std::make_shared<StmtEntArgStrategy>(StrategyType::MODIFIES_S, "a",
                                             StmtRefType::ASSIGN, "v",
                                             EntRefType::VARIABLE);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_v, {{modifiesStrategy}});
    std::list<std::string> expected = {"one", "three", "four"};
    REQUIRE(result == expected);

    // Select r such that Modifies(r, v)
    std::shared_ptr<Strategy> modifiesStrategy2 =
        std::make_shared<StmtEntArgStrategy>(StrategyType::MODIFIES_S, "r",
                                             StmtRefType::READ, "v",
                                             EntRefType::VARIABLE);
    std::list<std::string> result2 = Evaluator::getResultList(
        reader, Strategies::select_r, {{modifiesStrategy2}});
    std::list<std::string> expected2 = {"2", "5"};
    REQUIRE(result2 == expected2);
  }

  SECTION("(synonym, wildcard)") {
    // Select a such that Modifies(a, _)
    std::shared_ptr<Strategy> modifiesStrategy =
        std::make_shared<StmtEntArgStrategy>(StrategyType::MODIFIES_S, "a",
                                             StmtRefType::ASSIGN, "_",
                                             EntRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{modifiesStrategy}});
    std::list<std::string> expected = {"1", "3", "4"};
    REQUIRE(result == expected);
  }

  SECTION("(synonym, ident)") {
    // Select s such that Modifies(s, "three")
    std::shared_ptr<Strategy> modifiesStrategy =
        std::make_shared<StmtEntArgStrategy>(StrategyType::MODIFIES_S, "s",
                                             StmtRefType::STMT, "three",
                                             EntRefType::IDENT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{modifiesStrategy}});
    std::list<std::string> expected = {"3", "5"};
    REQUIRE(result == expected);
  }

  // ModifiesP: Modifies(entRef, entRef)

  SECTION("(ident, ident)") {
    // Select p such that Modifies("main", "two")
    std::shared_ptr<Strategy> modifiesStrategy =
        std::make_shared<EntEntArgStrategy>(StrategyType::MODIFIES_P, "main",
                                            EntRefType::IDENT, "two",
                                            EntRefType::IDENT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_p, {{modifiesStrategy}});
    std::list<std::string> expected = {"main", "second"};
    REQUIRE(result == expected);
  }

  SECTION("(ident, wildcard)") {
    // Select p such that Modifies("main", _)
    std::shared_ptr<Strategy> modifiesStrategy =
        std::make_shared<EntEntArgStrategy>(StrategyType::MODIFIES_P, "main",
                                            EntRefType::IDENT, "_",
                                            EntRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_p, {{modifiesStrategy}});
    std::list<std::string> expected = {"main", "second"};
    REQUIRE(result == expected);
  }

  SECTION("(ident, synonym)") {
    // Select v such that Modifies("main", v)
    std::shared_ptr<Strategy> modifiesStrategy =
        std::make_shared<EntEntArgStrategy>(StrategyType::MODIFIES_P, "main",
                                            EntRefType::IDENT, "v",
                                            EntRefType::VARIABLE);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_v, {{modifiesStrategy}});
    std::list<std::string> expected = {"one", "two", "three"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("(synonym, synonym)") {
    // Select p such that Modifies(p, v)
    std::shared_ptr<Strategy> modifiesStrategy =
        std::make_shared<EntEntArgStrategy>(StrategyType::MODIFIES_P, "p",
                                            EntRefType::PROCEDURE, "v",
                                            EntRefType::VARIABLE);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_p, {{modifiesStrategy}});
    std::list<std::string> expected = {"main", "second"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));

    // Select v such that Modifies(p, v)
    std::list<std::string> result2 = Evaluator::getResultList(
        reader, Strategies::select_v, {{modifiesStrategy}});
    std::list<std::string> expected2 = {"one", "two", "three", "four"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result2, expected2));
  }

  SECTION("(synonym, ident)") {
    // Select p such that Modifies(p, "four")
    std::shared_ptr<Strategy> modifiesStrategy =
        std::make_shared<EntEntArgStrategy>(StrategyType::MODIFIES_P, "p",
                                            EntRefType::PROCEDURE, "four",
                                            EntRefType::IDENT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_p, {{modifiesStrategy}});
    std::list<std::string> expected = {"second"};
    REQUIRE(result == expected);
  }

  SECTION("(synonym, wildcard)") {
    // Select p such that Modifies(p, _)
    std::shared_ptr<Strategy> modifiesStrategy =
        std::make_shared<EntEntArgStrategy>(StrategyType::MODIFIES_P, "p",
                                            EntRefType::PROCEDURE, "_",
                                            EntRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_p, {{modifiesStrategy}});
    std::list<std::string> expected = {"main", "second"};
    REQUIRE(result == expected);
  }

  // Cleanup
  writer.clearPKB();
}
