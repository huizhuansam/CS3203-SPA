#include "validator/syntax_validator/WithClauseValidator.h"

namespace QPS {
void WithClauseValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  consume(it, end, "with", GrammarRule::WITH_CL);
  AttrCondValidator validator;
  validator.validate(it, end);
}
}  // namespace QPS
