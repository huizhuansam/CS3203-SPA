#pragma once

#include <memory>
#include <string>

#include "../exception/SyntaxError.h"
#include "../tokenizer/Token.h"
#include "StringHandler.h"

namespace QPS {
class TokenCreator {
 public:
  /// @brief Factory method to create a token creator for a specific character
  /// @param character The character to create a token creator for
  /// @return A unique pointer to the token creator
  static std::unique_ptr<TokenCreator> of(char character, bool isLasCharPeriod);

  /// @brief Create a token
  /// @param it The iterator to the current character
  /// @param end The iterator to the end of the string
  /// @return A shared pointer to the token
  virtual std::shared_ptr<Token> createToken(
      std::string::const_iterator& it, std::string::const_iterator& end) = 0;

  virtual ~TokenCreator() = default;
};
}  // namespace QPS
