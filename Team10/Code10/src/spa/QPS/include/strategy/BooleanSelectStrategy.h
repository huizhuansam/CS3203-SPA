#pragma once

#include <string>

#include "strategy/Strategy.h"

namespace QPS {
class BooleanSelectStrategy : public Strategy {
 public:
  bool isSelectBooleanStrategy() override;
  bool isBooleanStrategy() override;
  bool evaluateBoolean(ReadFacade& readFacade) override;
};
}  // namespace QPS
