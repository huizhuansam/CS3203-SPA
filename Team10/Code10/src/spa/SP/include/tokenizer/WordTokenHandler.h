#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Token.h"
#include "TokenHandler.h"

namespace SP {
/// @brief Token handler for word tokens.
class WordTokenHandler : public TokenHandler {
 private:
  static const std::unordered_map<std::string, TokenType> wordToTokenTypeMap;

 public:
  /// @brief Handle a token
  /// @param it The iterator to the current character
  /// @param end The iterator to the end of the string
  /// @return A unique pointer to the token
  std::unique_ptr<Token> handleToken(std::string::const_iterator& it,
                                     std::string::const_iterator& end) override;
};
}  // namespace SP
