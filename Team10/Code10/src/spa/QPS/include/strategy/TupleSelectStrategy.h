#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "strategy/Strategy.h"
#include "strategy/argument_types/AttrNameType.h"
#include "strategy/argument_types/SynonymType.h"

namespace QPS {
class TupleSelectStrategy : public Strategy {
 private:
  std::vector<std::string> synonyms;
  std::vector<SynonymType> synonymTypes;
  std::vector<AttrNameType> attrNameTypes;

 public:
  /// Strategy constructor for Select tuple clause.
  explicit TupleSelectStrategy(std::vector<std::string> synonyms,
                               std::vector<SynonymType> synonymTypes,
                               std::vector<AttrNameType> attrNameTypes);
  bool isSelectTupleStrategy() override;

  Result evaluateValues(ReadFacade& readFacade) override;

  std::vector<std::string> getTargets();
  std::vector<std::string> getTupleSynonyms();
  std::vector<SynonymType> getSynonymTypes();
  std::vector<AttrNameType> getAttrNameTypes();

 private:
  static void getTupleResult(const std::vector<Result>& results,
                             Result& current);
};
}  // namespace QPS
