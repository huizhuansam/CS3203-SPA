#include "strategy/strategy_types/PatternStrategy.h"

namespace QPS {
PatternStrategy::PatternStrategy(StrategyType strategyType, std::string synonym,
                                 std::string arg1, EntRefType argType1,
                                 std::vector<std::string> arg2,
                                 ExprSpecType argType2)
    : strategyType(strategyType),
      synonym(std::move(synonym)),
      arg1(std::move(arg1)),
      argType1(argType1),
      arg2(std::move(arg2)),
      argType2(argType2) {
  setPriorityScore(PriorityScore::getPriorityScore(strategyType));
}

Result PatternStrategy::evaluateValues(ReadFacade& readFacade) {
  setArgFlags();

  std::unordered_map<std::string, int> headers = generateHeaders();

  std::vector<std::vector<std::string>> data;

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
      stmtVarPairSets = getStmtVarPairSet(readFacade);

  for (const auto& stmtVarPair : stmtVarPairSets) {
    std::string stmtNo = stmtVarPair.first;
    std::string var = stmtVarPair.second;
    if (isArg1Variable || isArg1Wildcard || (isArg1Ident && var == arg1)) {
      data.push_back(generateDataRow(stmtNo, var));
    }
  }

  return {headers, data};
}

std::unordered_set<std::pair<std::string, std::string>, PairHash>
PatternStrategy::getStmtVarPairSet(ReadFacade& readFacade) const {
  std::unordered_set<std::pair<std::string, std::string>, PairHash>
      stmtVarPairSets;
  if (isAssignPattern) {
    stmtVarPairSets =
        isExpr          ? readFacade.getAssignExpPairsSynonymExactMatch(arg2)
        : isPartialExpr ? readFacade.getAssignExpPairsSynonymPartialMatch(arg2)
                        : readFacade.getAllAssignExpPairs();
  }
  if (isWhilePattern || isIfPattern) {
    auto pairSets = isWhilePattern
                        ? readFacade.getAllWhileControlVariablePairs()
                        : readFacade.getAllIfControlVariablePairs();
    for (const auto& pair : pairSets) {
      stmtVarPairSets.insert({std::to_string(pair.first), pair.second});
    }
  }

  return stmtVarPairSets;
}

std::string PatternStrategy::getSynonym() { return synonym; }

std::string PatternStrategy::getArg1() { return arg1; }

EntRefType PatternStrategy::getArgType1() { return argType1; }

std::vector<std::string> PatternStrategy::getArg2() { return arg2; }

ExprSpecType PatternStrategy::getArgType2() { return argType2; }

std::unordered_set<std::string> PatternStrategy::getSynonyms() {
  std::unordered_set<std::string> synonyms = {synonym};
  if (EntRefTypeController::isSynonymType(argType1)) {
    synonyms.insert(arg1);
  }
  return synonyms;
}

void PatternStrategy::setArgFlags() {
  this->isAssignPattern = strategyType == StrategyType::ASSIGN_PATTERN;
  this->isWhilePattern = strategyType == StrategyType::WHILE_PATTERN;
  this->isIfPattern = strategyType == StrategyType::IF_PATTERN;

  this->isArg1Synonym = EntRefTypeController::isSynonymType(argType1);
  this->isArg1Variable = argType1 == EntRefType::VARIABLE;
  this->isArg1Ident = argType1 == EntRefType::IDENT;
  this->isArg1Wildcard = argType1 == EntRefType::WILDCARD;

  this->isExpr = argType2 == ExprSpecType::EXPR;
  this->isPartialExpr = argType2 == ExprSpecType::WILDCARD_EXPR;
}

std::unordered_map<std::string, int> PatternStrategy::generateHeaders() const {
  std::unordered_map<std::string, int> headers = {{synonym, 0}};
  if (isArg1Synonym) {
    headers[arg1] = 1;
  }
  return headers;
}

std::vector<std::string> PatternStrategy::generateDataRow(
    std::string& stmtNo, std::string& var) const {
  std::vector<std::string> row;
  row.push_back(stmtNo);
  if (isArg1Variable) {
    row.push_back(var);
  }
  return row;
}

void PatternStrategy::replaceSynFromWithClause(
    std::unordered_map<std::string, std::pair<std::string, bool>>&
        replaceableSynValues,
    [[maybe_unused]] std::unordered_map<std::string, SynonymType>&
        replaceableStmtSyn) {
  bool canArg1BeReplaced =
      replaceableSynValues.find(arg1) != replaceableSynValues.end();
  if (canArg1BeReplaced) {
    bool isReplaceValueInteger = replaceableSynValues.at(arg1).second;
    if (!isReplaceValueInteger) {
      arg1 = replaceableSynValues.at(arg1).first;
      argType1 = EntRefType::IDENT;
    }
  }
}
}  // namespace QPS
