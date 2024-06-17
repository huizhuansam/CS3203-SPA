#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../exception/GrammarRule.h"
#include "../../exception/SyntaxError.h"
#include "../../tokenizer/Token.h"
#include "../../validator/IValidator.h"
#include "../../validator/syntax_validator/DeclarationValidator.h"
#include "../../validator/syntax_validator/PatternClauseValidator.h"
#include "../../validator/syntax_validator/SuchThatClauseValidator.h"
#include "../../validator/syntax_validator/WithClauseValidator.h"

namespace QPS {
class ClauseListValidator : public IValidator {
 private:
  static std::unordered_map<std::string, std::shared_ptr<IValidator>>
      tokenToValidatorMap;

 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
