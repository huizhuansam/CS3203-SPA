#include "tokenizer/SymbolTokenCreator.h"

namespace QPS {
std::shared_ptr<Token> SymbolTokenCreator::createToken(
    std::string::const_iterator& it,
    [[maybe_unused]] std::string::const_iterator& end) {
  char currentChar = *it;
  std::unordered_map<char, TokenType> symbolTokenMap = {
      {';', TokenType::SEMICOLON},
      {'(', TokenType::OPEN_BRACKET},
      {')', TokenType::CLOSE_BRACKET},
      {'+', TokenType::PLUS},
      {'-', TokenType::MINUS},
      {'*', TokenType::TIMES},
      {'/', TokenType::DIV},
      {'%', TokenType::MOD},
      {'_', TokenType::WILDCARD},
      {',', TokenType::COMMA},
      {'"', TokenType::DOUBLE_QUOTE},
      {'<', TokenType::OPEN_ANGLE_BRACKET},
      {'>', TokenType::CLOSE_ANGLE_BRACKET},
      {'.', TokenType::PERIOD},
      {'=', TokenType::EQ},
  };

  if (symbolTokenMap.find(currentChar) == symbolTokenMap.end()) {
    throw SyntaxError("SyntaxError");
  }

  return std::make_shared<Token>(symbolTokenMap[currentChar],
                                 std::string(1, currentChar));
}

}  // namespace QPS
