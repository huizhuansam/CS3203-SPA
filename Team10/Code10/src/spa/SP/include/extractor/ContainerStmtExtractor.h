#pragma once

#include "IStmtExtractor.h"

namespace SP {
class ContainerStmtExtractor : public IStmtExtractor {
 private:
  std::unordered_set<std::string> varUsed;

  std::unordered_set<std::string> varModified;

  std::unordered_map<int, std::unordered_set<std::string>> stmtCallMap;

  std::unordered_set<std::string> procCalled;

 protected:
  WriteFacade& writer;

 public:
  ContainerStmtExtractor(WriteFacade& writer);

  void addAllVarUsedToThisStmt(StmtLstExtractor& stmtListExtractor);

  void addAllVarModifiedToThisStmt(StmtLstExtractor& stmtListExtractor);

  void addAllProcCalledToThisStmt(StmtLstExtractor& stmtListExtractor);

  void writeAllVarUsed(int currentStmtNo);

  void writeAllVarModified(int currentStmtNo);

  void addVarUsed(const std::string& var);

  void setStmtCallMap(
      std::unordered_map<int, std::unordered_set<std::string>>& map);

  /// @brief Append to the existing statement call map
  /// @param map A map of  number to set of procedure
  void appendToStmtCallMap(
      std::unordered_map<int, std::unordered_set<std::string>>& map);

  void addProcCalled(const std::string& proc);

  /// @brief Get the statement call map
  /// @return A map of  number to set of procedure names
  /// called
  std::unordered_map<int, std::unordered_set<std::string>>& getStmtCallMap();

  void dumpContentsInto(StmtLstExtractor& stmtListExtractor,
                        int currentStmtNo) override;

  ~ContainerStmtExtractor() = default;
};
}  // namespace SP
