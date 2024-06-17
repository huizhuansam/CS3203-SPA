#include "IntegerTokenHandler.h"

#include <stdexcept>

#include "StringHandler.h"

namespace SP {
std::unique_ptr<Token> IntegerTokenHandler::handleToken(
    std::string::const_iterator& it, std::string::const_iterator& end) {
  char currentChar = *it;
  bool hasNextChar = StringHandler::hasNextChar(it, end);

  // check if it is a name starting with a number
  bool isNextCharLetter =
      hasNextChar && StringHandler::isLetter(StringHandler::getNextChar(it));
  if (isNextCharLetter) {
    throw std::runtime_error("Invalid name");
  }

  // check if it is zero leading integer
  bool isCurrentZero = currentChar == '0';
  bool isNextCharDigit =
      hasNextChar && StringHandler::isDigit(StringHandler::getNextChar(it));
  if (isCurrentZero && isNextCharDigit) {
    throw std::runtime_error("Invalid number");
  }

  std::string number = StringHandler::formNumberString(it, end);
  return std::make_unique<Token>(TokenType::INTEGER, number);
}
}  // namespace SP
