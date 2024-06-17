#pragma once

#include <unordered_map>
#include <unordered_set>

#include "strategy/argument_types/AttrNameType.h"
#include "strategy/argument_types/RefType.h"
#include "strategy/argument_types/SynonymType.h"

namespace QPS {
class RefTypeController {
 private:
  static const std::unordered_set<RefType> boolStrategyTypes;
  static const std::unordered_set<RefType> strictStmtTypes;

  static const std::unordered_map<RefType, SynonymType> synonymTypeMap;
  static const std::unordered_map<RefType, AttrNameType> attrNameTypeMap;

 public:
  static bool isBoolResult(RefType refType);

  static bool isStrictStmtType(RefType refType);

  static SynonymType getSynonymType(RefType refType);

  static AttrNameType getAttrNameType(RefType refType);
};
}  // namespace QPS
