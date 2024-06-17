#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Token.h"
#include "TokenHandler.h"

namespace SP {
/// @brief The Tokenizer class is responsible for tokenizing a Simple
/// Programming Language program. It takes a string representing the program
/// source and returns a vector of tokens.
class Tokenizer {
 public:
  /// @brief Tokenize a Simple Programming Language program
  /// @param programSource The source code of the program
  /// @return A vector of tokens
  static std::vector<std::unique_ptr<Token>> tokenize(
      const std::string& source);
};
}  // namespace SP
