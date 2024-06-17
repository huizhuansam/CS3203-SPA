#pragma once

#include "../parser/ParserUtil.h"
#include "strategy/WithStrategy.h"

namespace QPS {
class WithParser {
 public:
  std::shared_ptr<WithStrategy> parse(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::unordered_map<std::string, SynonymType>& declarationsMap);

 private:
  static std::unordered_map<std::pair<SynonymType, std::string>, RefType,
                            PairHash>
      typeMap;

  static std::pair<std::string, RefType> parseRef(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::unordered_map<std::string, SynonymType>& declarationsMap);

  static std::pair<std::string, RefType> parseAttrRef(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::unordered_map<std::string, SynonymType>& declarationsMap);

  static RefType getRefType(SynonymType type, const std::string& attrName);
};
}  // namespace QPS
