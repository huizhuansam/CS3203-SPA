#pragma once

#include <memory>
#include <vector>

#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"
#include "tokenizer/TokenType.h"

namespace SP {
/// @brief The Parser Interface class. All program entity parsers are to
/// implement the `parse` method. Not to be confused with the SP::Parser class
/// which serves as the entry point to the parsing process.
class IParser {
 public:
  /// @brief The base parse method, to be overridden by implementing classes
  /// @param tokens A vector of tokens
  virtual void parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                     std::vector<std::unique_ptr<Token>>::iterator& end) = 0;

  /// @brief Expect a token of a certain type
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  /// @param type The expected token type
  /// @param rule The grammar rule that the token is expected to follow
  void expect(std::vector<std::unique_ptr<Token>>::iterator& it,
              std::vector<std::unique_ptr<Token>>::iterator& end,
              TokenType type, const std::string& rule);

  /// @brief Consume a token of a certain type
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  /// @param type The expected token type
  /// @param rule The grammar rule that the token is expected to follow
  void consume(std::vector<std::unique_ptr<Token>>::iterator& it,
               std::vector<std::unique_ptr<Token>>::iterator& end,
               TokenType type, const std::string& rule);

  virtual ~IParser() = default;
};
}  // namespace SP
