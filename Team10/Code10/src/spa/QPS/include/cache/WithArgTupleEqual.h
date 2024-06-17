#pragma once

#include <string>
#include <tuple>

#include "../strategy/argument_types/RefType.h"

namespace QPS {
class WithArgTupleEqual {
 public:
  bool operator()(
      const std::tuple<RefType, std::string, RefType, std::string>& t1,
      const std::tuple<RefType, std::string, RefType, std::string>& t2) const;
};
}  // namespace QPS
