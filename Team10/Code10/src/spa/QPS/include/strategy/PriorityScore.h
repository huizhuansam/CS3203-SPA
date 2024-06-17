#pragma once

#include <unordered_map>

#include "strategy/strategy_types/StrategyType.h"

namespace QPS {
class PriorityScore {
 public:
  static const int PRIORITY_1;
  static const int PRIORITY_2;
  static const int PRIORITY_3;
  static const int PRIORITY_4;
  static const int PRIORITY_5;
  static const int PRIORITY_6;
  static const int PRIORITY_7;
  static const int PRIORITY_8;

  static int getPriorityScore(StrategyType strategyType);
};
}  // namespace QPS
