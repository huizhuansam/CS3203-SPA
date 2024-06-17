#pragma once

#include <tuple>
#include <variant>

#include "../strategy/argument_types/EntRefType.h"
#include "../strategy/argument_types/ExprSpecType.h"
#include "../strategy/argument_types/RefType.h"
#include "../strategy/argument_types/StmtRefType.h"
#include "../strategy/strategy_types/StrategyType.h"

namespace QPS {
class SuchThatArgTupleHasher {
 public:
  size_t operator()(
      const std::tuple<StrategyType, std::variant<StmtRefType, EntRefType>,
                       std::variant<StmtRefType, EntRefType>>& key) const;
};
}  // namespace QPS
