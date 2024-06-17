#include "cache/WithArgTupleHasher.h"

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

#include "../strategy/argument_types/RefType.h"
#include "HashCombiner.h"

namespace QPS {
std::size_t WithArgTupleHasher::operator()(
    const std::tuple<RefType, std::string, RefType, std::string>& key) const {
  auto arg1 = std::get<0>(key);
  auto arg2 = std::get<1>(key);
  auto arg3 = std::get<2>(key);
  auto arg4 = std::get<3>(key);
  std::vector<std::tuple<RefType, std::string>> args = {{arg1, arg2},
                                                        {arg3, arg4}};
  std::sort(args.begin(), args.end());
  size_t hashValue = 0;
  HashCombiner::hash_combine(hashValue, std::get<0>(args[0]));
  HashCombiner::hash_combine(hashValue, std::get<1>(args[0]));
  HashCombiner::hash_combine(hashValue, std::get<0>(args[1]));
  HashCombiner::hash_combine(hashValue, std::get<1>(args[1]));
  return hashValue;
}
}  // namespace QPS
