#include "validator/syntax_validator/AttrCompareValidator.h"

namespace QPS {
void AttrCompareValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  RefValidator refValidator;
  refValidator.validate(it, end);
  // consume '='
  consume(it, end, TokenType::EQ, GrammarRule::ATTR_COMPARE);
  refValidator.validate(it, end);
}
}  // namespace QPS
