#pragma once

#include <vector>

#include "IExtractor.h"
#include "WriteFacade.h"
#include "tokenizer/Token.h"

namespace SP {
/// @brief Extractor for statement lists
class StmtLstExtractor : public IExtractor {
 private:
  WriteFacade& writer;
  int firstStmtNo;
  int lastStmtNo;
  int containerStmtNo;
  std::vector<int> nonNestedStmtNo;
  std::unordered_set<int> lastExecutedStmtNumbers;
  std::unordered_set<std::string> varUsed;
  std::unordered_set<std::string> varModified;
  std::unordered_set<std::string> procCalled;
  std::unordered_map<int, std::unordered_set<std::string>> stmtCallMap;

 public:
  /// @brief Construct a new Stmt Lst Extractor object
  /// @param writer A write facade providing write access to the PKB
  StmtLstExtractor(WriteFacade& writer);

  /// @brief Construct a new Stmt Lst Extractor object
  /// @param writer A write facade providing write access to the PKB
  /// @param containerStmtNo The statement number of the container statement
  StmtLstExtractor(WriteFacade& writer, int containerStmtNo);

  /// @brief Get the first statement number in the statement list
  /// @return The first statement number in the statement list
  int getFirstStmtNo();

  /// @brief Get the last statement number in the statement list
  /// @return The last statement number in the statement list
  int getLastStmtNo();

  /// @brief Get the non-nested statement numbers in the statement list
  /// @return A vector of non-nested statement numbers in the statement list
  std::vector<int>& getNonNestedStmtNo();

  /// @brief Get the variables modified in the statement list
  /// @return A set of variable names modified in the statement list
  std::unordered_set<std::string>& getVarModified();

  /// @brief Get the variables used in the statement list
  /// @return A set of variable names used in the statement list
  std::unordered_set<std::string>& getVarUsed();

  /// @brief Get the procedures called in the statement list
  /// @return A set of procedure names called in the statement list
  std::unordered_set<std::string>& getProcCalled();

  /// @brief Get the statement call map
  /// @return A map of  number to set of procedure names
  /// called
  std::unordered_map<int, std::unordered_set<std::string>>& getStmtCallMap();

  /// @brief Get the last statement numbers executed
  std::unordered_set<int> getLastExecutedStmtNumbers();

  /// @brief Extract statement lists from a token vector
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  void extract(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end) override;

  /// @brief Append to the existing statement call map
  /// @param map A map of  number to set of procedure
  void appendToStmtCallMap(
      std::unordered_map<int, std::unordered_set<std::string>>& map);

  void addVarUsedByStmt(std::unordered_set<std::string>& varUsedByStmt);

  void addVarModifiedByStmt(std::unordered_set<std::string>& varModifiedByStmt);

  void addProcCalledByStmt(std::unordered_set<std::string>& procCalledByStmt);

  void addToStmtCallMap(int currentStmtNo,
                        std::unordered_set<std::string>& procCalledByStmt);

 private:
  void processFollowsRelationship();
};
}  // namespace SP
