#pragma once

#include "ContainerStmtExtractor.h"
#include "StmtLstExtractor.h"
#include "WriteFacade.h"

namespace SP {
/// @brief Extractor for if statements
class IfExtractor : public ContainerStmtExtractor {
 private:
  std::unordered_set<int> trueBranchLastExecutedStmtNumbers;

  std::unordered_set<int> falseBranchLastExecutedStmtNumbers;

  void consumeCondition(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end);

  void consumeTrueBranch(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end,
      int currentStmtNo, StmtLstExtractor& stmtListExtractor);

  void consumeFalseBranch(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end,
      int currentStmtNo, StmtLstExtractor& stmtListExtractor);

  void writeParentChildRelationship(StmtLstExtractor& stmtListExtractor,
                                    int currentStmtNo);

  void consumeEntities(StmtLstExtractor& stmtListExtractor, int currentStmtNo);

 public:
  /// @brief Construct a new If Extractor object
  /// @param writer A write facade providing write access to the PKB
  IfExtractor(WriteFacade& writer);

  /// @brief Extract if statements from a token vector
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  void extract(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end) override;

  /// @brief Get the last statement numbers executed
  std::unordered_set<int> getLastExecutedStmtNumbers() override;
};
}  // namespace SP
