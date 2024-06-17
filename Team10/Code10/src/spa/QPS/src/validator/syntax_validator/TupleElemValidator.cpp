#include "TupleElemValidator.h"

namespace QPS {
void TupleElemValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  consume(it, end, TokenType::NAME, GrammarRule::TUPLE);
  if (it != end && (*it)->getType() == TokenType::PERIOD) {
    consume(it, end, TokenType::PERIOD, GrammarRule::ATTR_NAME);
    consume(it, end, TokenType::ATTR_NAME, GrammarRule::ATTR_NAME);
  }
}
}  // namespace QPS
