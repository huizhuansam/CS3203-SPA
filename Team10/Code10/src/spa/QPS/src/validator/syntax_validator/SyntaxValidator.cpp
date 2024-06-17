#include "validator/syntax_validator/SyntaxValidator.h"

namespace QPS {
void SyntaxValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  DeclarationListValidator declarationListValidator;
  declarationListValidator.validate(it, end);
  SelectResultClauseValidator selectResultClauseValidator;
  selectResultClauseValidator.validate(it, end);
  ClauseListValidator clauseListValidator;
  clauseListValidator.validate(it, end);
}
}  // namespace QPS
