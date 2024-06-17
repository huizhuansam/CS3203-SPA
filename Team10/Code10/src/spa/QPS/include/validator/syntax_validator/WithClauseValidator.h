#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../exception/GrammarRule.h"
#include "../../tokenizer/Token.h"
#include "../../validator/IValidator.h"
#include "../../validator/syntax_validator/AttrCondValidator.h"

namespace QPS {
class WithClauseValidator : public IValidator {
 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
