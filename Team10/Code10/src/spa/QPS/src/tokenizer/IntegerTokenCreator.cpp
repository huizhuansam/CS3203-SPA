#include "tokenizer/IntegerTokenCreator.h"

namespace QPS {
std::shared_ptr<Token> IntegerTokenCreator::createToken(
    std::string::const_iterator& it, std::string::const_iterator& end) {
  char currentChar = *it;
  bool hasNextChar = StringHandler::hasNextChar(it, end);

  // check if it is a name starting with a number
  bool isNextCharLetter =
      hasNextChar && StringHandler::isLetter(StringHandler::getNextChar(it));
  if (isNextCharLetter) {
    throw SyntaxError(GrammarRule::NAME);
  }

  // check if it is zero leading integer
  bool isCurrentZero = currentChar == '0';
  bool isNextCharDigit =
      hasNextChar && StringHandler::isDigit(StringHandler::getNextChar(it));
  if (isCurrentZero && isNextCharDigit) {
    throw SyntaxError(GrammarRule::INTEGER);
  }

  std::string number = StringHandler::formNumberString(it, end);
  return std::make_shared<Token>(TokenType::INTEGER, number);
}
}  // namespace QPS
