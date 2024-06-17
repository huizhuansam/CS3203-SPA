#include "tokenizer/Tokenizer.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "StringHandler.h"
#include "tokenizer/TokenHandler.h"

namespace SP {
std::vector<std::unique_ptr<Token>> Tokenizer::tokenize(
    const std::string& source) {
  if (source.empty()) {
    throw std::runtime_error("Empty source");
  }

  std::vector<std::unique_ptr<Token>> tokens;
  std::string::const_iterator it = source.begin();
  std::string::const_iterator end = source.end();

  while (it != end) {
    char currentChar = *it;
    std::unique_ptr<TokenHandler> handler = TokenHandler::of(currentChar);
    std::unique_ptr<Token> token = handler->handleToken(it, end);

    if (token->getType() != TokenType::WHITESPACE) {
      tokens.push_back(std::move(token));
    }

    StringHandler::pointNextChar(it);
  }

  return tokens;
}
}  // namespace SP
