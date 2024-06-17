#pragma once

#include <memory>
#include <vector>

#include "strategy/Strategy.h"

namespace QPS {
class GroupSorter {
 public:
  static void sort(std::unordered_set<std::string>& selectSynonyms,
                   std::vector<std::vector<std::shared_ptr<Strategy>>>& groups);

 private:
  static bool isMorePrioritized(
      std::unordered_set<std::string>& selectSynonyms,
      const std::vector<std::shared_ptr<Strategy>>& g1,
      const std::vector<std::shared_ptr<Strategy>>& g2);

  static std::unordered_set<std::string> getGroupSynonyms(
      const std::vector<std::shared_ptr<Strategy>>& group);

  static int countSelectSynonymInGroup(
      const std::unordered_set<std::string>& selectSynonyms,
      const std::unordered_set<std::string>& group);
};
}  // namespace QPS