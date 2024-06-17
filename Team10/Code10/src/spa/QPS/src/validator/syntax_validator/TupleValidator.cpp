#include "TupleValidator.h"

namespace QPS {
void TupleValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  consume(it, end, TokenType::OPEN_ANGLE_BRACKET, GrammarRule::TUPLE);
  TupleElemValidator tupleElemValidator;
  tupleElemValidator.validate(it, end);
  while (it != end && (*it)->getType() != TokenType::CLOSE_ANGLE_BRACKET) {
    consume(it, end, TokenType::COMMA, GrammarRule::TUPLE);
    tupleElemValidator.validate(it, end);
  }
  consume(it, end, TokenType::CLOSE_ANGLE_BRACKET, GrammarRule::TUPLE);
}
}  // namespace QPS
