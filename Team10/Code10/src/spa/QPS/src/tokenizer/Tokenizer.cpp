#include "tokenizer/Tokenizer.h"

namespace QPS {
std::vector<std::shared_ptr<Token>> Tokenizer::tokenize(
    const std::string& queryString) {
  if (queryString.empty()) {
    throw SyntaxError("SyntaxError");
  }

  bool isWhitespaceQuery = true;
  for (char c : queryString) {
    if (!StringHandler::isWhitespace(c)) {
      isWhitespaceQuery = false;
      break;
    }
  }

  if (isWhitespaceQuery) {
    throw SyntaxError("SyntaxError");
  }

  std::vector<std::shared_ptr<Token>> tokens;
  std::string::const_iterator it = queryString.begin();
  std::string::const_iterator end = queryString.end();

  while (it != end) {
    char currentChar = *it;
    bool isLastCharPeriod = !tokens.empty() && tokens.back()->getValue() == ".";
    std::unique_ptr<TokenCreator> creator =
        TokenCreator::of(currentChar, isLastCharPeriod);
    std::shared_ptr<Token> token = creator->createToken(it, end);

    if (token->getType() != TokenType::WHITESPACE) {
      tokens.push_back(token);
    }

    StringHandler::pointNextChar(it);
  }

  return tokens;
}
}  // namespace QPS
