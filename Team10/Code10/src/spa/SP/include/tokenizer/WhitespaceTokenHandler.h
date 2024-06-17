#pragma once

#include <memory>

#include "Token.h"
#include "TokenHandler.h"

namespace SP {
/// @brief Token handler for whitespace characters
class WhitespaceTokenHandler : public TokenHandler {
 public:
  /// @brief Handle a token
  /// @param it The iterator to the current character
  /// @param end The iterator to the end of the string
  /// @return A unique pointer to the token
  std::unique_ptr<Token> handleToken(std::string::const_iterator& it,
                                     std::string::const_iterator& end) override;
};
}  // namespace SP
