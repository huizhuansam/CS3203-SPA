#pragma once

#include <vector>

#include "IParser.h"
#include "tokenizer/Token.h"

namespace SP {
/// @brief Parser for statements
class StmtParser : public IParser {
 private:
  std::string procCalled;

 public:
  /// @brief Parse the token vector
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  /// @return The parsed statement
  static std::unique_ptr<StmtParser> of(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      std::vector<std::unique_ptr<Token>>::iterator& end);

  void setProcCalled(std::string& procName);
  std::string getProcCalled();
};
}  // namespace SP
