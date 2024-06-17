#include "strategy/argument_types/EntRefTypeController.h"

namespace QPS {
const std::unordered_set<EntRefType> EntRefTypeController::boolStrategyTypes = {
    EntRefType::WILDCARD, EntRefType::IDENT};

const std::unordered_set<EntRefType> EntRefTypeController::synonymTypes = {
    EntRefType::STMT,     EntRefType::READ,     EntRefType::PRINT,
    EntRefType::CALL,     EntRefType::WHILE,    EntRefType::IF,
    EntRefType::ASSIGN,   EntRefType::VARIABLE, EntRefType::CONSTANT,
    EntRefType::PROCEDURE};

const std::unordered_map<SynonymType, EntRefType>
    EntRefTypeController::synonymTypeToEntRefType = {
        {SynonymType::STMT, EntRefType::STMT},
        {SynonymType::READ, EntRefType::READ},
        {SynonymType::PRINT, EntRefType::PRINT},
        {SynonymType::CALL, EntRefType::CALL},
        {SynonymType::WHILE, EntRefType::WHILE},
        {SynonymType::IF, EntRefType::IF},
        {SynonymType::ASSIGN, EntRefType::ASSIGN},
        {SynonymType::VARIABLE, EntRefType::VARIABLE},
        {SynonymType::CONSTANT, EntRefType::CONSTANT},
        {SynonymType::PROCEDURE, EntRefType::PROCEDURE}};

bool EntRefTypeController::isBoolResult(const EntRefType entRefType) {
  return boolStrategyTypes.count(entRefType) > 0;
}

bool EntRefTypeController::isSynonymType(const EntRefType entRefType) {
  return synonymTypes.count(entRefType) > 0;
}

EntRefType EntRefTypeController::getEntRefType(const SynonymType synonymType) {
  return synonymTypeToEntRefType.at(synonymType);
}
}  // namespace QPS
