#pragma once

#include "../../exception/GrammarRule.h"
#include "../../validator/IValidator.h"
#include "../../validator/syntax_validator/TermValidator.h"

namespace QPS {
class ExpressionValidator : public IValidator {
 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
