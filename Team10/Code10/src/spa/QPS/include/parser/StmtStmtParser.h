#pragma once

#include "../parser/ParserUtil.h"
#include "strategy/strategy_types/StmtStmtArgStrategy.h"

namespace QPS {
class StmtStmtParser {
 public:
  static std::shared_ptr<StmtStmtArgStrategy> parse(
      StrategyType strategyType,
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::unordered_map<std::string, SynonymType>& declarationsMap);
};
}  // namespace QPS
