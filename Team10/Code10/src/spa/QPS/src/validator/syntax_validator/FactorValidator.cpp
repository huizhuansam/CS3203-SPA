#include "validator/syntax_validator/FactorValidator.h"

namespace QPS {
void FactorValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  // factor: var_name | const_value | '(' expr ')'
  if (it == end) {
    throw SyntaxError(GrammarRule::FACTOR);
  }

  if ((*it)->getType() == TokenType::NAME) {
    consume(it, end, TokenType::NAME, GrammarRule::FACTOR);
    return;
  }

  if ((*it)->getType() == TokenType::INTEGER) {
    consume(it, end, TokenType::INTEGER, GrammarRule::FACTOR);
    return;
  }

  consume(it, end, TokenType::OPEN_BRACKET, GrammarRule::FACTOR);
  ExpressionValidator expressionValidator;
  expressionValidator.validate(it, end);
  consume(it, end, TokenType::CLOSE_BRACKET, GrammarRule::FACTOR);
}
}  // namespace QPS
