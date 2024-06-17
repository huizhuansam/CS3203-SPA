#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "../parser/ParserUtil.h"
#include "../tokenizer/Token.h"
#include "strategy/argument_types/SynonymType.h"

namespace QPS {
class DeclarationParser {
 public:
  static std::unordered_map<std::string, SynonymType> parse(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end);

 private:
  static SynonymType getSynonymType(const std::string& type);
  static std::unordered_map<std::string, SynonymType> synonymTypeMap;
};
}  // namespace QPS
