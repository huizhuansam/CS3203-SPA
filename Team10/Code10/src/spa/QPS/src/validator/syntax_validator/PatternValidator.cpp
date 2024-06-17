#include "validator/syntax_validator/PatternValidator.h"

namespace QPS {
void PatternValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  if (it == end) {
    throw SyntaxError(GrammarRule::PATTERN);
  }
  consume(it, end, TokenType::NAME, GrammarRule::PATTERN);
  consume(it, end, TokenType::OPEN_BRACKET, GrammarRule::PATTERN);
  EntRefValidator entRefValidator;
  entRefValidator.validate(it, end);
  consume(it, end, TokenType::COMMA, GrammarRule::PATTERN);
  bool isWildcard = it != end && (*it)->getType() == TokenType::WILDCARD;
  ExpressionSpecValidator expressionSpecValidator;
  expressionSpecValidator.validate(it, end);
  // optional third argument
  if (it != end && (*it)->getType() == TokenType::COMMA) {
    if (!isWildcard) {
      // if there is a third argument, then second argument must be a wildcard
      throw SyntaxError(GrammarRule::PATTERN);
    }
    consume(it, end, TokenType::COMMA, GrammarRule::PATTERN);
    consume(it, end, TokenType::WILDCARD, GrammarRule::PATTERN);
  }
  consume(it, end, TokenType::CLOSE_BRACKET, GrammarRule::PATTERN);
}
}  // namespace QPS
