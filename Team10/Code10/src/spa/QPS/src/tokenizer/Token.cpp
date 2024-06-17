#include "tokenizer/Token.h"

namespace QPS {
Token::Token(TokenType type, std::string value)
    : type(type), value(std::move(value)) {}

TokenType Token::getType() { return type; }

const std::string Token::getValue() { return value; }
}  // namespace QPS
