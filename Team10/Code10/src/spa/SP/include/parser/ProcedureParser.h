#pragma once

#include <unordered_set>
#include <vector>

#include "IParser.h"
#include "tokenizer/Token.h"

namespace SP {
/// @brief Parser for procedures
class ProcedureParser : public IParser {
 private:
  std::string procedureName;
  std::unordered_set<std::string> procCalledSet;

 public:
  /// @brief Parse the token vector
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  void parse(std::vector<std::unique_ptr<Token>>::iterator& it,
             std::vector<std::unique_ptr<Token>>::iterator& end) override;

  /// @brief Get the Procedure Name
  /// @return The name of the procedure
  std::string getProcedureName();

  void setProcCalledSet(std::unordered_set<std::string> set);

  std::unordered_set<std::string> getProcCalledSet();
};
}  // namespace SP
