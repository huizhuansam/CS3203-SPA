#pragma once

#include <unordered_set>
#include <vector>

#include "IParser.h"
#include "StmtParser.h"
#include "tokenizer/Token.h"

namespace SP {
/// @brief Parser for statement lists
class StmtLstParser : public IParser {
 private:
  std::unordered_set<std::string> procCalledSet;

 public:
  /// @brief Parse the token vector
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  void parse(std::vector<std::unique_ptr<Token>>::iterator& it,
             std::vector<std::unique_ptr<Token>>::iterator& end) override;

  void addProcCalled(std::string& procName);

  std::unordered_set<std::string> getProcCalledSet();
};
}  // namespace SP
