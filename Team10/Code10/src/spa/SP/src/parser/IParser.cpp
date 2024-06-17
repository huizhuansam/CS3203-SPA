#include "IParser.h"

#include <memory>

#include "exception/GrammarRule.h"
#include "exception/SyntaxError.h"
#include "tokenizer/TokenType.h"

namespace SP {
void IParser::expect(std::vector<std::unique_ptr<Token>>::iterator& it,
                     std::vector<std::unique_ptr<Token>>::iterator& end,
                     TokenType expectedType, const std::string& rule) {
  // out of bound error
  if (it == end) {
    throw SyntaxError(rule);
  }

  // type mismatch error
  if (expectedType == TokenType::NAME) {
    if ((*it)->canBeName()) {
      // parse keyword as name
      (*it)->setType(TokenType::NAME);
    } else {
      throw SyntaxError(rule);
    }
    return;
  }

  if ((*it)->getType() != expectedType) {
    throw SyntaxError(rule);
  }
}

void IParser::consume(std::vector<std::unique_ptr<Token>>::iterator& it,
                      std::vector<std::unique_ptr<Token>>::iterator& end,
                      TokenType expectedType, const std::string& rule) {
  expect(it, end, expectedType, rule);
  it++;
}
}  // namespace SP
