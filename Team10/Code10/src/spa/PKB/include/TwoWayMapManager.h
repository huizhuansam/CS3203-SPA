#pragma once

#include <PKBUtil.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename K, typename V>
class TwoWayMapManager {
 protected:
  std::unordered_map<K, std::unordered_set<V>> leftToRightMap;
  std::unordered_map<V, std::unordered_set<K>> rightToLeftMap;
  std::unordered_set<K> leftSet;
  std::unordered_set<V> rightSet;

 public:
  TwoWayMapManager() = default;
  virtual ~TwoWayMapManager() = default;
  virtual void insert(K key, V value);
  virtual void clear();
  std::unordered_set<V> getLeftToRight(K key);
  std::unordered_set<K> getRightToLeft(V key);
  std::unordered_set<std::pair<K, V>, PairHash> getAllPairs();
  std::unordered_set<K> getAllLefts();
  std::unordered_set<V> getAllRights();
};