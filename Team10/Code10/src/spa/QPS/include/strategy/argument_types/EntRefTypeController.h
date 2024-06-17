#pragma once

#include <unordered_map>
#include <unordered_set>

#include "strategy/argument_types/EntRefType.h"
#include "strategy/argument_types/SynonymType.h"

namespace QPS {
class EntRefTypeController {
 private:
  static const std::unordered_set<EntRefType> boolStrategyTypes;

  static const std::unordered_set<EntRefType> synonymTypes;

  static const std::unordered_map<SynonymType, EntRefType>
      synonymTypeToEntRefType;

 public:
  static bool isBoolResult(EntRefType entRefType);

  static bool isSynonymType(EntRefType entRefType);

  static EntRefType getEntRefType(SynonymType synonymType);
};
}  // namespace QPS
