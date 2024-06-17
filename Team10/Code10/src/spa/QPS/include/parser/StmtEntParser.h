#pragma once

#include "../parser/ParserUtil.h"
#include "strategy/strategy_types/StmtEntArgStrategy.h"
#include "strategy/strategy_types/StrategyType.h"

namespace QPS {
class StmtEntParser {
 public:
  static std::shared_ptr<StmtEntArgStrategy> parse(
      StrategyType strategyType,
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::unordered_map<std::string, SynonymType>& declarationsMap);
};
}  // namespace QPS
