#pragma once

#include <stdexcept>

namespace SP {
/// @brief Exception for syntax errors
class SyntaxError : public std::runtime_error {
 public:
  /// @brief Construct a new Syntax Error object
  /// @param message The error message
  explicit SyntaxError(const std::string& message)
      : std::runtime_error(message) {}
};
}  // namespace SP
