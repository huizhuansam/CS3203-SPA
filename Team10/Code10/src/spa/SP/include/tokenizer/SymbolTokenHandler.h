#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "Token.h"
#include "TokenHandler.h"

namespace SP {
/// @brief Token handler for symbol tokens.
class SymbolTokenHandler : public TokenHandler {
 public:
  /// @brief Handle a token
  /// @param it The iterator to the current character
  /// @param end The iterator to the end of the string
  /// @return A unique pointer to the token
  std::unique_ptr<Token> handleToken(std::string::const_iterator& it,
                                     std::string::const_iterator& end) override;

 private:
  static std::unique_ptr<Token> handleExclamationMark(
      std::string::const_iterator& it, std::string::const_iterator& end);

  static std::unique_ptr<Token> handleEqual(std::string::const_iterator& it,
                                            std::string::const_iterator& end);

  static std::unique_ptr<Token> handleLessThan(
      std::string::const_iterator& it, std::string::const_iterator& end);

  static std::unique_ptr<Token> handleGreaterThan(
      std::string::const_iterator& it, std::string::const_iterator& end);

  static std::unique_ptr<Token> handleAmpersand(
      std::string::const_iterator& it, std::string::const_iterator& end);

  static std::unique_ptr<Token> handleVerticalBar(
      std::string::const_iterator& it, std::string::const_iterator& end);

  static std::unordered_map<char, std::function<std::unique_ptr<Token>()>>
      charToTokenHandlerMap;

  static std::unordered_map<
      char, std::function<std::unique_ptr<Token>(std::string::const_iterator&,
                                                 std::string::const_iterator&)>>
      charToSpecialTokenHandlerMap;
};
}  // namespace SP
