#pragma once

#include <queue>
#include <unordered_map>
#include <vector>

#include "strategy/Strategy.h"

namespace QPS {
class GroupDivider {
 private:
  static std::unordered_map<std::string, std::vector<std::shared_ptr<Strategy>>>
      synonymGraph;

 public:
  static std::vector<std::vector<std::shared_ptr<Strategy>>> divide(
      std::vector<std::shared_ptr<Strategy>>& strategies,
      std::vector<std::vector<std::shared_ptr<Strategy>>>& groups);
  static void divideNextStrategy(
      std::unordered_set<std::shared_ptr<Strategy>>& visited,
      std::vector<std::shared_ptr<Strategy>>& group,
      std::queue<std::shared_ptr<Strategy>>& queue);

 private:
  static void buildSynonymGraph(
      std::vector<std::shared_ptr<Strategy>>& strategies);
};
}  // namespace QPS