#pragma once

#include "../../exception/GrammarRule.h"
#include "../../exception/SyntaxError.h"
#include "../../validator/IValidator.h"
#include "../../validator/syntax_validator/PatternCondValidator.h"

namespace QPS {
class PatternClauseValidator : public IValidator {
 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
