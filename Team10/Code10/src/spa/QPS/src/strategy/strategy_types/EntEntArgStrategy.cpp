#include "strategy/strategy_types/EntEntArgStrategy.h"

namespace QPS {
const std::unordered_map<StrategyType, ReadFacadeStrMethod>
    EntEntArgStrategy::strategyToReadFacadeMethodMap = {
        {
            StrategyType::MODIFIES_P,
            [](std::string procedure, ReadFacade readFacade) {
              return readFacade.getVarsModifiedByProcedure(procedure);
            },
        },
        {
            StrategyType::USES_P,
            [](std::string procedure, ReadFacade readFacade) {
              return readFacade.getVarsUsedByProcedure(std::move(procedure));
            },
        },
        {
            StrategyType::CALLS,
            [](std::string procedure, ReadFacade readFacade) {
              return readFacade.getProcsThatIsCalledBy(procedure);
            },
        },
        {
            StrategyType::CALLS_T,
            [](std::string procedure, ReadFacade readFacade) {
              return readFacade.getProcsThatIsCalledByStar(procedure);
            },
        },
};

EntEntArgStrategy::EntEntArgStrategy(StrategyType strategyType,
                                     std::string arg1, EntRefType argType1,
                                     std::string arg2, EntRefType argType2)
    : strategyType(strategyType),
      arg1(std::move(arg1)),
      argType1(argType1),
      arg2(std::move(arg2)),
      argType2(argType2) {
  setPriorityScore(PriorityScore::getPriorityScore(strategyType));
}

Result EntEntArgStrategy::evaluateValues(ReadFacade& readFacade) {
  setArgFlags();
  setEvaluationSets(readFacade);

  std::unordered_map<std::string, int> headers = generateHeaders();
  auto key = std::make_tuple(strategyType, argType1, argType2);

  if (cache->isCached(key)) {
    return {headers, cache->get(key)};
  }

  for (const std::string& proc1 : argSet1) {
    relationMap[proc1] =
        strategyToReadFacadeMethodMap.at(strategyType)(proc1, readFacade);
  }

  std::vector<std::vector<std::string>> data;

  for (const std::string& proc1 : argSet1) {
    std::unordered_set<std::string> matchArg2Sets = relationMap[proc1];
    for (const std::string& matchArg2 : matchArg2Sets) {
      if (isBothArgSame && proc1 != matchArg2) {
        continue;
      }

      if (argSet2.find(matchArg2) != argSet2.end()) {
        auto row = generateDataRow(proc1, const_cast<std::string&>(matchArg2));
        data.push_back(row);
        if (isArg2Wildcard) {
          break;
        }
      }
    }
  }

  return {headers, arg1 == arg2 ? data : cache->storeAndReturn(key, data)};
}

bool EntEntArgStrategy::evaluateBoolean(ReadFacade& readFacade) {
  setArgFlags();
  setEvaluationSets(readFacade);

  for (const std::string& proc1 : argSet1) {
    relationMap[proc1] =
        strategyToReadFacadeMethodMap.at(strategyType)(proc1, readFacade);
  }

  for (const std::string& proc1 : argSet1) {
    std::unordered_set<std::string> matchArg2Sets = relationMap[proc1];
    for (const std::string& matchArg2 : matchArg2Sets) {
      if (argSet2.find(matchArg2) != argSet2.end()) {
        return true;
      }
    }
  }
  return false;
}

void EntEntArgStrategy::setArgFlags() {
  bool isArg1Wildcard = argType1 == EntRefType::WILDCARD;
  isArg2Wildcard = argType2 == EntRefType::WILDCARD;

  isArg1Ident = argType1 == EntRefType::IDENT;
  isArg2Ident = argType2 == EntRefType::IDENT;

  isArg1Synonym = !isArg1Ident && !isArg1Wildcard;
  isArg2Synonym = !isArg2Ident && !isArg2Wildcard;

  isBothArgSame = arg1 == arg2 && argType1 == argType2;
}

void EntEntArgStrategy::setEvaluationSets(ReadFacade& readFacade) {
  if (isArg1Ident) {
    argSet1 = {arg1};
  } else {
    argSet1 = readFacade.getAllProcedures();
  }

  bool isCalls = strategyType == StrategyType::CALLS ||
                 strategyType == StrategyType::CALLS_T;
  if (isArg2Ident) {
    argSet2 = {arg2};
  } else if (isCalls) {
    argSet2 = readFacade.getAllProcedures();
  } else {
    argSet2 = readFacade.getAllVariables();
  }
}

std::string EntEntArgStrategy::getArg1() { return arg1; }

EntRefType EntEntArgStrategy::getArgType1() { return argType1; }

std::string EntEntArgStrategy::getArg2() { return arg2; }

EntRefType EntEntArgStrategy::getArgType2() { return argType2; }

bool EntEntArgStrategy::isBooleanStrategy() {
  return EntRefTypeController::isBoolResult(argType1) &&
         EntRefTypeController::isBoolResult(argType2);
}

std::unordered_set<std::string> EntEntArgStrategy::getSynonyms() {
  std::unordered_set<std::string> synonyms;
  if (EntRefTypeController::isSynonymType(argType1)) {
    synonyms.insert(arg1);
  }
  if (EntRefTypeController::isSynonymType(argType2)) {
    synonyms.insert(arg2);
  }
  return synonyms;
}

std::unordered_map<std::string, int> EntEntArgStrategy::generateHeaders()
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

std::vector<std::string> EntEntArgStrategy::generateDataRow(
    const std::string& arg1Value, std::string& arg2Value) const {
  std::vector<std::string> row;
  if (isArg1Synonym) {
    row.push_back(arg1Value);
  }
  if (isArg2Synonym) {
    row.push_back(arg2Value);
  }
  return row;
}

void EntEntArgStrategy::replaceSynFromWithClause(
    std::unordered_map<std::string, std::pair<std::string, bool>>&
        replaceableSynValues,
    std::unordered_map<std::string, SynonymType>& replaceableStmtSyn) {
  bool canArg1BeReplaced =
      replaceableSynValues.find(arg1) != replaceableSynValues.end();
  if (canArg1BeReplaced) {
    bool isReplaceValueInteger = replaceableSynValues.at(arg1).second;
    if (!isReplaceValueInteger) {
      arg1 = replaceableSynValues.at(arg1).first;
      argType1 = EntRefType::IDENT;
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
    argType1 = EntRefTypeController::getEntRefType(replaceableStmtSyn.at(arg1));
  }

  bool canArg2SynonymBeReplaced =
      replaceableStmtSyn.find(arg2) != replaceableStmtSyn.end();
  if (canArg2SynonymBeReplaced) {
    argType2 = EntRefTypeController::getEntRefType(replaceableStmtSyn.at(arg2));
  }
}
}  // namespace QPS
