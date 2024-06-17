#pragma once

#include <memory>

#include "../strategy/Strategy.h"

namespace QPS {
class WithOptimizer {
 public:
  static void optimizeWith(std::vector<std::shared_ptr<Strategy>>& strategies);

 private:
  static std::unordered_map<std::string, std::pair<std::string, bool>>
  getReplaceableSynValues(std::vector<std::shared_ptr<Strategy>>& strategies);

  static std::unordered_map<std::string, SynonymType> getReplaceableStmtSyn(
      std::vector<std::shared_ptr<Strategy>>& strategies);
};
}  // namespace QPS