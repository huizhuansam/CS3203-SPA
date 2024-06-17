#pragma once

#include <stdexcept>

namespace SP {
/// @brief Exception for semantic errors
class SemanticError : public std::runtime_error {
 public:
  /// @brief Construct a new Semantic Error object
  /// @param message The error message
  explicit SemanticError(const std::string& message)
      : std::runtime_error(message) {}
};
}  // namespace SP
