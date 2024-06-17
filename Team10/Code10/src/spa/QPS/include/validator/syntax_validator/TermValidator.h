#pragma once

#include "../../exception/GrammarRule.h"
#include "../../tokenizer/TokenType.h"
#include "../../validator/IValidator.h"
#include "../../validator/syntax_validator/FactorValidator.h"

namespace QPS {
class TermValidator : public IValidator {
 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
