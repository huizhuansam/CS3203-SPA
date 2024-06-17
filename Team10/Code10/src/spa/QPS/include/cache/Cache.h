#pragma once

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "../result/Result.h"
#include "../strategy/argument_types/EntRefType.h"
#include "../strategy/argument_types/ExprSpecType.h"
#include "../strategy/argument_types/RefType.h"
#include "../strategy/argument_types/StmtRefType.h"
#include "../strategy/strategy_types/StrategyType.h"
#include "SuchThatArgTupleHasher.h"
#include "WithArgTupleEqual.h"
#include "WithArgTupleHasher.h"

namespace QPS {
class Cache {
 private:
  std::unordered_map<
      std::tuple<StrategyType, std::variant<StmtRefType, EntRefType>,
                 std::variant<StmtRefType, EntRefType>>,
      std::vector<std::vector<std::string>>, SuchThatArgTupleHasher>
      cache;

  std::unordered_map<std::tuple<RefType, std::string, RefType, std::string>,
                     Result, WithArgTupleHasher, WithArgTupleEqual>
      withCache;

 public:
  bool isCached(
      const std::tuple<StrategyType, std::variant<StmtRefType, EntRefType>,
                       std::variant<StmtRefType, EntRefType>>& key);

  bool isCached(
      const std::tuple<RefType, std::string, RefType, std::string>& key);

  const std::vector<std::vector<std::string>>& get(
      const std::tuple<StrategyType, std::variant<StmtRefType, EntRefType>,
                       std::variant<StmtRefType, EntRefType>>& key);

  const Result& get(
      const std::tuple<RefType, std::string, RefType, std::string>& key);

  const std::vector<std::vector<std::string>>& storeAndReturn(
      const std::tuple<StrategyType, std::variant<StmtRefType, EntRefType>,
                       std::variant<StmtRefType, EntRefType>>& key,
      const std::vector<std::vector<std::string>>& value);

  const Result& storeAndReturn(
      const std::tuple<RefType, std::string, RefType, std::string>& key,
      const Result& value);
};
}  // namespace QPS
