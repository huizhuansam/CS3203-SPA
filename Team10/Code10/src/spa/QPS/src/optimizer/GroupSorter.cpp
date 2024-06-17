#include "optimizer/GroupSorter.h"

namespace QPS {
void GroupSorter::sort(
    std::unordered_set<std::string>& selectSynonyms,
    std::vector<std::vector<std::shared_ptr<Strategy>>>& groups) {
  std::sort(
      groups.begin(), groups.end(),
      [&selectSynonyms](const std::vector<std::shared_ptr<Strategy>>& g1,
                        const std::vector<std::shared_ptr<Strategy>>& g2) {
        return isMorePrioritized(selectSynonyms, g1, g2);
      });
}

bool GroupSorter::isMorePrioritized(
    std::unordered_set<std::string>& selectSynonyms,
    const std::vector<std::shared_ptr<Strategy>>& g1,
    const std::vector<std::shared_ptr<Strategy>>& g2) {
  std::unordered_set<std::string> g1Synonyms = getGroupSynonyms(g1);
  std::unordered_set<std::string> g2Synonyms = getGroupSynonyms(g2);

  // Start with group without synonym, then
  if (g1Synonyms.empty() && !g2Synonyms.empty()) {
    return true;
  } else if (!g1Synonyms.empty() && g2Synonyms.empty()) {
    return false;
  }

  // prioritize groups that do not return results in Select
  int g1SelectSynonymCount =
      countSelectSynonymInGroup(selectSynonyms, g1Synonyms);
  int g2SelectSynonymCount =
      countSelectSynonymInGroup(selectSynonyms, g2Synonyms);

  return g1SelectSynonymCount < g2SelectSynonymCount;
}

std::unordered_set<std::string> GroupSorter::getGroupSynonyms(
    const std::vector<std::shared_ptr<Strategy>>& group) {
  std::unordered_set<std::string> synonyms;
  for (const auto& strategy : group) {
    for (const auto& synonym : strategy->getSynonyms()) {
      synonyms.insert(synonym);
    }
  }
  return synonyms;
}

int GroupSorter::countSelectSynonymInGroup(
    const std::unordered_set<std::string>& selectSynonyms,
    const std::unordered_set<std::string>& group) {
  int count = 0;
  for (const auto& synonym : group) {
    if (selectSynonyms.find(synonym) != selectSynonyms.end()) {
      count++;
    }
  }
  return count;
}
}  // namespace QPS