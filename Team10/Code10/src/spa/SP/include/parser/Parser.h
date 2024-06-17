#pragma once

#include <memory>
#include <vector>

#include "tokenizer/Token.h"

namespace SP {
/// @brief This class is the entry point for parsing programs written in the
/// SIMPLE language
class Parser {
 public:
  /// @brief The driver method for parsing the tokenized program
  /// @param tokens A vector of tokens
  static void parse(std::vector<std::unique_ptr<Token>>& tokens);

  // Disallow instantiation
  Parser() = delete;
};
}  // namespace SP
