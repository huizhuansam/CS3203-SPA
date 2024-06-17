#include "strategy/WithStrategy.h"
#include "strategy/strategy_types/PatternStrategy.h"
#include "strategy/strategy_types/StmtEntArgStrategy.h"
#include "strategy/strategy_types/StmtStmtArgStrategy.h"

using namespace QPS;

namespace TestStrategies {
// Uses("5", "y")
const std::shared_ptr<Strategy> uses1 = std::make_shared<StmtEntArgStrategy>(
    StrategyType::USES_S, "5", StmtRefType::INTEGER, "y", EntRefType::VARIABLE);

// Uses(s1, v1)
const std::shared_ptr<Strategy> uses2 = std::make_shared<StmtEntArgStrategy>(
    StrategyType::USES_S, "s1", StmtRefType::STMT, "v1", EntRefType::VARIABLE);

// Affects(a1, a2)
const std::shared_ptr<Strategy> affects = std::make_shared<StmtStmtArgStrategy>(
    StrategyType::AFFECTS, "a1", StmtRefType::ASSIGN, "a2",
    StmtRefType::ASSIGN);

// with a1.stmt# = 20
const std::shared_ptr<Strategy> with = std::make_shared<WithStrategy>(
    "a1", RefType::ASSIGN_STMTNO, "20", RefType::INTEGER);

// Parent(s1, s2)
const std::shared_ptr<Strategy> parent = std::make_shared<StmtStmtArgStrategy>(
    StrategyType::PARENT, "s1", StmtRefType::STMT, "s2", StmtRefType::STMT);

// pattern a2 ("a", _)
const std::shared_ptr<Strategy> pattern1 = std::make_shared<PatternStrategy>(
    StrategyType::ASSIGN_PATTERN, "a2", "\"a\"", EntRefType::IDENT,
    std::vector<std::string>{"_"}, ExprSpecType::WILDCARD);

// Next(s2, s3)
const std::shared_ptr<Strategy> next = std::make_shared<StmtStmtArgStrategy>(
    StrategyType::NEXT, "s2", StmtRefType::STMT, "s3", StmtRefType::STMT);

// Modifies(s1, "x")
const std::shared_ptr<Strategy> modifies1 =
    std::make_shared<StmtEntArgStrategy>(StrategyType::MODIFIES_S, "s1",
                                         StmtRefType::STMT, "\"x\"",
                                         EntRefType::IDENT);

// Modifies(a, v2)
const std::shared_ptr<Strategy> modifies2 =
    std::make_shared<StmtEntArgStrategy>(StrategyType::MODIFIES_S, "a",
                                         StmtRefType::ASSIGN, "v2",
                                         EntRefType::VARIABLE);

// pattern a (v1, "x")
const std::shared_ptr<Strategy> pattern2 = std::make_shared<PatternStrategy>(
    StrategyType::ASSIGN_PATTERN, "a", "v1", EntRefType::VARIABLE,
    std::vector<std::string>{"\"x\""}, ExprSpecType::EXPR);
}  // namespace TestStrategies
