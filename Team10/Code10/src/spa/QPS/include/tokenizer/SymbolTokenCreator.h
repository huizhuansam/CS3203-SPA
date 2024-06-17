#pragma once

#include <memory>
#include <unordered_map>

#include "../exception/SyntaxError.h"
#include "../tokenizer/Token.h"
#include "../tokenizer/TokenCreator.h"

namespace QPS {
/// @brief Token creator for Symbol characters
class SymbolTokenCreator : public TokenCreator {
 public:
  /// @brief Create a token
  /// @param it The iterator to the current character
  /// @param end The iterator to the end of the string
  /// @return A shared pointer to the token
  std::shared_ptr<Token> createToken(std::string::const_iterator& it,
                                     std::string::const_iterator& end) override;
};
}  // namespace QPS
