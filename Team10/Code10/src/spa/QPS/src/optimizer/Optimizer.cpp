#include "optimizer/Optimizer.h"

namespace QPS {
std::shared_ptr<Strategy> Optimizer::selectStrategy = nullptr;
std::vector<std::shared_ptr<Strategy>> Optimizer::constraintStrategies;
std::vector<std::vector<std::shared_ptr<Strategy>>> Optimizer::groups;

std::shared_ptr<Strategy> Optimizer::getSelectStrategy() {
  return selectStrategy;
}

std::vector<std::vector<std::shared_ptr<Strategy>>> Optimizer::getGroups() {
  return groups;
}

void Optimizer::optimize(std::vector<std::shared_ptr<Strategy>>& strategies) {
  // Reset storage fields
  reset();

  // replace synonym with values or stricter stmt type if applicable
  WithOptimizer::optimizeWith(strategies);

  // Split select strategy from constraint strategies
  splitConstraintsFromSelect(strategies);

  // Split constraint strategies into groups
  GroupDivider::divide(constraintStrategies, groups);

  // Sort constraint group order
  std::unordered_set<std::string> selectSynonyms =
      selectStrategy->getSynonyms();
  GroupSorter::sort(selectSynonyms, groups);

  // Sort strategies inside each group
  sortStrategiesInAllGroups();
}

void Optimizer::splitConstraintsFromSelect(
    std::vector<std::shared_ptr<Strategy>>& strategies) {
  for (auto& strategy : strategies) {
    if (!strategy->isSelectStrategy()) {
      constraintStrategies.push_back(strategy);
    } else {
      selectStrategy = strategy;
    }
  }
}

void Optimizer::sortStrategiesInAllGroups() {
  for (auto& group : groups) {
    StrategySorter::sort(group);
  }
}

void Optimizer::reset() {
  selectStrategy = nullptr;
  constraintStrategies.clear();
  groups.clear();
}
}  // namespace QPS