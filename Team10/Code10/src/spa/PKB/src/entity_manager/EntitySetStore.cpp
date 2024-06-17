#include "entity_manager/EntitySetStore.h"

#include <iostream>
#include <string>

// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/79929c11-45e4-4e55-9996-cc966fd74a80
template <typename T>
void EntitySetStore<T>::insert(const T& element) {
  set.insert(element);
}

template <typename T>
std::unordered_set<T> EntitySetStore<T>::getAll() {
  return set;
}

template <typename T>
void EntitySetStore<T>::clear() {
  set.clear();
}

template class EntitySetStore<int>;
template class EntitySetStore<std::string>;
// ai-gen end
