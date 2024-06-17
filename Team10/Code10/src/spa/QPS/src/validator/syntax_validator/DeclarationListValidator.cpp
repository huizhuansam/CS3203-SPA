#include "validator/syntax_validator/DeclarationListValidator.h"

namespace QPS {
void DeclarationListValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  if (it == end) {
    throw SyntaxError(GrammarRule::DECLARATION);
  }
  DeclarationValidator declarationValidator;
  while (it != end && (*it)->getValue() != "Select") {
    declarationValidator.validate(it, end);
  }
}
}  // namespace QPS
