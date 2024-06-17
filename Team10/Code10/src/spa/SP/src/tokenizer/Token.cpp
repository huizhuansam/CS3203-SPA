#include "tokenizer/Token.h"

#include <utility>

namespace SP {
Token::Token(TokenType type, std::string value)
    : type(type), value(std::move(value)) {}

TokenType Token::getType() { return type; }

void Token::setType(TokenType newType) { this->type = newType; }

const std::string Token::getValue() { return value; }

bool Token::canBeName() {
  return type == TokenType::PROCEDURE || type == TokenType::READ ||
         type == TokenType::PRINT || type == TokenType::IF ||
         type == TokenType::THEN || type == TokenType::ELSE ||
         type == TokenType::WHILE || type == TokenType::CALL ||
         type == TokenType::NAME;
}
}  // namespace SP
