#include "ReadFacade.h"
#include "WriteFacade.h"
#include "catch.hpp"
#include "evaluator/Evaluator.h"
#include "fixtures/Strategies.h"
#include "fixtures/TestUtil.h"
#include "strategy/strategy_types/EntEntArgStrategy.h"
#include "strategy/strategy_types/StmtEntArgStrategy.h"

using namespace QPS;

TEST_CASE("QPS::Evaluator integration with ReadFacade for Uses relationship",
          "[UsesS][UsesP]") {
  // Setup
  WriteFacade writer{};
  writer.clearPKB();
  ReadFacade reader{};

  // Write data to PKB
  // procedure main {
  //    a = b + 3;
  //    print a;
  //    while (a < 40) {
  //       a = a + c;
  //    }
  //    c = c + 21;
  // }
  // procedure second {
  //    d = a + 11;
  //    print d;
  // }
  writer.addProcedure("main");
  writer.addProcedure("second");
  writer.addStatement(StatementType::ASSIGN, 1);
  writer.addStatement(StatementType::PRINT, 2);
  writer.addStatement(StatementType::WHILE, 3);
  writer.addStatement(StatementType::ASSIGN, 4);
  writer.addStatement(StatementType::ASSIGN, 5);
  writer.addStatement(StatementType::ASSIGN, 6);
  writer.addStatement(StatementType::PRINT, 7);

  writer.addVariable("a");
  writer.addVariable("b");
  writer.addVariable("c");
  writer.addVariable("d");

  writer.insertUses(1, "b");
  writer.insertUses(2, "a");
  writer.insertUses(3, "a");
  writer.insertUses(3, "c");
  writer.insertUses(4, "a");
  writer.insertUses(4, "c");
  writer.insertUses(5, "c");
  writer.insertUses(6, "a");
  writer.insertUses(7, "d");

  writer.insertUsesProcedure("main", "a");
  writer.insertUsesProcedure("main", "b");
  writer.insertUsesProcedure("main", "c");
  writer.insertUsesProcedure("second", "d");
  writer.insertUsesProcedure("second", "d");

  // UsesS: Uses(stmtRef, entRef)

  SECTION("(int, synonym)") {
    // Select v such that Uses(4, v)
    std::shared_ptr<Strategy> usesStrategy =
        std::make_shared<StmtEntArgStrategy>(StrategyType::USES_S, "4",
                                             StmtRefType::INTEGER, "v",
                                             EntRefType::VARIABLE);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_v, {{usesStrategy}});
    std::list<std::string> expected = {"a", "c"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("(int, wildcard)") {
    // Select v such that Uses(4, _)
    std::shared_ptr<Strategy> usesStrategy =
        std::make_shared<StmtEntArgStrategy>(StrategyType::USES_S, "4",
                                             StmtRefType::INTEGER, "_",
                                             EntRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_v, {{usesStrategy}});
    std::list<std::string> expected = {"a", "b", "c", "d"};
    REQUIRE(result == expected);
  }

  SECTION("(int, ident)") {
    // Select v such that Uses(4, "a")
    std::shared_ptr<Strategy> usesStrategy =
        std::make_shared<StmtEntArgStrategy>(StrategyType::USES_S, "4",
                                             StmtRefType::INTEGER, "a",
                                             EntRefType::IDENT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_v, {{usesStrategy}});
    std::list<std::string> expected = {"a", "b", "c", "d"};
    REQUIRE(result == expected);
  }

  SECTION("(synonym, synonym)") {
    // Select v such that Uses(pn, v)
    std::shared_ptr<Strategy> usesStrategy =
        std::make_shared<StmtEntArgStrategy>(StrategyType::USES_S, "pn",
                                             StmtRefType::PRINT, "v",
                                             EntRefType::VARIABLE);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_v, {{usesStrategy}});
    std::list<std::string> expected = {"a", "d"};
    REQUIRE(result == expected);

    // Select a such that Uses(a, v)
    std::shared_ptr<Strategy> usesStrategy2 =
        std::make_shared<StmtEntArgStrategy>(StrategyType::USES_S, "a",
                                             StmtRefType::ASSIGN, "v",
                                             EntRefType::VARIABLE);
    std::list<std::string> result2 = Evaluator::getResultList(
        reader, Strategies::select_a, {{usesStrategy}});
    std::list<std::string> expected2 = {"1", "4", "5", "6"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result2, expected2));
  }

  SECTION("(synonym, wildcard)") {
    // Select a such that Uses(a, _)
    std::shared_ptr<Strategy> usesStrategy =
        std::make_shared<StmtEntArgStrategy>(StrategyType::USES_S, "a",
                                             StmtRefType::ASSIGN, "_",
                                             EntRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{usesStrategy}});
    std::list<std::string> expected = {"1", "4", "5", "6"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("(synonym, ident)") {
    // Select s such that Uses(s, "c")
    std::shared_ptr<Strategy> usesStrategy =
        std::make_shared<StmtEntArgStrategy>(StrategyType::USES_S, "s",
                                             StmtRefType::STMT, "c",
                                             EntRefType::IDENT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{usesStrategy}});
    std::list<std::string> expected = {"3", "4", "5"};
    REQUIRE(result == expected);
  }

  // UsesP: Uses(entRef, entRef)

  SECTION("(ident, ident)") {
    // Select p such that Uses("main", "b")
    std::shared_ptr<Strategy> usesStrategy =
        std::make_shared<EntEntArgStrategy>(StrategyType::USES_P, "main",
                                            EntRefType::IDENT, "b",
                                            EntRefType::IDENT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_p, {{usesStrategy}});
    std::list<std::string> expected = {"main", "second"};
    REQUIRE(result == expected);
  }

  SECTION("(ident, wildcard)") {
    // Select p such that Uses("main", _)
    std::shared_ptr<Strategy> usesStrategy =
        std::make_shared<EntEntArgStrategy>(StrategyType::USES_P, "main",
                                            EntRefType::IDENT, "_",
                                            EntRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_p, {{usesStrategy}});
    std::list<std::string> expected = {"main", "second"};
    REQUIRE(result == expected);
  }

  SECTION("(ident, synonym)") {
    // Select v such that Uses("main", v)
    std::shared_ptr<Strategy> usesStrategy =
        std::make_shared<EntEntArgStrategy>(StrategyType::USES_P, "main",
                                            EntRefType::IDENT, "v",
                                            EntRefType::VARIABLE);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_v, {{usesStrategy}});
    std::list<std::string> expected = {"a", "b", "c"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));
  }

  SECTION("(synonym, synonym)") {
    // Select p such that Uses(p, v)
    std::shared_ptr<Strategy> usesStrategy =
        std::make_shared<EntEntArgStrategy>(StrategyType::USES_P, "p",
                                            EntRefType::PROCEDURE, "v",
                                            EntRefType::VARIABLE);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_p, {{usesStrategy}});
    std::list<std::string> expected = {"main", "second"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result, expected));

    // Select v such that Uses(p, v)
    std::list<std::string> result2 = Evaluator::getResultList(
        reader, Strategies::select_v, {{usesStrategy}});
    std::list<std::string> expected2 = {"a", "b", "c", "d"};
    REQUIRE(TestUtil::removeDuplicatesAndCompare(result2, expected2));
  }

  SECTION("(synonym, ident)") {
    // Select p such that Uses(p, "d")
    std::shared_ptr<Strategy> usesStrategy =
        std::make_shared<EntEntArgStrategy>(StrategyType::USES_P, "p",
                                            EntRefType::PROCEDURE, "d",
                                            EntRefType::IDENT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_p, {{usesStrategy}});
    std::list<std::string> expected = {"second"};
    REQUIRE(result == expected);
  }

  SECTION("(synonym, wildcard)") {
    // Select p such that Uses(p, _)
    std::shared_ptr<Strategy> usesStrategy =
        std::make_shared<EntEntArgStrategy>(StrategyType::USES_P, "p",
                                            EntRefType::PROCEDURE, "_",
                                            EntRefType::WILDCARD);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_p, {{usesStrategy}});
    std::list<std::string> expected = {"main", "second"};
    REQUIRE(result == expected);
  }

  // Cleanup
  writer.clearPKB();
}
