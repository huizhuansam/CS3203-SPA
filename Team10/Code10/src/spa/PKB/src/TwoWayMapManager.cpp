#include "TwoWayMapManager.h"

#include <algorithm>
#include <unordered_set>

template <typename K, typename V>
void TwoWayMapManager<K, V>::insert(K key, V value) {
  leftSet.insert(key);
  rightSet.insert(value);

  leftToRightMap[key].insert(value);
  rightToLeftMap[value].insert(key);
}

template <typename K, typename V>
void TwoWayMapManager<K, V>::clear() {
  leftToRightMap.clear();
  rightToLeftMap.clear();
  leftSet.clear();
  rightSet.clear();
}

template <typename K, typename V>
std::unordered_set<V> TwoWayMapManager<K, V>::getLeftToRight(K key) {
  auto it = leftToRightMap.find(key);
  if (it != leftToRightMap.end()) {
    return it->second;
  }
  const std::unordered_set<V> emptyVector = {};
  return emptyVector;
}

template <typename K, typename V>
std::unordered_set<K> TwoWayMapManager<K, V>::getRightToLeft(V key) {
  auto it = rightToLeftMap.find(key);
  if (it != rightToLeftMap.end()) {
    return it->second;
  }
  const std::unordered_set<K> emptyVector = {};
  return emptyVector;
}

// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/dca2f158-ec25-4775-809b-e95bfe1a5d46
template <typename K, typename V>
std::unordered_set<std::pair<K, V>, PairHash>
TwoWayMapManager<K, V>::getAllPairs() {
  std::unordered_set<std::pair<K, V>, PairHash> pairs;
  // Iterate over the key-value pairs in the map
  for (const auto& kvp : leftToRightMap) {
    const auto key = kvp.first;
    const auto arr = kvp.second;
    for (const auto& val : arr) {
      pairs.insert({key, val});
    }
  }
  return pairs;
}
// ai-gen end

template <typename K, typename V>
std::unordered_set<K> TwoWayMapManager<K, V>::getAllLefts() {
  return leftSet;
}

template <typename K, typename V>
std::unordered_set<V> TwoWayMapManager<K, V>::getAllRights() {
  return rightSet;
}

// for unit testing
template class TwoWayMapManager<int, int>;
template class TwoWayMapManager<int, std::string>;
template class TwoWayMapManager<std::string, std::string>;