#include "strategy/strategy_types/StmtStmtArgStrategy.h"

namespace QPS {
const std::unordered_map<StrategyType, ReadFacadeIntReturnIntMethod>
    StmtStmtArgStrategy::strategyToReadFacadeMethodMap = {
        {
            StrategyType::FOLLOWS,
            [](int stmt, ReadFacade readFacade) {
              return std::unordered_set<int>{
                  readFacade.getStmtThatFollowsAfter(stmt)};
            },
        },
        {
            StrategyType::FOLLOWS_T,
            [](int stmt, ReadFacade readFacade) {
              return readFacade.getAllStmtsThatFollowAfter(stmt);
            },
        },
        {
            StrategyType::PARENT,
            [](int stmt, ReadFacade readFacade) {
              return readFacade.getChildren(stmt);
            },
        },
        {
            StrategyType::PARENT_T,
            [](int stmt, ReadFacade readFacade) {
              return readFacade.getChildrenStar(stmt);
            },
        },
        {
            StrategyType::NEXT,
            [](int stmt, ReadFacade readFacade) {
              return readFacade.getStmtsNextOf(stmt);
            },
        },
        {
            StrategyType::NEXT_T,
            [](int stmt, ReadFacade readFacade) {
              return readFacade.getStmtsNextStarOf(stmt);
            },
        },
        {
            StrategyType::AFFECTS,
            [](int stmt, ReadFacade readFacade) {
              return readFacade.getStmtsAffectedBy(stmt);
            },
        },
};

StmtStmtArgStrategy::StmtStmtArgStrategy(StrategyType strategyType,
                                         std::string arg1, StmtRefType argType1,
                                         std::string arg2, StmtRefType argType2)
    : strategyType(strategyType),
      arg1(std::move(arg1)),
      argType1(argType1),
      arg2(std::move(arg2)),
      argType2(argType2) {
  setPriorityScore(PriorityScore::getPriorityScore(strategyType));
}

Result StmtStmtArgStrategy::evaluateValues(ReadFacade &readFacade) {
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

  std::unordered_set<int> visitedArg2;
  for (int stmt1 : argSet1) {
    std::unordered_set<int> matchStmts = relationMap[stmt1];
    for (int matchStmt : matchStmts) {
      if ((isBothArgSame && stmt1 != matchStmt) ||
          visitedArg2.find(matchStmt) != visitedArg2.end()) {
        continue;
      }

      if (argSet2.find(matchStmt) != argSet2.end()) {
        data.push_back(generateDataRow(stmt1, matchStmt));
        if (isArg1Wildcard) {
          visitedArg2.insert(matchStmt);
        }
        if (isArg2Wildcard) {
          break;
        }
      }
    }
  }

  return {headers, arg1 == arg2 ? data : cache->storeAndReturn(key, data)};
}

bool StmtStmtArgStrategy::evaluateBoolean(ReadFacade &readFacade) {
  setArgFlags();
  setEvaluationSets(readFacade);

  for (int stmt1 : argSet1) {
    relationMap[stmt1] =
        strategyToReadFacadeMethodMap.at(strategyType)(stmt1, readFacade);
  }

  for (int stmt1 : argSet1) {
    std::unordered_set<int> matchStmts = relationMap[stmt1];
    for (int matchStmt : matchStmts) {
      if (argSet2.find(matchStmt) != argSet2.end()) {
        return true;
      }
    }
  }
  return false;
}

std::string StmtStmtArgStrategy::getArg1() { return arg1; }

StmtRefType StmtStmtArgStrategy::getArgType1() { return argType1; }

std::string StmtStmtArgStrategy::getArg2() { return arg2; }

StmtRefType StmtStmtArgStrategy::getArgType2() { return argType2; }

bool StmtStmtArgStrategy::isBooleanStrategy() {
  return StmtRefTypeController::isBoolResult(argType1) &&
         StmtRefTypeController::isBoolResult(argType2);
}

std::unordered_set<std::string> StmtStmtArgStrategy::getSynonyms() {
  std::unordered_set<std::string> synonyms;
  if (!StmtRefTypeController::isBoolResult(argType1)) {
    synonyms.insert(arg1);
  }
  if (!StmtRefTypeController::isBoolResult(argType2)) {
    synonyms.insert(arg2);
  }
  return synonyms;
}

void StmtStmtArgStrategy::setArgFlags() {
  isArg1Integer = argType1 == StmtRefType::INTEGER;
  isArg2Integer = argType2 == StmtRefType::INTEGER;

  isArg1Stmt = argType1 == StmtRefType::STMT;
  isArg2Stmt = argType2 == StmtRefType::STMT;

  isArg1Assign = argType1 == StmtRefType::ASSIGN;
  isArg2Assign = argType2 == StmtRefType::ASSIGN;

  isArg1Wildcard = argType1 == StmtRefType::WILDCARD;
  isArg2Wildcard = argType2 == StmtRefType::WILDCARD;

  isBothArgSame = arg1 == arg2 && argType1 == argType2;

  isArg1Synonym = !isArg1Integer && !isArg1Wildcard;
  isArg2Synonym = !isArg2Integer && !isArg2Wildcard;
}

void StmtStmtArgStrategy::setEvaluationSets(ReadFacade &readFacade) {
  bool isAffects = strategyType == StrategyType::AFFECTS;

  if (isArg1Integer) {
    argSet1 = {std::stoi(arg1)};
  } else if (isAffects) {
    if (isArg1Stmt || isArg1Assign || isArg1Wildcard) {
      argSet1 =
          Strategy::getAllStmtBySynonymType(StmtRefType::ASSIGN, readFacade);
    }
  } else {
    argSet1 = Strategy::getAllStmtBySynonymType(argType1, readFacade);
  }

  if (isArg2Integer) {
    argSet2 = {std::stoi(arg2)};
  } else if (isAffects) {
    if (isArg2Stmt || isArg2Assign || isArg2Wildcard) {
      argSet2 =
          Strategy::getAllStmtBySynonymType(StmtRefType::ASSIGN, readFacade);
    }
  } else {
    argSet2 = Strategy::getAllStmtBySynonymType(argType2, readFacade);
  }
}

std::unordered_map<std::string, int> StmtStmtArgStrategy::generateHeaders()
    const {
  std::unordered_map<std::string, int> headers;
  if (isArg1Synonym) {
    headers[arg1] = static_cast<int>(headers.size());
  }
  if (isArg2Synonym && !isBothArgSame) {
    headers[arg2] = static_cast<int>(headers.size());
  }
  return headers;
}

std::vector<std::string> StmtStmtArgStrategy::generateDataRow(
    int assign1, int assign2) const {
  std::vector<std::string> row;
  if (isArg1Synonym) {
    row.push_back(std::to_string(assign1));
  }
  if (isArg2Synonym && !isBothArgSame) {
    row.push_back(std::to_string(assign2));
  }
  return row;
}

void StmtStmtArgStrategy::replaceSynFromWithClause(
    std::unordered_map<std::string, std::pair<std::string, bool>>
        &replaceableSynValues,
    std::unordered_map<std::string, SynonymType> &replaceableStmtSyn) {
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
    if (isReplaceValueInteger) {
      arg2 = replaceableSynValues.at(arg2).first;
      argType2 = StmtRefType::INTEGER;
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
    argType2 =
        StmtRefTypeController::getStmtRefType(replaceableStmtSyn.at(arg2));
  }
}
}  // namespace QPS
