#pragma once

#include <memory>
#include <vector>

#include "tokenizer/Token.h"

namespace SP {
/// @brief Interface for extractors
class IExtractor {
 public:
  /// @brief Extracts information from a token vector
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  virtual void extract(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end) = 0;

  virtual ~IExtractor() = default;
};
}  // namespace SP
