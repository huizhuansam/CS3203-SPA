#include "strategy/TupleSelectStrategy.h"

namespace QPS {
TupleSelectStrategy::TupleSelectStrategy(
    std::vector<std::string> synonyms, std::vector<SynonymType> synonymTypes,
    std::vector<AttrNameType> attrNameTypes) {
  this->synonyms = std::move(synonyms);
  this->synonymTypes = std::move(synonymTypes);
  this->attrNameTypes = std::move(attrNameTypes);
}

bool TupleSelectStrategy::isSelectTupleStrategy() { return true; }

Result TupleSelectStrategy::evaluateValues(ReadFacade& readFacade) {
  std::vector<Result> results;
  std::unordered_set<std::string> seenSynonyms;

  // assume synonyms and synonymTypes are of the same size
  for (size_t i = 0; i < synonyms.size(); i++) {
    std::string synonym = synonyms[i];

    // not repeating the same synonym again
    // even if it has different attribute name
    if (seenSynonyms.find(synonym) != seenSynonyms.end()) {
      continue;
    } else {
      seenSynonyms.insert(synonym);
    }

    SynonymType synonymType = synonymTypes[i];
    std::string headerName = synonyms[i];

    // form headers for current synonym
    std::vector<std::string> allHeaderNames =
        getAllHeaderNames(synonym, synonymType);
    std::unordered_map<std::string, int> headers;
    for (size_t j = 0; j < allHeaderNames.size(); j++) {
      headers[allHeaderNames[j]] = static_cast<int>(j);
    }

    // form data
    std::vector<std::vector<std::string>> data =
        synonymAttrNameEvaluationMap.at(synonymType)(readFacade);
    if (data.empty() || data[0].empty()) {
      return {headers, {}};
    }

    results.emplace_back(headers, data);
  }

  // merge each "column" (which is a single header result)
  // to form the tuple result
  Result tupleResult = Result();
  getTupleResult(results, tupleResult);
  return tupleResult;
}

void TupleSelectStrategy::getTupleResult(const std::vector<Result>& results,
                                         Result& current) {
  bool first = true;
  for (Result result : results) {
    if (first) {
      current = result;
      first = false;
      continue;
    }
    Result merged = Result();
    Result::merge(current, result, merged);
    current = merged;
  }
}

std::vector<std::string> TupleSelectStrategy::getTupleSynonyms() {
  return synonyms;
}

std::vector<SynonymType> TupleSelectStrategy::getSynonymTypes() {
  return synonymTypes;
}

std::vector<AttrNameType> TupleSelectStrategy::getAttrNameTypes() {
  return attrNameTypes;
}

std::vector<std::string> TupleSelectStrategy::getTargets() {
  std::vector<std::string> targets;
  for (size_t i = 0; i < synonyms.size(); i++) {
    // form target attribute name for current synonym
    SynonymType synonymType = synonymTypes[i];
    AttrNameType attrNameType = attrNameTypes[i];
    std::string attributeName;
    // do not add attribute name if it is none, or integer
    if (attrNameType != AttrNameType::NONE &&
        attrNameType != AttrNameType::INTEGER) {
      bool isCall = synonymType == SynonymType::CALL;
      bool isReadOrPrint =
          synonymType == SynonymType::READ || synonymType == SynonymType::PRINT;
      attributeName = isCall ? ".procName" : isReadOrPrint ? ".varName" : "";
    }

    // if attrNameType not none, target: synonym.attribute name
    // else, target: synonym
    std::string synonym = synonyms[i];
    std::string targetName = synonym + attributeName;

    targets.push_back(targetName);
  }
  return targets;
}
}  // namespace QPS
