#include "strategy/argument_types/StmtRefTypeController.h"

namespace QPS {
const std::unordered_set<StmtRefType> StmtRefTypeController::boolStrategyTypes =
    {StmtRefType::WILDCARD, StmtRefType::INTEGER};

const std::unordered_map<SynonymType, StmtRefType>
    StmtRefTypeController::synonymTypeToStmtRefType = {
        {SynonymType::STMT, StmtRefType::STMT},
        {SynonymType::READ, StmtRefType::READ},
        {SynonymType::PRINT, StmtRefType::PRINT},
        {SynonymType::CALL, StmtRefType::CALL},
        {SynonymType::WHILE, StmtRefType::WHILE},
        {SynonymType::IF, StmtRefType::IF},
        {SynonymType::ASSIGN, StmtRefType::ASSIGN},
        {SynonymType::VARIABLE, StmtRefType::VARIABLE},
        {SynonymType::CONSTANT, StmtRefType::CONSTANT},
        {SynonymType::PROCEDURE, StmtRefType::PROCEDURE}};

bool StmtRefTypeController::isBoolResult(const StmtRefType stmtRefType) {
  return boolStrategyTypes.count(stmtRefType) > 0;
}

StmtRefType StmtRefTypeController::getStmtRefType(
    const SynonymType synonymType) {
  return synonymTypeToStmtRefType.at(synonymType);
}
}  // namespace QPS
