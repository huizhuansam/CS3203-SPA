#pragma once

#include <unordered_map>
#include <unordered_set>

#include "strategy/argument_types/StmtRefType.h"
#include "strategy/argument_types/SynonymType.h"

namespace QPS {
class StmtRefTypeController {
 private:
  static const std::unordered_set<StmtRefType> boolStrategyTypes;

  static const std::unordered_map<SynonymType, StmtRefType>
      synonymTypeToStmtRefType;

 public:
  static bool isBoolResult(StmtRefType stmtRefType);

  static StmtRefType getStmtRefType(SynonymType synonymType);
};
}  // namespace QPS
