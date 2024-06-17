#include "optimizer/StrategySorter.h"

namespace QPS {
std::unordered_map<std::shared_ptr<Strategy>,
                   std::vector<std::shared_ptr<Strategy>>>
    StrategySorter::connectionGraph;

void StrategySorter::sort(std::vector<std::shared_ptr<Strategy>>& group) {
  if (group.size() <= 1) {
    return;
  }

  buildConnectionGraph(group);
  auto firstStrategy = getFirstStrategy(group);
  auto sortedStrategies = getSortStrategies(firstStrategy);

  group = sortedStrategies;
}

std::unordered_set<std::string> StrategySorter::getIntersection(
    const std::shared_ptr<Strategy>& strategy1,
    const std::shared_ptr<Strategy>& strategy2) {
  auto strategy1Synonyms = strategy1->getSynonyms();
  auto strategy2Synonyms = strategy2->getSynonyms();

  // convert unordered set to vector
  std::vector<std::string> strategy1SynonymsVector;
  strategy1SynonymsVector.reserve(strategy1Synonyms.size());
  for (const auto& synonym : strategy1Synonyms) {
    strategy1SynonymsVector.push_back(synonym);
  }
  std::sort(strategy1SynonymsVector.begin(), strategy1SynonymsVector.end());

  std::vector<std::string> strategy2SynonymsVector;
  strategy2SynonymsVector.reserve(strategy2Synonyms.size());
  for (const auto& synonym : strategy2Synonyms) {
    strategy2SynonymsVector.push_back(synonym);
  }
  std::sort(strategy2SynonymsVector.begin(), strategy2SynonymsVector.end());

  std::unordered_set<std::string> intersection;
  std::set_intersection(
      strategy1SynonymsVector.begin(), strategy1SynonymsVector.end(),
      strategy2SynonymsVector.begin(), strategy2SynonymsVector.end(),
      std::inserter(intersection, intersection.begin()));

  return intersection;
}

void StrategySorter::buildConnectionGraph(
    const std::vector<std::shared_ptr<Strategy>>& group) {
  connectionGraph.clear();

  for (size_t i = 0; i < group.size(); i++) {
    for (size_t j = i + 1; j < group.size(); j++) {
      const auto& strategy1 = group[i];
      const auto& strategy2 = group[j];

      // find intersection between two strategies' synonyms
      std::unordered_set<std::string> intersection =
          getIntersection(strategy1, strategy2);

      if (intersection.empty()) {
        continue;
      }

      connectionGraph[strategy1].push_back(strategy2);
      connectionGraph[strategy2].push_back(strategy1);
    }
  }
}

std::shared_ptr<Strategy> StrategySorter::getFirstStrategy(
    const std::vector<std::shared_ptr<Strategy>>& group) {
  size_t firstStrategyIndex = 0;
  std::pair<int, int> score =
      std::make_pair(group[0]->getSynonymCount(), group[0]->getPriorityScore());

  for (size_t i = 1; i < group.size(); i++) {
    int currentSynonymCount = group[i]->getSynonymCount();
    int currentPriorityScore = group[i]->getPriorityScore();

    if (currentSynonymCount < score.first) {
      score = std::make_pair(currentSynonymCount, currentPriorityScore);
      firstStrategyIndex = i;
    }

    if (currentSynonymCount == score.first &&
        currentPriorityScore < score.second) {
      score = std::make_pair(currentSynonymCount, currentPriorityScore);
      firstStrategyIndex = i;
    }
  }

  return group[firstStrategyIndex];
}

bool StrategySorter::isEasyToEvaluate(
    const std::shared_ptr<Strategy>& strategy1,
    const std::shared_ptr<Strategy>& strategy2) {
  int priority1 =
      (strategy1->getSynonymCount() + 1) * strategy1->getPriorityScore();
  int priority2 =
      (strategy2->getSynonymCount() + 1) * strategy2->getPriorityScore();

  return priority1 > priority2;
}

std::priority_queue<
    std::shared_ptr<Strategy>, std::vector<std::shared_ptr<Strategy>>,
    std::function<bool(const std::shared_ptr<Strategy>& strategy1,
                       const std::shared_ptr<Strategy>& strategy2)>>
StrategySorter::initializePriorityQueue(
    std::shared_ptr<Strategy>& firstStrategy) {
  std::priority_queue<
      std::shared_ptr<Strategy>, std::vector<std::shared_ptr<Strategy>>,
      std::function<bool(const std::shared_ptr<Strategy>& strategy1,
                         const std::shared_ptr<Strategy>& strategy2)>>
      priorityQueue(isEasyToEvaluate);

  priorityQueue.push(firstStrategy);
  return priorityQueue;
}

std::vector<std::shared_ptr<Strategy>> StrategySorter::getSortStrategies(
    std::shared_ptr<Strategy>& firstStrategy) {
  std::vector<std::shared_ptr<Strategy>> sortedGroup;
  std::unordered_set<std::shared_ptr<Strategy>> visited;

  // priority queue makes sure
  // the easy-to-evaluate strategy will be evaluated first
  auto priorityQueue = initializePriorityQueue(firstStrategy);

  // when getting the connected strategies,
  // we always pop from the top which is the easiest to evaluate
  while (!priorityQueue.empty()) {
    std::shared_ptr<Strategy> strategy = priorityQueue.top();
    priorityQueue.pop();

    if (visited.find(strategy) != visited.end()) {
      continue;
    }

    visited.insert(strategy);
    sortedGroup.push_back(strategy);

    for (const auto& connectedStrategy : connectionGraph[strategy]) {
      priorityQueue.push(connectedStrategy);
    }
  }

  return sortedGroup;
}
}  // namespace QPS