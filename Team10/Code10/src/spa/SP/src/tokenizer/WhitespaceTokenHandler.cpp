#include "WhitespaceTokenHandler.h"

#include <memory>

#include "StringHandler.h"

namespace SP {
std::unique_ptr<Token> WhitespaceTokenHandler::handleToken(
    std::string::const_iterator& it, std::string::const_iterator& end) {
  while (it != end && std::isspace(*it)) {
    StringHandler::pointNextChar(it);
  }

  // go back to the last non-whitespace character
  StringHandler::pointPreviousChar(it);

  return std::make_unique<Token>(TokenType::WHITESPACE, std::string(it, it));
};
}  // namespace SP
