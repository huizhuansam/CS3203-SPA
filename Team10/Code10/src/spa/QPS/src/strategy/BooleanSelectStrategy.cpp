#include "strategy/BooleanSelectStrategy.h"

namespace QPS {
bool BooleanSelectStrategy::isSelectBooleanStrategy() { return true; }

bool BooleanSelectStrategy::isBooleanStrategy() { return true; }

bool BooleanSelectStrategy::evaluateBoolean(
    [[maybe_unused]] ReadFacade& readFacade) {
  return true;
}
}  // namespace QPS
