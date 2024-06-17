#include "validator/syntax_validator/AttrRefValidator.h"

namespace QPS {
void AttrRefValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  consume(it, end, TokenType::NAME, GrammarRule::REF);
  consume(it, end, TokenType::PERIOD, GrammarRule::REF);
  consume(it, end, TokenType::ATTR_NAME, GrammarRule::REF);
}
}  // namespace QPS
