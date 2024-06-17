#include "cache/Cache.h"

#include <string>
#include <vector>

#include "catch.hpp"
#include "result/Result.h"
#include "strategy/argument_types/EntRefType.h"
#include "strategy/argument_types/ExprSpecType.h"
#include "strategy/argument_types/RefType.h"
#include "strategy/argument_types/StmtRefType.h"
#include "strategy/strategy_types/StrategyType.h"

using namespace QPS;

TEST_CASE("Test for hashing robustness", "[Cache]") {
  Cache cache{};

  SECTION("Every single permutation for such that and pattern clause") {
    std::vector<std::vector<std::string>> v = {{"dummy"}};

    std::vector<StrategyType> strategyTypes = {
        StrategyType::FOLLOWS, StrategyType::FOLLOWS_T,
        StrategyType::PARENT,  StrategyType::PARENT_T,
        StrategyType::NEXT,    StrategyType::NEXT_T,
        StrategyType::AFFECTS, StrategyType::MODIFIES_P,
        StrategyType::USES_P,  StrategyType::CALLS,
        StrategyType::CALLS_T, StrategyType::MODIFIES_S,
        StrategyType::USES_S,
    };
    std::vector<EntRefType> entRefTypes = {
        EntRefType::STMT,      EntRefType::READ,     EntRefType::PRINT,
        EntRefType::CALL,      EntRefType::WHILE,    EntRefType::IF,
        EntRefType::ASSIGN,    EntRefType::VARIABLE, EntRefType::CONSTANT,
        EntRefType::PROCEDURE, EntRefType::WILDCARD,
    };
    std::vector<StmtRefType> stmtRefTypes = {
        StmtRefType::STMT,      StmtRefType::READ,     StmtRefType::PRINT,
        StmtRefType::CALL,      StmtRefType::WHILE,    StmtRefType::IF,
        StmtRefType::ASSIGN,    StmtRefType::VARIABLE, StmtRefType::CONSTANT,
        StmtRefType::PROCEDURE, StmtRefType::WILDCARD,
    };

    for (auto& strategyType : strategyTypes) {
      for (auto& entRefType1 : entRefTypes) {
        for (auto& entRefType2 : entRefTypes) {
          auto k = std::make_tuple(strategyType, entRefType1, entRefType2);
          REQUIRE(cache.isCached(k) == false);
          auto& r1 = cache.storeAndReturn(k, v);
          REQUIRE(cache.isCached(k) == true);
          REQUIRE(r1 == v);
          auto& r2 = cache.get(k);
          REQUIRE(r2 == v);
          REQUIRE(r2 == r1);
        }
      }
    }

    for (auto& strategyType : strategyTypes) {
      for (auto& stmtRefType1 : stmtRefTypes) {
        for (auto& stmtRefType2 : stmtRefTypes) {
          auto k = std::make_tuple(strategyType, stmtRefType1, stmtRefType2);
          REQUIRE(cache.isCached(k) == false);
          auto& r1 = cache.storeAndReturn(k, v);
          REQUIRE(cache.isCached(k) == true);
          REQUIRE(r1 == v);
          auto& r2 = cache.get(k);
          REQUIRE(r2 == v);
        }
      }
    }

    for (auto& strategyType : strategyTypes) {
      for (auto& entRefType : entRefTypes) {
        for (auto& stmtRefType : stmtRefTypes) {
          auto k = std::make_tuple(strategyType, entRefType, stmtRefType);
          REQUIRE(cache.isCached(k) == false);
          auto& r1 = cache.storeAndReturn(k, v);
          REQUIRE(cache.isCached(k) == true);
          REQUIRE(r1 == v);
          auto& r2 = cache.get(k);
          REQUIRE(r2 == v);
          REQUIRE(r2 == r1);
        }
      }
    }
  }

  SECTION("Test hash equality for with clause") {
    Result r{};
    std::vector<RefType> refTypes = {RefType::IDENT,
                                     RefType::INTEGER,
                                     RefType::PROCEDURE_PROCNAME,
                                     RefType::CALL_PROCNAME,
                                     RefType::VARIABLE_VARNAME,
                                     RefType::READ_VARNAME,
                                     RefType::PRINT_VARNAME,
                                     RefType::CONSTANT_VALUE,
                                     RefType::STMT_STMTNO,
                                     RefType::READ_STMTNO,
                                     RefType::PRINT_STMTNO,
                                     RefType::CALL_STMTNO,
                                     RefType::WHILE_STMTNO,
                                     RefType::IF_STMTNO,
                                     RefType::ASSIGN_STMTNO,
                                     RefType::NONE};
    // the key is in the form of (RefType, std::string, RefType, std::string)
    // two keys are equal if they have the same RefType and std::string values
    // or if the left and right (RefType, std::string) are swapped
    for (auto& refType1 : refTypes) {
      for (auto& refType2 : refTypes) {
        auto k1 = std::make_tuple(refType1, "a", refType2, "b");
        auto k2 = std::make_tuple(refType2, "b", refType1, "a");

        REQUIRE(cache.isCached(k1) == false);
        REQUIRE(cache.isCached(k2) == false);
        auto& r1 = cache.storeAndReturn(k1, r);
        REQUIRE(cache.isCached(k1) == true);
        REQUIRE(cache.isCached(k2) == true);
        REQUIRE(r == r1);
        auto& r2 = cache.get(k2);
        REQUIRE(r2 == r);
        REQUIRE(r2 == r1);
      }
    }
  }
}
