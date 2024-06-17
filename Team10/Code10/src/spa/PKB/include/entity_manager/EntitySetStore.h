#pragma once

#include <iostream>
#include <string>
#include <unordered_set>

template <typename T>
class EntitySetStore {
 private:
  std::unordered_set<T> set;

 public:
  void insert(const T& element);
  std::unordered_set<T> getAll();
  void clear();
};
