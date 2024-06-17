#include "validator/syntax_validator/EntOrStmtRefValidator.h"

namespace QPS {
void EntOrStmtRefValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  if (it == end) {
    throw SyntaxError(GrammarRule::REL_REF);
  }
  switch ((*it)->getType()) {
    case TokenType::NAME: {
      consume(it, end, TokenType::NAME, GrammarRule::NAME);
      break;
    }
    case TokenType::WILDCARD: {
      consume(it, end, TokenType::WILDCARD, GrammarRule::NAME);
      break;
    }
    case TokenType::INTEGER: {
      consume(it, end, TokenType::INTEGER, GrammarRule::NAME);
      break;
    }
    case TokenType::DOUBLE_QUOTE: {
      consume(it, end, TokenType::DOUBLE_QUOTE, GrammarRule::NAME);
      consume(it, end, TokenType::NAME, GrammarRule::NAME);
      consume(it, end, TokenType::DOUBLE_QUOTE, GrammarRule::NAME);
      break;
    }
    default:
      throw SyntaxError(GrammarRule::NAME);
  }
}
}  // namespace QPS
