#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../exception/SyntaxError.h"
#include "../tokenizer/Token.h"
#include "../tokenizer/TokenCreator.h"
#include "StringHandler.h"

namespace QPS {
/// @brief The Tokenizer class is responsible for tokenizing a query
/// written in PQL. It takes a string representing the query
/// and returns a vector of tokens.
class Tokenizer {
 public:
  /// @brief Tokenize a PQL query
  /// @param queryString The query string
  /// @return A vector of tokens
  static std::vector<std::shared_ptr<Token>> tokenize(
      const std::string& queryString);
};
}  // namespace QPS
