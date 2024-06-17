#include "validator/syntax_validator/StmtRefValidator.h"

namespace QPS {
void StmtRefValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  if (it == end) {
    throw SyntaxError(GrammarRule::NAME);
  }
  switch ((*it)->getType()) {
    case TokenType::NAME: {
      this->consume(it, end, TokenType::NAME, GrammarRule::EXPRESSION_SPEC);
      break;
    }
    case TokenType::WILDCARD: {
      consume(it, end, TokenType::WILDCARD, GrammarRule::EXPRESSION_SPEC);
      break;
    }
    case TokenType::INTEGER: {
      consume(it, end, TokenType::INTEGER, GrammarRule::EXPRESSION_SPEC);
      break;
    }
    default: {
      throw SyntaxError(GrammarRule::NAME);
    }
  }
}
}  // namespace QPS
