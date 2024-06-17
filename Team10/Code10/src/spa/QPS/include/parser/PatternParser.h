#pragma once

#include "../parser/ParserUtil.h"
#include "strategy/strategy_types/PatternStrategy.h"
#include "strategy/strategy_types/StrategyType.h"

namespace QPS {
class PatternParser {
 public:
  static std::shared_ptr<PatternStrategy> parse(
      StrategyType strategyType,
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::unordered_map<std::string, SynonymType>& declarationsMap);
};
}  // namespace QPS
