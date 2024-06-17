#include "tokenizer/WhitespaceTokenCreator.h"

namespace QPS {
std::shared_ptr<Token> WhitespaceTokenCreator::createToken(
    std::string::const_iterator& it, std::string::const_iterator& end) {
  while (it != end && std::isspace(*it)) {
    StringHandler::pointNextChar(it);
  }

  // go back to the last non-whitespace character
  StringHandler::pointPreviousChar(it);

  return std::make_shared<Token>(TokenType::WHITESPACE, std::string(it, it));
};
}  // namespace QPS
