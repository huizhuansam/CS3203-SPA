#pragma once

#include <memory>
#include <vector>

#include "tokenizer/Token.h"

namespace SP {
/// @brief Extractor for design entities and abstractions
class DesignExtractor {
 private:
  static int stmtNumber;

 public:
  /// @brief The driver method for extracting designs from the tokenized program
  /// @param tokens A vector of tokens
  static void extract(std::vector<std::unique_ptr<Token>>& tokens);

  /// @brief Reset the statement number
  static void resetStmtNumber();

  /// @brief Get the statement number
  /// @return The statement number
  static int getStmtNumber();

  /// @brief Increment the statement number
  static void incrementStmtNumber();

  // Disallow instantiation
  DesignExtractor() = delete;
};
}  // namespace SP
