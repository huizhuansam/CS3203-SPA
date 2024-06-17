#pragma once

#include <vector>

#include "IStmtExtractor.h"
#include "WriteFacade.h"
#include "tokenizer/Token.h"

namespace SP {
/// @brief Extractor for assign statements
class AssignExtractor : public IStmtExtractor {
 private:
  WriteFacade& writer;

  std::unordered_set<std::string> varUsed;

  std::unordered_set<std::string> varModified;

  std::string varModifiedName;

  void extractVarName(std::vector<std::unique_ptr<Token>>::iterator& it,
                      const std::vector<std::unique_ptr<Token>>::iterator& end);

  void extractExpression(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end);

  void processModifies(const std::string& varName);

  void processUsesAndPattern(
      std::vector<std::unique_ptr<Token>>::iterator& exprStart,
      std::vector<std::unique_ptr<Token>>::iterator& exprEnd);

  void writeAssignExprPattern(const std::string& var,
                              const std::vector<std::string>& expr);

 public:
  /// @brief Construct a new Assign Extractor object
  /// @param writer A write facade providing write access to the PKB
  AssignExtractor(WriteFacade& writer);

  /// @brief Extract assign statements from a token vector
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  void extract(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end) override;

  void dumpContentsInto(StmtLstExtractor& stmtListExtractor,
                        int currentStmtNo) override;
};
}  // namespace SP
