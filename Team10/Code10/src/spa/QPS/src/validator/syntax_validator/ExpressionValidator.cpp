#include "validator/syntax_validator/ExpressionValidator.h"

namespace QPS {
void ExpressionValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  // expr: expr '+' term | expr '-' term | term
  TermValidator termValidator;
  termValidator.validate(it, end);

  while (it != end && ((*it)->getType() == TokenType::PLUS ||
                       (*it)->getType() == TokenType::MINUS)) {
    TokenType plusOrMinus = (*it)->getType();
    consume(it, end, plusOrMinus, GrammarRule::EXPR);
    termValidator.validate(it, end);
  }
}
}  // namespace QPS
