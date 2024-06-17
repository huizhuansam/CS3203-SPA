#include "optimizer/GroupDivider.h"

namespace QPS {

std::unordered_map<std::string, std::vector<std::shared_ptr<Strategy>>>
    GroupDivider::synonymGraph;

std::vector<std::vector<std::shared_ptr<Strategy>>> GroupDivider::divide(
    std::vector<std::shared_ptr<Strategy>>& strategies,
    std::vector<std::vector<std::shared_ptr<Strategy>>>& groups) {
  buildSynonymGraph(strategies);
  std::unordered_set<std::shared_ptr<Strategy>> visited;

  for (const auto& strategy : strategies) {
    if (visited.find(strategy) != visited.end()) {
      continue;
    }

    std::vector<std::shared_ptr<Strategy>> group;
    std::queue<std::shared_ptr<Strategy>> queue;
    queue.push(strategy);

    while (!queue.empty()) {
      divideNextStrategy(visited, group, queue);
    }

    groups.push_back(group);
  }

  return groups;
}

void GroupDivider::divideNextStrategy(
    std::unordered_set<std::shared_ptr<Strategy>>& visited,
    std::vector<std::shared_ptr<Strategy>>& group,
    std::queue<std::shared_ptr<Strategy>>& queue) {
  std::shared_ptr<Strategy> current = queue.front();
  queue.pop();

  if (visited.find(current) != visited.end()) {
    return;
  }

  visited.insert(current);
  group.push_back(current);

  const std::unordered_set<std::string> synonyms = current->getSynonyms();
  for (const auto& synonym : synonyms) {
    if (synonymGraph.find(synonym) != synonymGraph.end()) {
      for (const auto& next : synonymGraph[synonym]) {
        queue.push(next);
      }
    }
  }
}

void GroupDivider::buildSynonymGraph(
    std::vector<std::shared_ptr<Strategy>>& strategies) {
  synonymGraph.clear();

  for (const auto& strategy : strategies) {
    const std::unordered_set<std::string> synonyms = strategy->getSynonyms();
    for (const auto& synonym : synonyms) {
      if (synonymGraph.find(synonym) == synonymGraph.end()) {
        synonymGraph[synonym] =
            std::vector<std::shared_ptr<Strategy>>{strategy};
      }
      synonymGraph[synonym].push_back(strategy);
    }
  }
}
}  // namespace QPS