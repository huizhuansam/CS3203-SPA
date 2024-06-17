#include <memory>

#include "ReadFacadeStub.h"
#include "catch.hpp"
#include "result/Result.h"
#include "strategy/PriorityScore.h"
#include "strategy/WithStrategy.h"
#include "strategy/strategy_types/PatternStrategy.h"
#include "strategy/strategy_types/StmtStmtArgStrategy.h"
#include "strategy/strategy_types/StrategyType.h"

using namespace QPS;

namespace StrategyTest {
ReadFacadeStub readFacadeStub = ReadFacadeStub();

std::vector<std::string> WILDCARD = {"_"};
std::vector<std::string> EXPR = {"0"};
std::vector<std::string> IDENT = {"x"};

std::shared_ptr<Strategy> IF_SYN_WILDCARD_WILDCARD =
    std::make_shared<PatternStrategy>(
        StrategyType::IF_PATTERN, "p", "p1", EntRefType::PRINT,
        std::vector<std::string>{}, ExprSpecType::INVALID);
std::shared_ptr<Strategy> IF_WILDCARD_WILDCARD_WILDCARD =
    std::make_shared<PatternStrategy>(
        StrategyType::IF_PATTERN, "a", "_", EntRefType::WILDCARD,
        std::vector<std::string>{}, ExprSpecType::INVALID);
std::shared_ptr<Strategy> AFFECTS_WILDCARD_INT =
    std::make_shared<StmtStmtArgStrategy>(StrategyType::AFFECTS, "_",
                                          StmtRefType::WILDCARD, "70",
                                          StmtRefType::INTEGER);
std::shared_ptr<Strategy> AFFECTS_STMT_WILDCARD =
    std::make_shared<StmtStmtArgStrategy>(StrategyType::AFFECTS, "s1",
                                          StmtRefType::STMT, "_",
                                          StmtRefType::WILDCARD);
std::shared_ptr<Strategy> AFFECTS_STMT_STMT =
    std::make_shared<StmtStmtArgStrategy>(StrategyType::AFFECTS, "s1",
                                          StmtRefType::STMT, "s2",
                                          StmtRefType::STMT);
std::shared_ptr<Strategy> PARENT_INT_WILDCARD =
    std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT, "3",
                                          StmtRefType::INTEGER, "_",
                                          StmtRefType::WILDCARD);
std::shared_ptr<Strategy> PARENT_SYNONYM_WILDCARD =
    std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT, "w",
                                          StmtRefType::WHILE, "_",
                                          StmtRefType::WILDCARD);
std::shared_ptr<Strategy> PARENT_SYNONYM_SYNONYM =
    std::make_shared<StmtStmtArgStrategy>(StrategyType::PARENT, "w",
                                          StmtRefType::WHILE, "a",
                                          StmtRefType::ASSIGN);
std::shared_ptr<Strategy> WHILE_IDENT = std::make_shared<PatternStrategy>(
    StrategyType::WHILE_PATTERN, "a", "_", EntRefType::IDENT,
    std::vector<std::string>{}, ExprSpecType::INVALID);
std::shared_ptr<Strategy> WHILE_SYN = std::make_shared<PatternStrategy>(
    StrategyType::WHILE_PATTERN, "a", "p", EntRefType::PROCEDURE,
    std::vector<std::string>{}, ExprSpecType::INVALID);
std::shared_ptr<Strategy> WITH_INT_STMT = std::make_shared<WithStrategy>(
    "5", RefType::INTEGER, "s", RefType::PRINT_STMTNO);
std::shared_ptr<Strategy> WITH_READ_PRINT = std::make_shared<WithStrategy>(
    "r", RefType::READ_VARNAME, "s", RefType::PRINT_VARNAME);
std::shared_ptr<Strategy> WITH_IDENT_IDENT =
    std::make_shared<WithStrategy>("r", RefType::IDENT, "s", RefType::IDENT);
std::vector<std::string> assign_vector = {"a"};
std::shared_ptr<Strategy> ASSIGN_SYN_WILDCARD =
    std::make_shared<PatternStrategy>(StrategyType::ASSIGN_PATTERN, "a", "p",
                                      EntRefType::PRINT, assign_vector,
                                      ExprSpecType::EXPR);
std::shared_ptr<Strategy> ASSIGN_IDENT_WILDCARD =
    std::make_shared<PatternStrategy>(StrategyType::ASSIGN_PATTERN, "a", "p",
                                      EntRefType::IDENT, assign_vector,
                                      ExprSpecType::EXPR);
