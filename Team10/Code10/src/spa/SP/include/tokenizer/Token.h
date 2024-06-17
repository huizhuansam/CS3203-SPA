#pragma once

#include <string>

#include "TokenType.h"

namespace SP {
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

  /// @brief Set the type of the token
  /// @param type The new type of the token
  void setType(TokenType type);

  /// @brief Get the value of the token
  /// @return The value of the token
  const std::string getValue();

  /// @brief Determine if the token can be a name
  /// @return True if the token can be a name, false otherwise
  bool canBeName();
};

}  // namespace SP
