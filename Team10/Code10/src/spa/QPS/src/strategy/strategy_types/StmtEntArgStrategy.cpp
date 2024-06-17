#include "strategy/strategy_types/StmtEntArgStrategy.h"

namespace QPS {
const std::unordered_map<StrategyType, ReadFacadeIntReturnStrMethod>
    StmtEntArgStrategy::strategyToReadFacadeMethodMap = {
        {
            StrategyType::MODIFIES_S,
            [](int stmtNo, ReadFacade readFacade) {
              return readFacade.getVarsModifiedByStmt(stmtNo);
            },
        },
        {
            StrategyType::USES_S,
            [](int stmtNo, ReadFacade readFacade) {
              return readFacade.getVarsUsedByStmt(stmtNo);
            },
        },
};

StmtEntArgStrategy::StmtEntArgStrategy(StrategyType strategyType,
                                       std::string arg1, StmtRefType argType1,
                                       std::string arg2, EntRefType argType2)
    : strategyType(strategyType),
      arg1(std::move(arg1)),
      argType1(argType1),
      arg2(std::move(arg2)),
      argType2(argType2) {
  setPriorityScore(PriorityScore::getPriorityScore(strategyType));
}

Result StmtEntArgStrategy::evaluateValues(ReadFacade& readFacade) {
  setArgFlags();
  setEvaluationSets(readFacade);

  std::unordered_map<std::string, int> headers = generateHeaders();
  auto key = std::make_tuple(strategyType, argType1, argType2);

  if (cache->isCached(key)) {
    return {headers, cache->get(key)};
  }

  for (int stmt1 : argSet1) {
    relationMap[stmt1] =
        strategyToReadFacadeMethodMap.at(strategyType)(stmt1, readFacade);
  }

  std::vector<std::vector<std::string>> data;

  for (int stmt1 : argSet1) {
    std::unordered_set<std::string> matchArg2Sets = relationMap[stmt1];
    for (const std::string& matchArg2 : matchArg2Sets) {
      if (argSet2.find(matchArg2) != argSet2.end()) {
        auto row = generateDataRow(stmt1, const_cast<std::string&>(matchArg2));
        data.push_back(row);
        if (isArg2Wildcard) {
          break;
        }
      }
    }
  }

  return {headers, arg1 == arg2 ? data : cache->storeAndReturn(key, data)};
}

bool StmtEntArgStrategy::evaluateBoolean(ReadFacade& readFacade) {
  setArgFlags();
  setEvaluationSets(readFacade);

  for (int stmt1 : argSet1) {
    relationMap[stmt1] =
        strategyToReadFacadeMethodMap.at(strategyType)(stmt1, readFacade);
  }

  for (int stmt1 : argSet1) {
    std::unordered_set<std::string> matchArg2Sets = relationMap[stmt1];
    for (const std::string& matchArg2 : matchArg2Sets) {
      if (argSet2.find(matchArg2) != argSet2.end()) {
        return true;
      }
    }
  }
  return false;
}

std::string StmtEntArgStrategy::getArg1() { return arg1; }

StmtRefType StmtEntArgStrategy::getArgType1() { return argType1; }

std::string StmtEntArgStrategy::getArg2() { return arg2; }

EntRefType StmtEntArgStrategy::getArgType2() { return argType2; }

bool StmtEntArgStrategy::isBooleanStrategy() {
  return StmtRefTypeController::isBoolResult(argType1) &&
         EntRefTypeController::isBoolResult(argType2);
}

std::unordered_set<std::string> StmtEntArgStrategy::getSynonyms() {
  std::unordered_set<std::string> synonyms;
  if (!StmtRefTypeController::isBoolResult(argType1)) {
    synonyms.insert(arg1);
  }
  if (EntRefTypeController::isSynonymType(argType2)) {
    synonyms.insert(arg2);
  }
  return synonyms;
}

void StmtEntArgStrategy::setArgFlags() {
  isArg1Integer = argType1 == StmtRefType::INTEGER;
  isArg2Ident = argType2 == EntRefType::IDENT;

  bool isArg1Wildcard = argType1 == StmtRefType::WILDCARD;
  isArg2Wildcard = argType2 == EntRefType::WILDCARD;

  isArg1Synonym = !isArg1Integer && !isArg1Wildcard;
  isArg2Synonym = !isArg2Ident && !isArg2Wildcard;
}

void StmtEntArgStrategy::setEvaluationSets(ReadFacade& readFacade) {
  if (isArg1Integer) {
    argSet1 = {std::stoi(arg1)};
  } else {
    argSet1 = Strategy::getAllStmtBySynonymType(argType1, readFacade);
  }

  if (isArg2Ident) {
    argSet2 = {arg2};
  } else {
    argSet2 = readFacade.getAllVariables();
  }
}

std::unordered_map<std::string, int> StmtEntArgStrategy::generateHeaders()
    const {
  std::unordered_map<std::string, int> headers;
  if (isArg1Synonym) {
    headers[arg1] = static_cast<int>(headers.size());
  }
  if (isArg2Synonym) {
    headers[arg2] = static_cast<int>(headers.size());
  }
  return headers;
}

std::vector<std::string> StmtEntArgStrategy::generateDataRow(
    int stmtNo, std::string& var) const {
  std::vector<std::string> row;
  if (isArg1Synonym) {
    row.push_back(std::to_string(stmtNo));
  }
  if (isArg2Synonym) {
    row.push_back(var);
  }
  return row;
}

void StmtEntArgStrategy::replaceSynFromWithClause(
    std::unordered_map<std::string, std::pair<std::string, bool>>&
        replaceableSynValues,
    std::unordered_map<std::string, SynonymType>& replaceableStmtSyn) {
  bool canArg1BeReplaced =
      replaceableSynValues.find(arg1) != replaceableSynValues.end();
  if (canArg1BeReplaced) {
    bool isReplaceValueInteger = replaceableSynValues.at(arg1).second;
    if (isReplaceValueInteger) {
      arg1 = replaceableSynValues.at(arg1).first;
      argType1 = StmtRefType::INTEGER;
    }
  }

  bool canArg2BeReplaced =
      replaceableSynValues.find(arg2) != replaceableSynValues.end();
  if (canArg2BeReplaced) {
    bool isReplaceValueInteger = replaceableSynValues.at(arg2).second;
    if (!isReplaceValueInteger) {
      arg2 = replaceableSynValues.at(arg2).first;
      argType2 = EntRefType::IDENT;
    }
  }

  bool canArg1SynonymBeReplaced =
      replaceableStmtSyn.find(arg1) != replaceableStmtSyn.end();
  if (canArg1SynonymBeReplaced) {
    argType1 =
        StmtRefTypeController::getStmtRefType(replaceableStmtSyn.at(arg1));
  }

  bool canArg2SynonymBeReplaced =
      replaceableStmtSyn.find(arg2) != replaceableStmtSyn.end();
  if (canArg2SynonymBeReplaced) {
    argType2 = EntRefTypeController::getEntRefType(replaceableStmtSyn.at(arg2));
  }
}
}  // namespace QPS
