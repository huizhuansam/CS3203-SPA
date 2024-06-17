#pragma once

#include <CallStarStore.h>
#include <TwoWayMapManager.h>

#include <string>
#include <unordered_map>
#include <vector>

class RelationshipManager {
 private:
  TwoWayMapManager<int, int> followsStore;
  TwoWayMapManager<int, int> followsStarStore;
  TwoWayMapManager<int, int> parentStore;
  TwoWayMapManager<int, int> parentStarStore;
  TwoWayMapManager<int, std::string> usesStore;
  TwoWayMapManager<int, std::string> modifiesStore;
  TwoWayMapManager<std::string, std::string> usesProcedureStore;
  TwoWayMapManager<std::string, std::string> modifiesProcedureStore;
  TwoWayMapManager<std::string, std::string> callStore;
  CallStarStore<std::string, std::string> callStarStore;
  TwoWayMapManager<int, int> nextStore;

 public:
  // parent
  RelationshipManager() = default;
  void insertDirectParentChildRelationship(int parentStmtNo, int childStmtNo);
  std::unordered_set<int> getChildren(int parent);
  int getParent(int child);
  std::unordered_set<int> getChildrenStar(int parent);
  std::unordered_set<int> getParentStar(int child);
  std::unordered_set<std::pair<int, int>, PairHash> getAllParentPairs();
  std::unordered_set<std::pair<int, int>, PairHash> getAllParentStarPairs();
  void insertParentStarRelationship(int parent, int child);
  std::unordered_set<int> getAllParents();
  std::unordered_set<int> getAllChildren();

  // follows
  void insertDirectFollowsRelationship(int beforeStmtNo, int afterStmtNo);
  void insertFollowsStarRelationship(int beforeStmtNo, int afterStmtNo);
  int getStmtThatFollowsAfter(int stmtNo);
  int getStmtThatFollowsBefore(int stmtNo);
  std::unordered_set<int> getAllStmtsThatFollowAfter(int stmtNo);
  std::unordered_set<int> getAllStmtsThatFollowBefore(int stmtNo);
  std::unordered_set<std::pair<int, int>, PairHash> getAllFollowPairs();
  std::unordered_set<std::pair<int, int>, PairHash> getAllFollowStarPairs();
  std::unordered_set<int> getAllStmtsThatFollowAfterOtherStmts();
  std::unordered_set<int> getAllStmtsThatFollowBeforeOtherStmts();

  // calls
  void insertCallsRelationship(const std::string& sourceProcName,
                               const std::string& targetProcName);

  std::unordered_set<std::string> getProcsThatIsCalledBy(
      std::string& sourceProcName);
  std::unordered_set<std::string> getProcsThatCalls(
      std::string& targetProcName);
  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllCallPairs();
  std::unordered_set<std::string> getAllProcsThatCallOtherProcs();
  std::unordered_set<std::string> getAllProcsThatGetCalledByOtherProcs();

  // calls*
  std::unordered_set<std::string> getProcsThatIsCalledByStar(
      std::string& sourceProcName);
  std::unordered_set<std::string> getProcsThatCallsStar(
      std::string& targetProcName);
  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllCallStarPairs();

  // modifies
  void insertModifies(int stmtNo, const std::string& str);
  std::unordered_set<std::string> getVarsModifiedByStmt(int stmtNo);
  std::unordered_set<int> getStmtsThatModifyVar(std::string var);
  std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllVarModifiedByStmtPairs();
  void insertModifiesProcedure(const std::string& str1,
                               const std::string& str2);
  std::unordered_set<std::string> getVarsModifiedByProcedure(
      std::string& procedure);
  std::unordered_set<std::string> getProceduresThatModifyVar(std::string& var);
  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllVarModifiedByProcedurePairs();
  std::unordered_set<int> getAllStmtsThatModifyVars();
  std::unordered_set<std::string> getAllVarsModifiedByStmts();
  std::unordered_set<std::string> getAllProceduresThatModifyVars();
  std::unordered_set<std::string> getAllVarsModifiedByProcedures();

  // uses
  void insertUses(int stmtNo, const std::string& str);
  std::unordered_set<std::string> getVarsUsedByStmt(int stmtNo);
  std::unordered_set<int> getStmtsThatUseVar(std::string var);
  std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllVarsUsedByStmtPairs();
  void insertUsesProcedure(const std::string& str1, const std::string& str2);
  std::unordered_set<std::string> getVarsUsedByProcedure(std::string procedure);
  std::unordered_set<std::string> getProceduresThatUseVar(std::string var);
  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllVarUsedByProcedurePairs();
  std::unordered_set<int> getAllStmtsThatUseVars();
  std::unordered_set<std::string> getAllVarsUsedByStmts();
  std::unordered_set<std::string> getAllProceduresThatUseVars();
  std::unordered_set<std::string> getAllVarsUsedByProcedures();

  void insertNextRelationship(int previousStmtNo, int nextStmtNo);
  std::unordered_set<int> getStmtsNextOf(int stmtNo);
  std::unordered_set<int> getStmtsPreviousOf(int stmtNo);
  std::unordered_set<std::pair<int, int>, PairHash> getAllNextPairs();
  std::unordered_set<int> getAllStmtsThatAreNextOfOtherStmts();
  std::unordered_set<int> getAllStmtsThatArePreviousOfOtherStmts();

  void clear();
};