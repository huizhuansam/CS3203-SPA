#include "cache/SuchThatArgTupleHasher.h"

#include <tuple>
#include <variant>

#include "HashCombiner.h"

namespace QPS {
size_t SuchThatArgTupleHasher::operator()(
    const std::tuple<StrategyType, std::variant<StmtRefType, EntRefType>,
                     std::variant<StmtRefType, EntRefType>>& key) const {
  size_t hashValue = 0;
  HashCombiner::hash_combine(hashValue, std::get<0>(key));
  HashCombiner::hash_combine(hashValue, std::get<1>(key));
  HashCombiner::hash_combine(hashValue, std::get<2>(key));
  return hashValue;
}
}  // namespace QPS
