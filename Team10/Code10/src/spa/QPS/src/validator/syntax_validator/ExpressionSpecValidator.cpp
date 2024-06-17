#include "validator/syntax_validator/ExpressionSpecValidator.h"

namespace QPS {
void ExpressionSpecValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  if (it == end) {
    throw SyntaxError(GrammarRule::EXPRESSION_SPEC);
  }
  switch ((*it)->getType()) {
    case TokenType::WILDCARD: {
      consume(it, end, TokenType::WILDCARD, GrammarRule::EXPRESSION_SPEC);
      if (it != end && (*it)->getType() == TokenType::DOUBLE_QUOTE) {
        consume(it, end, TokenType::DOUBLE_QUOTE, GrammarRule::EXPRESSION_SPEC);
        ExpressionValidator expressionValidator;
        expressionValidator.validate(it, end);
        consume(it, end, TokenType::DOUBLE_QUOTE, GrammarRule::EXPRESSION_SPEC);
        consume(it, end, TokenType::WILDCARD, GrammarRule::EXPRESSION_SPEC);
      }
      break;
    }
    case TokenType::DOUBLE_QUOTE: {
      consume(it, end, TokenType::DOUBLE_QUOTE, GrammarRule::EXPRESSION_SPEC);
      ExpressionValidator expressionValidator;
      expressionValidator.validate(it, end);
      consume(it, end, TokenType::DOUBLE_QUOTE, GrammarRule::EXPRESSION_SPEC);
      break;
    }
    default: {
      throw SyntaxError(GrammarRule::EXPRESSION_SPEC);
    }
  }
}
}  // namespace QPS
