#include "cache/WithArgTupleEqual.h"

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

#include "../strategy/argument_types/RefType.h"

namespace QPS {

bool WithArgTupleEqual::operator()(
    const std::tuple<RefType, std::string, RefType, std::string>& t1,
    const std::tuple<RefType, std::string, RefType, std::string>& t2) const {
  // sort the tuples to compare them
  std::vector<std::tuple<RefType, std::string>> args1 = {
      {std::get<0>(t1), std::get<1>(t1)}, {std::get<2>(t1), std::get<3>(t1)}};
  std::vector<std::tuple<RefType, std::string>> args2 = {
      {std::get<0>(t2), std::get<1>(t2)}, {std::get<2>(t2), std::get<3>(t2)}};
  std::sort(args1.begin(), args1.end());
  std::sort(args2.begin(), args2.end());

  return args1 == args2;
}
}  // namespace QPS
