#pragma once

#include "../../exception/GrammarRule.h"
#include "../../exception/SyntaxError.h"
#include "../../validator/IValidator.h"
#include "../../validator/syntax_validator/ExpressionValidator.h"

namespace QPS {
class FactorValidator : public IValidator {
 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
