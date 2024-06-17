#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "IParser.h"
#include "tokenizer/Token.h"

namespace SP {
/// @brief Parser for programs
class ProgramParser : public IParser {
 public:
  /// @brief Parse the token vector
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  void parse(std::vector<std::unique_ptr<Token>>::iterator& it,
             std::vector<std::unique_ptr<Token>>::iterator& end) override;

 private:
  static void checkProcedureCallSemanticError(
      std::unordered_map<std::string, std::unordered_set<std::string>>
          procToProcCalls,
      std::unordered_set<std::string> procedureNames, std::string& startProc);
};
}  // namespace SP
