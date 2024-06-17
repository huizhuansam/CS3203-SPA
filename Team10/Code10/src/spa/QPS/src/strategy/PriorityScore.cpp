#include "strategy/PriorityScore.h"

namespace QPS {
const int PriorityScore::PRIORITY_1 = 10;
const int PriorityScore::PRIORITY_2 = 20;
const int PriorityScore::PRIORITY_3 = 30;
const int PriorityScore::PRIORITY_4 = 40;
const int PriorityScore::PRIORITY_5 = 50;
const int PriorityScore::PRIORITY_6 = 60;
const int PriorityScore::PRIORITY_7 = 70;
const int PriorityScore::PRIORITY_8 = 80;

int PriorityScore::getPriorityScore(StrategyType strategyType) {
  std::unordered_map<StrategyType, int> strategyToPriorityScoreMap = {
      {StrategyType::FOLLOWS, PriorityScore::PRIORITY_1},
      {StrategyType::FOLLOWS_T, PriorityScore::PRIORITY_2},
      {StrategyType::PARENT, PriorityScore::PRIORITY_1},
      {StrategyType::PARENT_T, PriorityScore::PRIORITY_2},
      {StrategyType::USES_S, PriorityScore::PRIORITY_1},
      {StrategyType::USES_P, PriorityScore::PRIORITY_1},
      {StrategyType::MODIFIES_S, PriorityScore::PRIORITY_1},
      {StrategyType::MODIFIES_P, PriorityScore::PRIORITY_1},
      {StrategyType::CALLS, PriorityScore::PRIORITY_1},
      {StrategyType::CALLS_T, PriorityScore::PRIORITY_2},
      {StrategyType::NEXT, PriorityScore::PRIORITY_3},
      {StrategyType::NEXT_T, PriorityScore::PRIORITY_4},
      {StrategyType::AFFECTS, PriorityScore::PRIORITY_5},
      {StrategyType::WHILE_PATTERN, PriorityScore::PRIORITY_7},
      {StrategyType::IF_PATTERN, PriorityScore::PRIORITY_7},
      {StrategyType::ASSIGN_PATTERN, PriorityScore::PRIORITY_8},
  };
  return strategyToPriorityScoreMap.at(strategyType);
}
}  // namespace QPS
