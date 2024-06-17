#pragma once

#include <memory>
#include <unordered_map>

#include "../../exception/GrammarRule.h"
#include "../../exception/SyntaxError.h"
#include "../../validator/IValidator.h"
#include "../../validator/syntax_validator/EntRefValidator.h"
#include "../../validator/syntax_validator/ExpressionSpecValidator.h"

namespace QPS {
class PatternValidator : public IValidator {
 private:
  static std::unordered_map<std::string, std::shared_ptr<IValidator>>
      designEntityToValidatorMap;

 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
