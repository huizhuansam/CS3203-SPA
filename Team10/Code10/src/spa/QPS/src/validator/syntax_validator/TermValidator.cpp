#include "validator/syntax_validator/TermValidator.h"

namespace QPS {
void TermValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  // term: term '*' factor | term '/' factor | term '%' factor | factor
  FactorValidator factorValidator;
  factorValidator.validate(it, end);

  while (it != end && ((*it)->getType() == TokenType::TIMES ||
                       (*it)->getType() == TokenType::DIV ||
                       (*it)->getType() == TokenType::MOD)) {
    consume(it, end, (*it)->getType(), GrammarRule::TERM);
    factorValidator.validate(it, end);
  }
}
}  // namespace QPS
