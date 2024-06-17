#include "WordTokenHandler.h"

#include "StringHandler.h"

namespace SP {
const std::unordered_map<std::string, TokenType>
    WordTokenHandler::wordToTokenTypeMap = {
        {"procedure", TokenType::PROCEDURE}, {"read", TokenType::READ},
        {"print", TokenType::PRINT},         {"call", TokenType::CALL},
        {"while", TokenType::WHILE},         {"if", TokenType::IF},
        {"then", TokenType::THEN},           {"else", TokenType::ELSE},
};

std::unique_ptr<Token> WordTokenHandler::handleToken(
    std::string::const_iterator& it, std::string::const_iterator& end) {
  std::string word = StringHandler::formWordString(it, end);
  TokenType tokenType;

  if (wordToTokenTypeMap.find(word) != wordToTokenTypeMap.end()) {
    tokenType = wordToTokenTypeMap.at(word);
  } else {
    tokenType = TokenType::NAME;
  }

  return std::make_unique<Token>(tokenType, word);
}
}  // namespace SP
