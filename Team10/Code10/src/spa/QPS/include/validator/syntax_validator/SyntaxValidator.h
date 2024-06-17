#pragma once

#include <memory>
#include <vector>

#include "../../exception/GrammarRule.h"
#include "../../exception/SyntaxError.h"
#include "../../tokenizer/Token.h"
#include "../../validator/IValidator.h"
#include "../../validator/syntax_validator/ClauseListValidator.h"
#include "../../validator/syntax_validator/DeclarationListValidator.h"
#include "../../validator/syntax_validator/SelectResultClauseValidator.h"

namespace QPS {
class SyntaxValidator : public IValidator {
 public:
  SyntaxValidator() = default;

  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
