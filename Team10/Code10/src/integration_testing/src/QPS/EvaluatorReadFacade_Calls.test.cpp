#include "ReadFacade.h"
#include "WriteFacade.h"
#include "catch.hpp"
#include "evaluator/Evaluator.h"
#include "strategy/TupleSelectStrategy.h"
#include "strategy/strategy_types/EntEntArgStrategy.h"

using namespace QPS;

// QPS::Evaluator integration with PKB ReadFacade for Calls/* relationship

TEST_CASE("QPS::Evaluator integration with ReadFacade", "[Calls][Calls*]") {
  // Setup
  WriteFacade writer{};
  writer.clearPKB();
  ReadFacade reader{};

  // Write data to PKB
  // ProcA --> ProcB --> Proc C
  // ProcA --> ProcC
  // ProcB --> ProcD
  writer.addProcedure("ProcA");
  writer.addProcedure("ProcB");
  writer.addProcedure("ProcC");
  writer.addProcedure("ProcD");
  writer.insertCallsRelationship("ProcA", "ProcB");
  writer.insertCallsRelationship("ProcB", "ProcC");
  writer.insertCallsRelationship("ProcA", "ProcC");
  writer.insertCallsRelationship("ProcB", "ProcD");

  auto selectStrategy = std::make_shared<TupleSelectStrategy>(
      std::vector<std::string>{"p"},
      std::vector<SynonymType>{SynonymType::PROCEDURE},
      std::vector<AttrNameType>{AttrNameType::NONE});
  std::list<std::string> EMPTY_RESULT;

  // Calls

  SECTION("Select p such that Calls(wildcard,wildcard)") {
    // Select p such that Calls(_,_)
    auto callsStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS, "_", EntRefType::WILDCARD, "_",
        EntRefType::WILDCARD);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsStrategy}});
    REQUIRE(result.size() == 4);
  }

  SECTION("Select p such that Calls(wildcard,synonym)") {
    // Select p such that Calls(_,p)
    auto callsStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS, "_", EntRefType::WILDCARD, "p",
        EntRefType::PROCEDURE);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"ProcB", "ProcC", "ProcD"};
    REQUIRE(result == expected);
  }

  SECTION("Select p such that Calls(synonym,wildcard)") {
    // Select p such that Calls(p,_)
    auto callsStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS, "p", EntRefType::PROCEDURE, "_",
        EntRefType::WILDCARD);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsStrategy}});
    std::list<std::string> expected = {"ProcA", "ProcB"};
    REQUIRE(result == expected);
  }

  SECTION("Select p such that Calls(wildcard,ident)") {
    // Select p such that Calls(_,"ProcC")
    auto callsStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS, "_", EntRefType::WILDCARD, "ProcC",
        EntRefType::IDENT);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsStrategy}});
    REQUIRE(result.size() == 4);
  }

  SECTION(
      "Select p such that Calls(wildcard,ident) - Calls clause evaluates to "
      "false") {
    // Select p such that Calls(_,"ProcA")
    auto callsStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS, "p", EntRefType::PROCEDURE, "ProcA",
        EntRefType::IDENT);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsStrategy}});
    REQUIRE(result.empty() == true);
  }

  SECTION("Select p such that Calls(ident,wildcard)") {
    // Select p such that Calls("ProcB",_)
    auto callsStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS, "ProcB", EntRefType::IDENT, "_",
        EntRefType::WILDCARD);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsStrategy}});
    REQUIRE(result.size() == 4);
  }

  SECTION(
      "Select p such that Calls(ident,wildcard) - Calls clause evaluates to "
      "false") {
    // Select p such that Calls("ProcE",_)
    auto callsStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS, "ProcE", EntRefType::IDENT, "_",
        EntRefType::WILDCARD);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsStrategy}});
    REQUIRE(result == EMPTY_RESULT);
  }

  SECTION("Select p such that Calls(ident,ident)") {
    // Select p such that Calls("ProcA","ProcB")
    auto callsStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS, "ProcA", EntRefType::IDENT, "ProcB",
        EntRefType::IDENT);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsStrategy}});
    REQUIRE(result.size() == 4);
  }

  SECTION(
      "Select p such that Calls(ident,ident) - Calls clause evaluates to "
      "false") {
    // Select p such that Calls("ProcA","ProcB")
    auto callsStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS, "ProcA", EntRefType::IDENT, "ProcD",
        EntRefType::IDENT);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsStrategy}});
    REQUIRE(result == EMPTY_RESULT);
  }

  SECTION("Select p such that Calls(ident,synonym)") {
    // Select p such that Calls("ProcB",p)
    auto callsStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS, "ProcB", EntRefType::IDENT, "p",
        EntRefType::PROCEDURE);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"ProcC", "ProcD"};
    REQUIRE(result == expected);
  }

  SECTION("Select p such that Calls(synonym,ident)") {
    // Select p such that Calls(p, "ProcC")
    auto callsStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS, "p", EntRefType::PROCEDURE, "ProcC",
        EntRefType::IDENT);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsStrategy}});
    std::list<std::string> expected = {"ProcA", "ProcB"};
    REQUIRE(result == expected);
  }

  SECTION("Select p such that Calls(synonym,synonym)") {
    // Select p such that Calls(p, p2)
    auto callsStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS, "p", EntRefType::PROCEDURE, "p2",
        EntRefType::PROCEDURE);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"ProcA", "ProcB"};
    REQUIRE(result == expected);
  }

  // Calls*

  SECTION("Select p such that Calls*(wildcard,wildcard)") {
    // Select p such that Calls*(_,_)
    auto callsTStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS_T, "_", EntRefType::WILDCARD, "_",
        EntRefType::WILDCARD);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsTStrategy}});
    REQUIRE(result.size() == 4);
  }

  SECTION("Select p such that Calls*(wildcard,synonym)") {
    // Select p such that Calls*(_,p)
    auto callsTStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS_T, "_", EntRefType::WILDCARD, "p",
        EntRefType::PROCEDURE);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsTStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"ProcB", "ProcC", "ProcD"};
    REQUIRE(result == expected);
  }

  SECTION("Select p such that Calls*(synonym,wildcard)") {
    // Select p such that Calls*(p,_)
    auto callsTStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS_T, "p", EntRefType::PROCEDURE, "_",
        EntRefType::WILDCARD);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsTStrategy}});
    std::list<std::string> expected = {"ProcA", "ProcB"};
    REQUIRE(result == expected);
  }

  SECTION("Select p such that Calls*(wildcard,ident)") {
    // Select p such that Calls*(_,"ProcC")
    auto callsTStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS_T, "_", EntRefType::WILDCARD, "ProcC",
        EntRefType::IDENT);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsTStrategy}});
    REQUIRE(result.size() == 4);
  }

  SECTION(
      "Select p such that Calls*(wildcard,ident) - Calls clause evaluates to "
      "false") {
    // Select p such that Calls*(_,"ProcA")
    auto callsTStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS_T, "p", EntRefType::PROCEDURE, "ProcA",
        EntRefType::IDENT);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsTStrategy}});
    REQUIRE(result.empty() == true);
  }

  SECTION("Select p such that Calls*(ident,wildcard)") {
    // Select p such that Calls*("ProcB",_)
    auto callsTStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS_T, "ProcB", EntRefType::IDENT, "_",
        EntRefType::WILDCARD);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsTStrategy}});
    REQUIRE(result.size() == 4);
  }

  SECTION(
      "Select p such that Calls*(ident,wildcard) - Calls clause evaluates to "
      "false") {
    // Select p such that Calls*("ProcE",_)
    auto callsTStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS_T, "ProcE", EntRefType::IDENT, "_",
        EntRefType::WILDCARD);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsTStrategy}});
    REQUIRE(result == EMPTY_RESULT);
  }

  SECTION("Select p such that Calls*(ident,ident)") {
    // Select p such that Calls*("ProcA","ProcD")
    auto callsTStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS_T, "ProcA", EntRefType::IDENT, "ProcD",
        EntRefType::IDENT);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsTStrategy}});
    REQUIRE(result.size() == 4);
  }

  SECTION(
      "Select p such that Calls*(ident,ident) - Calls clause evaluates to "
      "false") {
    // Select p such that Calls*("ProcB","ProcA")
    auto callsTStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS_T, "ProcB", EntRefType::IDENT, "ProcA",
        EntRefType::IDENT);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsTStrategy}});
    REQUIRE(result == EMPTY_RESULT);
  }

  SECTION("Select p such that Calls*(ident,synonym)") {
    // Select p such that Calls*("ProcA",p)
    auto callsTStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS_T, "ProcA", EntRefType::IDENT, "p",
        EntRefType::PROCEDURE);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsTStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"ProcB", "ProcC", "ProcD"};
    REQUIRE(result == expected);
  }

  SECTION("Select p such that Calls*(synonym,ident)") {
    // Select p such that Calls*(p, "ProcD")
    auto callsTStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS_T, "p", EntRefType::PROCEDURE, "ProcD",
        EntRefType::IDENT);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsTStrategy}});
    std::list<std::string> expected = {"ProcA", "ProcB"};
    REQUIRE(result == expected);
  }

  SECTION("Select p such that Calls*(synonym,synonym)") {
    // Select p such that Calls*(p1, p)
    auto callsTStrategy = std::make_shared<EntEntArgStrategy>(
        StrategyType::CALLS_T, "p1", EntRefType::PROCEDURE, "p",
        EntRefType::PROCEDURE);
    auto result =
        Evaluator::getResultList(reader, selectStrategy, {{callsTStrategy}});
    result.sort();
    result.unique();
    std::list<std::string> expected = {"ProcB", "ProcC", "ProcD"};
    REQUIRE(result == expected);
  }

  // Cleanup
  writer.clearPKB();
}