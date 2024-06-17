#pragma once

#include "optimizer/GroupDivider.h"
#include "optimizer/GroupSorter.h"
#include "optimizer/StrategySorter.h"
#include "optimizer/WithOptimizer.h"

namespace QPS {
class Optimizer {
 private:
  static std::shared_ptr<Strategy> selectStrategy;
  static std::vector<std::shared_ptr<Strategy>> constraintStrategies;
  static std::vector<std::vector<std::shared_ptr<Strategy>>> groups;

 public:
  static std::shared_ptr<Strategy> getSelectStrategy();
  static std::vector<std::vector<std::shared_ptr<Strategy>>> getGroups();
  static void optimize(std::vector<std::shared_ptr<Strategy>>& strategies);

 private:
  static void splitConstraintsFromSelect(
      std::vector<std::shared_ptr<Strategy>>& strategies);
  static void sortStrategiesInAllGroups();
  static void reset();
};
}  // namespace QPS