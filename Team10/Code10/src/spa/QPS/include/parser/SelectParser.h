#pragma once

#include "../parser/ParserUtil.h"
#include "../tokenizer/Token.h"
#include "strategy/BooleanSelectStrategy.h"
#include "strategy/TupleSelectStrategy.h"
#include "strategy/argument_types/SynonymType.h"

namespace QPS {
class SelectParser {
 public:
  static std::shared_ptr<BooleanSelectStrategy> parseBooleanSelect(
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static std::shared_ptr<TupleSelectStrategy> parseTupleSelect(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end,
      const std::unordered_map<std::string, SynonymType>& declarationsMap);

 private:
  static std::tuple<std::string, SynonymType, AttrNameType> parseElem(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end,
      const std::unordered_map<std::string, SynonymType>& declarationsMap);

  static AttrNameType getAttrNameType(const std::string& attrName);
};
}  // namespace QPS
