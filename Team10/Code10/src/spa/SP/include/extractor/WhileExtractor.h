#pragma once

#include <memory>
#include <vector>

#include "ContainerStmtExtractor.h"
#include "StmtLstExtractor.h"
#include "WriteFacade.h"
#include "tokenizer/Token.h"

namespace SP {
/// @brief Extractor for while statements
class WhileExtractor : public ContainerStmtExtractor {
 private:
  int thisStmtNo;

  void consumeCondition(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end);

  void consumeStmtList(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end);

  void writeParentChildRelationship(StmtLstExtractor& stmtListExtractor);

  void writeNextRelationshipToThisStmt(StmtLstExtractor& stmtListExtractor);

 public:
  /// @brief Construct a new While Extractor object
  /// @param writer A write facade providing write access to the PKB
  WhileExtractor(WriteFacade& writer);

  /// @brief Extract while statements from a token vector
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  void extract(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end) override;

  /// @brief Get the last statement numbers executed
  std::unordered_set<int> getLastExecutedStmtNumbers() override;
};
}  // namespace SP