std::shared_ptr<Strategy> FOLLOWST_SYNONYM_WILDCARD =
    std::make_shared<StmtStmtArgStrategy>(StrategyType::FOLLOWS_T, "a",
                                          StmtRefType::ASSIGN, "_",
                                          StmtRefType::WILDCARD);
std::shared_ptr<Strategy> NEXT_INT_INT = std::make_shared<StmtStmtArgStrategy>(
    StrategyType::NEXT, "2", StmtRefType::INTEGER, "9", StmtRefType::INTEGER);
std::shared_ptr<Strategy> NEXTT_INT_SYNONYM =
    std::make_shared<StmtStmtArgStrategy>(StrategyType::NEXT_T, "2",
                                          StmtRefType::INTEGER, "a",
                                          StmtRefType::ASSIGN);

TEST_CASE("Strategy synonym count") {
  SECTION("IF: Syn, Wildcard, Wildcard") {
    REQUIRE(IF_SYN_WILDCARD_WILDCARD->getSynonymCount() == 2);
  }
  SECTION("IF: Wildcard, Wildcard, Wildcard") {
    REQUIRE(IF_WILDCARD_WILDCARD_WILDCARD->getSynonymCount() == 1);
  }
  SECTION("Parent: Int, Wildcard") {
    REQUIRE(PARENT_INT_WILDCARD->getSynonymCount() == 0);
  }
  SECTION("Parent: Syn, Syn") {
    REQUIRE(PARENT_SYNONYM_WILDCARD->getSynonymCount() == 1);
  }
  SECTION("Parent: Syn, Syn") {
    REQUIRE(PARENT_SYNONYM_SYNONYM->getSynonymCount() == 2);
  }
  SECTION("While: Ident") { REQUIRE(WHILE_IDENT->getSynonymCount() == 1); }
  SECTION("While: Syn") { REQUIRE(WHILE_SYN->getSynonymCount() == 2); }
  SECTION("With: INT, Syn") { REQUIRE(WITH_INT_STMT->getSynonymCount() == 1); }
  SECTION("With: Syn, Syn") {
    REQUIRE(WITH_READ_PRINT->getSynonymCount() == 2);
  }
  SECTION("With: Ident, Ident") {
    REQUIRE(WITH_IDENT_IDENT->getSynonymCount() == 0);
  }
  SECTION("Assign: Syn") {
    REQUIRE(ASSIGN_SYN_WILDCARD->getSynonymCount() == 2);
  }
  SECTION("Assign: Syn") {
    REQUIRE(ASSIGN_IDENT_WILDCARD->getSynonymCount() == 1);
  }
  SECTION("Affects: Wildcard, Wildcard") {
    REQUIRE(AFFECTS_WILDCARD_INT->getSynonymCount() == 0);
  }
  SECTION("Affects: Syn, syn") {
    REQUIRE(AFFECTS_STMT_WILDCARD->getSynonymCount() == 1);
  }
  SECTION("Affects: Syn, syn") {
    REQUIRE(AFFECTS_STMT_STMT->getSynonymCount() == 2);
  }
}

TEST_CASE("Strategy get priority score") {
  SECTION("getPriorityScore") {
    REQUIRE(PARENT_INT_WILDCARD->getPriorityScore() ==
            PriorityScore::PRIORITY_1);

    REQUIRE(FOLLOWST_SYNONYM_WILDCARD->getPriorityScore() ==
            PriorityScore::PRIORITY_2);

    REQUIRE(NEXT_INT_INT->getPriorityScore() == PriorityScore::PRIORITY_3);

    REQUIRE(NEXTT_INT_SYNONYM->getPriorityScore() == PriorityScore::PRIORITY_4);

    REQUIRE(AFFECTS_WILDCARD_INT->getPriorityScore() ==
            PriorityScore::PRIORITY_5);

    REQUIRE(WITH_INT_STMT->getPriorityScore() == PriorityScore::PRIORITY_6);

    REQUIRE(IF_SYN_WILDCARD_WILDCARD->getPriorityScore() ==
            PriorityScore::PRIORITY_7);

    REQUIRE(ASSIGN_SYN_WILDCARD->getPriorityScore() ==
            PriorityScore::PRIORITY_8);
  }
}
}  // namespace StrategyTest
