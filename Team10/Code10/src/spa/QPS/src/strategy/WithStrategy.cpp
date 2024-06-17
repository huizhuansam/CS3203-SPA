#include "strategy/WithStrategy.h"

namespace QPS {

WithStrategy::WithStrategy(std::string arg1, RefType argType1, std::string arg2,
                           RefType argType2)
    : arg1(std::move(arg1)),
      argType1(argType1),
      arg2(std::move(arg2)),
      argType2(argType2) {
  setPriorityScore(PriorityScore::PRIORITY_6);
}

Result WithStrategy::evaluateValues(ReadFacade& readFacade) {
  auto key = std::make_tuple(argType1, arg1, argType2, arg2);

  if (cache->isCached(key)) {
    return cache->get(key);
  }

  Result LHS = getResultOfOneSide(true, readFacade);
  // both sides contain same synonym
  if (arg1 == arg2) {
    return LHS;
  }

  Result RHS = getResultOfOneSide(false, readFacade);
  Result result;

  // either side contains non-synonym
  if (RefTypeController::isBoolResult(argType1) ||
      RefTypeController::isBoolResult(argType2)) {
    Result::merge(LHS, RHS, result);
    return result;
  }

  // both sides contain different synonym
  std::string leftMatchHeader = getHeaderWithAttrName(arg1, argType1);
  std::string rightMatchHeader = getHeaderWithAttrName(arg2, argType2);
  Result::innerJoinByHeaders(LHS, RHS, leftMatchHeader, rightMatchHeader,
                             result);

  return cache->storeAndReturn(key, result);
}

std::string WithStrategy::getHeaderWithAttrName(const std::string& synonym,
                                                const RefType refType) {
  std::string header = synonym;

  SynonymType synonymType = RefTypeController::getSynonymType(refType);
  AttrNameType attrNameType = RefTypeController::getAttrNameType(refType);

  // all integer, procedure's, and variable's attribute names can be ignored
  // since the synonym itself represents those attributes
  // e.g. read.stmt# == read, variable.varName == variable
  if (attrNameType == AttrNameType::NAME &&
      synonymType != SynonymType::PROCEDURE &&
      synonymType != SynonymType::VARIABLE) {
    bool isCallSyn = synonymType == SynonymType::CALL;
    header += isCallSyn ? ".procName" : ".varName";
  }
  return header;
}

Result WithStrategy::getResultOfOneSide(bool isLHS, ReadFacade& readFacade) {
  std::string arg = isLHS ? arg1 : arg2;
  bool isNotSyn = isLHS ? RefTypeController::isBoolResult(argType1)
                        : RefTypeController::isBoolResult(argType2);

  std::unordered_map<std::string, int> headers;
  std::vector<std::vector<std::string>> data;

  if (isNotSyn) {
    // e.g. with v.varName = "x"
    // it will create a header "v.varName" on RHS,
    // so it can be merged later with LHS
    std::string anotherArg = isLHS ? arg2 : arg1;
    RefType anotherArgType = isLHS ? argType2 : argType1;
    std::string matchHeaderWithAnotherSide =
        getHeaderWithAttrName(anotherArg, anotherArgType);

    headers = {{matchHeaderWithAnotherSide, 0}};
    data = {{arg}};
  } else {
    SynonymType synonymType =
        RefTypeController::getSynonymType(isLHS ? argType1 : argType2);

    // get header
    auto headerNames = Strategy::getAllHeaderNames(arg, synonymType);
    for (const auto& name : headerNames) {
      headers[name] = static_cast<int>(headers.size());
    }

    // get data
    EvaluateFunctionType evaluateFunction =
        Strategy::synonymAttrNameEvaluationMap.at(synonymType);
    data = evaluateFunction(readFacade);
  }

  return {headers, data};
}

bool WithStrategy::isBooleanStrategy() {
  return RefTypeController::isBoolResult(argType1) &&
         RefTypeController::isBoolResult(argType2);
}

bool WithStrategy::isWithStrategy() { return true; }

bool WithStrategy::evaluateBoolean([[maybe_unused]] ReadFacade& readFacade) {
  return arg1 == arg2;
}

std::string WithStrategy::getArg1() { return arg1; }
RefType WithStrategy::getArgType1() { return argType1; }

std::string WithStrategy::getArg2() { return arg2; }
RefType WithStrategy::getArgType2() { return argType2; }

std::unordered_set<std::string> WithStrategy::getSynonyms() {
  std::unordered_set<std::string> synonyms;
  if (!RefTypeController::isBoolResult(argType1)) {
    synonyms.insert(arg1);
  }
  if (!RefTypeController::isBoolResult(argType2)) {
    synonyms.insert(arg2);
  }
  return synonyms;
}

std::tuple<std::string, std::string, bool>
WithStrategy::getReplaceableSynValues() {
  bool isArg1Bool = RefTypeController::isBoolResult(argType1);
  bool isArg2Bool = RefTypeController::isBoolResult(argType2);
  bool isSynValuePair =
      (isArg1Bool && !isArg2Bool) || (!isArg1Bool && isArg2Bool);

  if (!isSynValuePair) {
    // not a synonym-value pair,
    // then return empty pair (not replaceable)
    return {};
  }

  return isArg1Bool ? std::make_tuple(arg2, arg1, argType1 == RefType::INTEGER)
                    : std::make_tuple(arg1, arg2, argType2 == RefType::INTEGER);
}

std::pair<std::string, SynonymType> WithStrategy::getReplaceableStmtSyn() {
  bool isStmtStrictLoosePair = (RefTypeController::isStrictStmtType(argType1) &&
                                argType2 == RefType::STMT_STMTNO) ||
                               (RefTypeController::isStrictStmtType(argType2) &&
                                argType1 == RefType::STMT_STMTNO);

  if (!isStmtStrictLoosePair) {
    // not a stmt-synonym pair,
    // then not replaceable
    return {"", SynonymType::INVALID};
  }

  return argType1 == RefType::STMT_STMTNO
             ? std::make_pair(arg1, RefTypeController::getSynonymType(argType2))
             : std::make_pair(arg2,
                              RefTypeController::getSynonymType(argType1));
}
}  // namespace QPS
