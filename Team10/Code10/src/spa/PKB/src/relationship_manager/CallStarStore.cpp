#include "relationship_manager/CallStarStore.h"

#include <algorithm>
#include <unordered_set>

template <typename K, typename V>
void CallStarStore<K, V>::insert(K key, V value) {
  this->leftSet.insert(key);
  this->rightSet.insert(value);

  this->leftToRightMap[key].insert(value);
  this->rightToLeftMap[value].insert(key);

  for (const auto& e : this->rightToLeftMap[key]) {
    this->leftToRightMap[e].insert(value);
    // also merge ltr[value] inside
    this->leftToRightMap[e].insert(this->leftToRightMap[value].begin(),
                                   this->leftToRightMap[value].end());
  }

  for (const auto& e : this->leftToRightMap[value]) {
    this->rightToLeftMap[e].insert(key);
    // also merge rtl[key] inside
    this->rightToLeftMap[e].insert(this->rightToLeftMap[key].begin(),
                                   this->rightToLeftMap[key].end());
  }

  // Merge rtl[value] and rtl[key]
  this->rightToLeftMap[value].insert(this->rightToLeftMap[key].begin(),
                                     this->rightToLeftMap[key].end());

  // Merge ltr[key] and ltr[value]
  this->leftToRightMap[key].insert(this->leftToRightMap[value].begin(),
                                   this->leftToRightMap[value].end());
}

template class CallStarStore<std::string, std::string>;