#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../exception/GrammarRule.h"
#include "../../tokenizer/Token.h"
#include "../../tokenizer/TokenType.h"
#include "../../validator/IValidator.h"
#include "../../validator/syntax_validator/RefValidator.h"

namespace QPS {
class AttrCompareValidator : public IValidator {
 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
