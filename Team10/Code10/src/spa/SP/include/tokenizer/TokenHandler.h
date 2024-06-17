#pragma once

#include <memory>

#include "Token.h"

namespace SP {
/// @brief Interface for token handlers. A token handler is responsible for
/// handling a specific character and creating a token from it.
class TokenHandler {
 public:
  /// @brief Factory method to create a token handler for a specific character
  /// @param character The character to create a token handler for
  /// @return A unique pointer to the token handler
  static std::unique_ptr<TokenHandler> of(char character);

  /// @brief Handle a token
  /// @param it The iterator to the current character
  /// @param end The iterator to the end of the string
  /// @return A unique pointer to the token
  virtual std::unique_ptr<Token> handleToken(
      std::string::const_iterator& it, std::string::const_iterator& end) = 0;

  virtual ~TokenHandler() = default;
};
}  // namespace SP
