#pragma once

#include <string>
#include <tuple>

#include "../strategy/argument_types/RefType.h"

namespace QPS {
class WithArgTupleHasher {
 public:
  std::size_t operator()(
      const std::tuple<RefType, std::string, RefType, std::string>& key) const;
};
}  // namespace QPS
