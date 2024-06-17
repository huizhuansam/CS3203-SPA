#include "IStmtExtractor.h"

#include "DesignExtractor.h"

namespace SP {
std::unordered_set<int> IStmtExtractor::getLastExecutedStmtNumbers() {
  return {DesignExtractor::getStmtNumber()};
}
}  // namespace SP
