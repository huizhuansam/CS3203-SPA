#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "../tokenizer/TokenType.h"

namespace QPS {
/// @brief The Token class represents a token in the Simple Programming
/// Language. A token is a pair of a TokenType and a string value. The TokenType
/// represents the type of the token, and the string value represents the actual
/// value of the token.
class Token {
 private:
  TokenType type;
  std::string value;

 public:
  /// @brief Construct a new Token object
  /// @param type The type of the token
  /// @param value The value of the token
  Token(TokenType type, std::string value);

  /// @brief Get the type of the token
  /// @return The type of the token
  TokenType getType();

  /// @brief Get the value of the token
  /// @return The value of the token
  const std::string getValue();
};

}  // namespace QPS
