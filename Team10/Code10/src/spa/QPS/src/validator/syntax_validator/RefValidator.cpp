#include "validator/syntax_validator/RefValidator.h"

namespace QPS {
void RefValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  if (it == end) {
    throw SyntaxError(GrammarRule::REF);
  }
  const auto& tokenType = (*it)->getType();
  switch (tokenType) {
    case TokenType::DOUBLE_QUOTE: {
      consume(it, end, TokenType::DOUBLE_QUOTE, GrammarRule::REF);
      consume(it, end, TokenType::NAME, GrammarRule::REF);
      consume(it, end, TokenType::DOUBLE_QUOTE, GrammarRule::REF);
      break;
    }
    case TokenType::INTEGER: {
      consume(it, end, TokenType::INTEGER, GrammarRule::REF);
      break;
    }
    case TokenType::NAME: {
      AttrRefValidator attrRefValidator;
      attrRefValidator.validate(it, end);
      break;
    }
    default: {
      throw SyntaxError(GrammarRule::REF);
    }
  }
}
}  // namespace QPS
