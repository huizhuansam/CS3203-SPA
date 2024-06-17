#pragma once

#include "StmtParser.h"

namespace SP {
/// @brief Parser for if statements
class IfParser : public StmtParser {
 public:
  /// @brief Parse the token vector
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  void parse(std::vector<std::unique_ptr<Token>>::iterator& it,
             std::vector<std::unique_ptr<Token>>::iterator& end) override;
};
}  // namespace SP
