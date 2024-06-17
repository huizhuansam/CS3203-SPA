#pragma once

#include <memory>
#include <vector>

#include "../../exception/GrammarRule.h"
#include "../../exception/SyntaxError.h"
#include "../../tokenizer/Token.h"
#include "../../validator/IValidator.h"
#include "../../validator/syntax_validator/RelCondValidator.h"

namespace QPS {
class SuchThatClauseValidator : public IValidator {
 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
