#include "evaluator/Evaluator.h"

namespace QPS {
const std::list<std::string> Evaluator::TRUE_LIST = {"TRUE"};
const std::list<std::string> Evaluator::FALSE_LIST = {"FALSE"};
const std::list<std::string> Evaluator::EMPTY_LIST = {};

std::list<std::string> Evaluator::getResultList(
    ReadFacade& readFacade, const std::shared_ptr<Strategy>& selectStrategy,
    const std::vector<std::vector<std::shared_ptr<Strategy>>>& groups) {
  bool isBoolean = selectStrategy->isSelectBooleanStrategy();
  if (isBoolean) {
    return evaluateBoolean(readFacade, groups);
  }
  return evaluateValues(readFacade, selectStrategy, groups);
}

std::list<std::string> Evaluator::evaluateBoolean(
    ReadFacade& readFacade,
    const std::vector<std::vector<std::shared_ptr<Strategy>>>& groups) {
  bool hasNoConstraint = groups.empty();

  if (hasNoConstraint) {
    return TRUE_LIST;
  }

  std::vector<Result> groupResults = evaluateEachGroup(readFacade, groups);
  bool hasFalseOrEmptyGroup = groupResults.empty();
  if (hasFalseOrEmptyGroup) {
    return FALSE_LIST;
  }

  return TRUE_LIST;
}

std::list<std::string> Evaluator::evaluateValues(
    ReadFacade& readFacade, const std::shared_ptr<Strategy>& selectStrategy,
    const std::vector<std::vector<std::shared_ptr<Strategy>>>& groups) {
  bool hasNoConstraint = groups.empty();
  std::vector<Result> groupResults = evaluateEachGroup(readFacade, groups);
  bool hasFalseOrEmptyGroup = !hasNoConstraint && groupResults.empty();
  if (hasFalseOrEmptyGroup) {
    return EMPTY_LIST;
  }

  std::vector<std::string> selectSynonyms = getSelectSynonyms(selectStrategy);
  std::vector<Result> filteredGroupResults =
      filterGroupResultsByTargetSynonyms(groupResults, selectSynonyms);
  Result constraintResult = mergeResults(filteredGroupResults);

  std::vector<std::string> selectTargets = getSelectTargets(selectStrategy);
  std::vector<SynonymType> selectSynonymTypes = getSynonymTypes(selectStrategy);
  std::vector<AttrNameType> selectAttrNameTypes =
      getAttrNameTypes(selectStrategy);

  Result finalResult = selectResultWithConstraint(
      selectTargets, selectSynonyms, selectSynonymTypes, selectAttrNameTypes,
      constraintResult, readFacade);

  return finalResult.getFlattenListByHeaderNames(selectTargets);
}

std::vector<Result> Evaluator::evaluateEachGroup(
    ReadFacade& readFacade,
    const std::vector<std::vector<std::shared_ptr<Strategy>>>& groups) {
  auto cache = std::make_shared<Cache>();
  std::vector<Result> groupResults;
  for (const auto& group : groups) {
    Result groupResult;
    bool isFirstStrategy = true;
    for (const auto& strategy : group) {
      strategy->injectCache(cache);
      // evaluate the strategy, and check if it is a boolean or non-boolean
      if (strategy->isBooleanStrategy()) {
        // process boolean result
        bool isTrue = strategy->evaluateBoolean(readFacade);
        bool isNot = strategy->isNotStrategy();
        isTrue = isNot == !isTrue;
        if (!isTrue) {
          groupResults.clear();
          return groupResults;
        }
      } else {
        // process non-boolean result
        if (isFirstStrategy) {
          groupResult = evaluateValueStrategy(readFacade, strategy,
                                              isFirstStrategy, groupResult);
          isFirstStrategy = false;
        } else {
          groupResult = evaluateValueStrategy(readFacade, strategy,
                                              isFirstStrategy, groupResult);
        }
        if (groupResult.isDataEmpty()) {
          groupResults.clear();
          return groupResults;
        }
      }
    }
    groupResults.push_back(groupResult);
  }
  return groupResults;
}

Result Evaluator::evaluateValueStrategy(
    ReadFacade& readFacade, const std::shared_ptr<Strategy>& strategy,
    bool isFirst, Result groupResult) {
  Result result;
  if (strategy->isNotStrategy()) {
    result = evaluateNotValueStrategy(readFacade, strategy);
  } else {
    result = strategy->evaluateValues(readFacade);
  }
  if (isFirst || result.isDataEmpty()) {
    return result;
  }
  Result newResult;
  Result::merge(groupResult, result, newResult);
  return newResult;
}

Result Evaluator::evaluateNotValueStrategy(
    ReadFacade& readFacade, const std::shared_ptr<Strategy>& strategy) {
  Result filterResult = strategy->evaluateValues(readFacade);
  std::vector<std::string> headerNames =
      filterResult.getHeaderNamesWithoutAttrNames();
  std::vector<SynonymType> headerTypes =
      Result::getHeaderSynonymTypes(headerNames);
  TupleSelectStrategy headerSelectStrategy =
      TupleSelectStrategy(headerNames, headerTypes, {});
  Result headerSelectResult = headerSelectStrategy.evaluateValues(readFacade);
  if (filterResult.isDataEmpty()) {
    return headerSelectResult;
  } else {
    Result filteredResult;
    Result::subtract(headerSelectResult, filterResult, filteredResult);
    return filteredResult;
  }
}

std::vector<std::string> Evaluator::getSelectTargets(
    const std::shared_ptr<Strategy>& selectStrategy) {
  return std::dynamic_pointer_cast<TupleSelectStrategy>(selectStrategy)
      ->getTargets();
}

std::vector<Result> Evaluator::filterGroupResultsByTargetSynonyms(
    std::vector<Result>& groupResults,
    std::vector<std::string>& targetSynonyms) {
  std::vector<Result> filteredGroupResults;
  for (auto& groupResult : groupResults) {
    Result filteredGroupResult;
    filterGroupResultByTargetSynonyms(groupResult, targetSynonyms,
                                      filteredGroupResult);

    // if no headers are in selectTargets, skip this group
    if (filteredGroupResult.getHeaders().empty()) {
      continue;
    }

    // add data that are in select synonyms
    std::vector<std::string> filteredHeaders =
        filteredGroupResult.getSortedHeaderNames();
    std::vector<std::vector<std::string>> filteredData;
    groupResult.getDataByHeaderNames(filteredHeaders, filteredData);
    filteredGroupResult.setData(filteredData);

    filteredGroupResults.push_back(filteredGroupResult);
  }

  return filteredGroupResults;
}

void Evaluator::filterGroupResultByTargetSynonyms(
    Result& groupResult, std::vector<std::string>& targetSynonyms,
    Result& filteredGroupResult) {
  auto headers = groupResult.getHeaders();
  // add headers that are in selectTargets
  for (auto& synonym : targetSynonyms) {
    for (auto& header : headers) {
      // if header has attrName, compare synonym with substring before "."
      bool headerHasAttrName = header.first.find(".") != std::string::npos;
      if (headerHasAttrName) {
        std::string headerNames = header.first;
        std::string headerSynonym =
            headerNames.substr(0, headerNames.find('.'));
        bool isSameSynonym = headerSynonym == synonym;
        if (isSameSynonym) {
          int index = static_cast<int>(filteredGroupResult.getHeaders().size());
          filteredGroupResult.addHeader(headerNames, index);
        }
      } else if (header.first == synonym) {
        int index = static_cast<int>(filteredGroupResult.getHeaders().size());
        filteredGroupResult.addHeader(synonym, index);
      }
    }
  }
}

Result Evaluator::mergeResults(std::vector<Result>& filteredGroupResults) {
  Result mergedResult;
  bool isFirstResult = true;
  for (auto& filteredGroupResult : filteredGroupResults) {
    if (isFirstResult) {
      mergedResult = filteredGroupResult;
      isFirstResult = false;
    } else {
      Result newResult;
      Result::merge(mergedResult, filteredGroupResult, newResult);
      mergedResult = newResult;
    }
  }
  return mergedResult;
}

std::vector<std::string> Evaluator::getSelectSynonyms(
    const std::shared_ptr<Strategy>& selectStrategy) {
  return std::dynamic_pointer_cast<TupleSelectStrategy>(selectStrategy)
      ->getTupleSynonyms();
}

std::vector<SynonymType> Evaluator::getSynonymTypes(
    const std::shared_ptr<Strategy>& selectStrategy) {
  return std::dynamic_pointer_cast<TupleSelectStrategy>(selectStrategy)
      ->getSynonymTypes();
}

std::vector<AttrNameType> Evaluator::getAttrNameTypes(
    const std::shared_ptr<Strategy>& selectStrategy) {
  return std::dynamic_pointer_cast<TupleSelectStrategy>(selectStrategy)
      ->getAttrNameTypes();
}

Result Evaluator::selectResultWithConstraint(
    const std::vector<std::string>& selectTargets,
    const std::vector<std::string>& selectSynonyms,
    const std::vector<SynonymType>& selectSynonymTypes,
    const std::vector<AttrNameType>& selectAttrNameTypes,
    Result& constraintResult, ReadFacade& readFacade) {
  std::unordered_map<std::string, int> constraintHeaders =
      constraintResult.getHeaders();

  std::vector<std::string> missingSynonyms;
  std::vector<SynonymType> missingSynonymTypes;
  std::vector<AttrNameType> missingAttrNames;

  missingSynonyms.reserve(selectSynonyms.size());
  missingSynonymTypes.reserve(selectSynonyms.size());
  missingAttrNames.reserve(selectSynonyms.size());

  for (size_t i = 0; i < selectSynonyms.size(); i++) {
    bool hasAttrName = selectAttrNameTypes[i] != AttrNameType::NONE;

    const std::string& key = hasAttrName ? selectTargets[i] : selectSynonyms[i];

    if (constraintHeaders.find(key) == constraintHeaders.end()) {
      missingSynonyms.push_back(selectSynonyms[i]);
      missingSynonymTypes.push_back(selectSynonymTypes[i]);
      missingAttrNames.push_back(selectAttrNameTypes[i]);
    }
  }

  if (missingSynonyms.empty()) {
    return constraintResult;
  }

  // create a select tuple strategy based on the missing targets
  auto selectTupleStrategy = std::make_unique<TupleSelectStrategy>(
      missingSynonyms, missingSynonymTypes, missingAttrNames);
  Result missingSelectResult = selectTupleStrategy->evaluateValues(readFacade);

  // the constraint group is empty, return the entire missing select result
  if (constraintResult.isDataEmpty()) {
    return missingSelectResult;
  }

  Result finalResult;
  Result::merge(missingSelectResult, constraintResult, finalResult);
  return finalResult;
}
}  // namespace QPS
