#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "strategy/Strategy.h"

namespace QPS {
class StrategySorter {
 private:
  static std::unordered_map<std::shared_ptr<Strategy>,
                            std::vector<std::shared_ptr<Strategy>>>
      connectionGraph;

 public:
  static void sort(std::vector<std::shared_ptr<Strategy>>& group);

 private:
  static void buildConnectionGraph(
      const std::vector<std::shared_ptr<Strategy>>& group);

  static std::shared_ptr<Strategy> getFirstStrategy(
      const std::vector<std::shared_ptr<Strategy>>& group);

  static bool isEasyToEvaluate(const std::shared_ptr<Strategy>& strategy1,
                               const std::shared_ptr<Strategy>& strategy2);

  static std::unordered_set<std::string> getIntersection(
      const std::shared_ptr<Strategy>& strategy1,
      const std::shared_ptr<Strategy>& strategy2);

  static std::priority_queue<
      std::shared_ptr<Strategy>, std::vector<std::shared_ptr<Strategy>>,
      std::function<bool(const std::shared_ptr<Strategy>& strategy1,
                         const std::shared_ptr<Strategy>& strategy2)>>
  initializePriorityQueue(std::shared_ptr<Strategy>& firstStrategy);

  static std::vector<std::shared_ptr<Strategy>> getSortStrategies(
      std::shared_ptr<Strategy>& firstStrategy);
};
}  // namespace QPS