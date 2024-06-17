#pragma once

#include "../../exception/GrammarRule.h"
#include "../../exception/SyntaxError.h"
#include "../../tokenizer/Token.h"
#include "../../validator/IValidator.h"
#include "../../validator/syntax_validator/DeclarationValidator.h"

namespace QPS {
class DeclarationListValidator : public IValidator {
 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
