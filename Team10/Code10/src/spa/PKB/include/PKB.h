#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "EntityManager.h"
#include "PatternManager.h"
#include "RelationshipManager.h"

class PKB {
  // ai-gen start(gpt, 1, e)
  // prompt: https://chat.openai.com/share/5765cbd9-43bc-41c3-ae9f-7bebba3c41a3
 private:
  PKB();
  PKB(const PKB&) = delete;
  PKB& operator=(const PKB&) = delete;
  EntityManager entityManager;
  PatternManager patternManager;
  RelationshipManager relationshipManager;

 public:
  static PKB& getPKB();
  void clear();
  // ai-gen end

  // Entity Manager
  void addVariable(const std::string& var);
  void addConstant(const std::string& constant);
  void addProcedure(const std::string& proc);
  void addStatement(StatementType type, int stmtNo);

  void insertStmtCallsProc(int stmtNo, const std::string& procName);
  void insertStmtPrintsVar(int stmtNo, const std::string& var);
  void insertStmtReadsVar(int stmtNo, const std::string& var);

  std::unordered_set<std::string> getAllVariables();
  std::unordered_set<std::string> getAllConstants();
  std::unordered_set<std::string> getAllProcedures();
  std::unordered_set<int> getStatements();
  std::unordered_set<int> getAssigns();
  std::unordered_set<int> getReads();
  std::unordered_set<int> getPrints();
  std::unordered_set<int> getCalls();
  std::unordered_set<int> getWhiles();
  std::unordered_set<int> getIfs();

  std::string getProcCalledByStmt(int callStmt);
  std::unordered_set<int> getAllStmtsThatCallProc(std::string& procName);
  std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllCallsProcPairs();
  std::unordered_set<std::string> getAllProceduresCalledByStmts();

  std::string getVarPrintedByStmt(int printStmt);
  std::unordered_set<int> getAllStmtsThatPrintVar(std::string& var);
  std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllPrintVarPairs();
  std::unordered_set<std::string> getAllVarsPrintByStmts();

  std::string getVarReadByStmt(int readStmt);
  std::unordered_set<int> getAllStmtsThatReadVar(std::string& var);
  std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllReadVarPairs();
  std::unordered_set<std::string> getAllVarsReadByStmts();

  // Pattern Manager
  void addAssignExpPattern(int stmtNo, const std::string& var,
                           const std::vector<std::string>& exp);

  void addWhileControlVariable(int stmtNo, const std::string& var);
  void addIfControlVariable(int stmtNo, const std::string& var);

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllAssignExpPairs();

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsPartialMatch(const std::string& var,
                                const std::vector<std::string>& infixTokens);

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsSynonymPartialMatch(
      const std::vector<std::string>& infixTokens);

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsExactMatch(const std::string& var,
                              const std::vector<std::string>& infixTokens);

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsSynonymExactMatch(
      const std::vector<std::string>& infixTokens);

  // while
  std::unordered_set<std::string> getControlVariableOfWhileStmt(int stmtNo);
  std::unordered_set<int> getWhileStmtsThatUseControlVariable(
      const std::string& var);
  std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllWhileControlVariablePairs();
  std::unordered_set<int> getAllWhileStmtsThatUseControlVariables();
  std::unordered_set<std::string> getAllWhileControlVariables();

  // if
  std::unordered_set<std::string> getControlVariableOfIfStmt(int stmtNo);
  std::unordered_set<int> getIfStmtsThatUseControlVariable(
      const std::string& var);
  std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllIfControlVariablePairs();
  std::unordered_set<int> getAllIfStmtsThatUseControlVariables();
  std::unordered_set<std::string> getAllIfControlVariables();

  // Relationship Manager
  // parent
  void insertDirectParentChildRelationship(int parentStmtNo, int childStmtNo);
  std::unordered_set<int> getChildren(int parent);
  int getParent(int child);
  std::unordered_set<int> getChildrenStar(int parent);
  std::unordered_set<int> getParentsStar(int child);
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
  getAllVarUsedByStmtPairs();
  void insertUsesProcedure(const std::string& str1, const std::string& str2);
  std::unordered_set<std::string> getVarsUsedByProcedure(std::string procedure);
  std::unordered_set<std::string> getProceduresThatUseVar(std::string var);
  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllVarUsedByProcedurePairs();
  std::unordered_set<int> getAllStmtsThatUseVars();
  std::unordered_set<std::string> getAllVarsUsedByStmts();
  std::unordered_set<std::string> getAllProceduresThatUseVars();
  std::unordered_set<std::string> getAllVarsUsedByProcedures();

  // next
  void insertNextRelationship(int previousStmtNo, int nextStmtNo);
  std::unordered_set<int> getStmtsNextOf(int stmtNo);
  std::unordered_set<int> getStmtsPreviousOf(int stmtNo);
  std::unordered_set<std::pair<int, int>, PairHash> getAllNextPairs();
  std::unordered_set<int> getAllStmtsThatAreNextOfOtherStmts();
  std::unordered_set<int> getAllStmtsThatArePreviousOfOtherStmts();
};
