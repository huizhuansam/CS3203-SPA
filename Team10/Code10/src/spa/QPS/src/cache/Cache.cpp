#include "cache/Cache.h"

namespace QPS {
bool Cache::isCached(
    const std::tuple<StrategyType, std::variant<StmtRefType, EntRefType>,
                     std::variant<StmtRefType, EntRefType>>& key) {
  return this->cache.find(key) != this->cache.end();
}

bool Cache::isCached(
    const std::tuple<RefType, std::string, RefType, std::string>& key) {
  return this->withCache.find(key) != this->withCache.end();
}

const std::vector<std::vector<std::string>>& Cache::get(
    const std::tuple<StrategyType, std::variant<StmtRefType, EntRefType>,
                     std::variant<StmtRefType, EntRefType>>& key) {
  return this->cache[key];
}

const Result& Cache::get(
    const std::tuple<RefType, std::string, RefType, std::string>& key) {
  return this->withCache[key];
}

const std::vector<std::vector<std::string>>& Cache::storeAndReturn(
    const std::tuple<StrategyType, std::variant<StmtRefType, EntRefType>,
                     std::variant<StmtRefType, EntRefType>>& key,
    const std::vector<std::vector<std::string>>& value) {
  bool shouldNotStore = false;
  auto first_variant = std::get<1>(key);
  if (std::holds_alternative<StmtRefType>(first_variant)) {
    if (std::get<StmtRefType>(first_variant) == StmtRefType::INTEGER) {
      shouldNotStore = true;
    }
  } else if (std::holds_alternative<EntRefType>(first_variant)) {
    if (std::get<EntRefType>(first_variant) == EntRefType::IDENT) {
      shouldNotStore = true;
    }
  }

  auto second_variant = std::get<2>(key);
  if (std::holds_alternative<StmtRefType>(second_variant)) {
    if (std::get<StmtRefType>(second_variant) == StmtRefType::INTEGER) {
      shouldNotStore = true;
    }
  } else if (std::holds_alternative<EntRefType>(second_variant)) {
    if (std::get<EntRefType>(second_variant) == EntRefType::IDENT) {
      shouldNotStore = true;
    }
  }

  if (shouldNotStore) {
    return value;
  }

  this->cache[key] = value;
  return this->cache[key];
}

const Result& Cache::storeAndReturn(
    const std::tuple<RefType, std::string, RefType, std::string>& key,
    const Result& value) {
  this->withCache[key] = std::move(value);
  return this->withCache[key];
}
}  // namespace QPS
