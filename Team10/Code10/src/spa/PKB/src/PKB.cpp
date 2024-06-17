#include "PKB.h"

#include <iostream>
#include <string>
#include <vector>

// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/5765cbd9-43bc-41c3-ae9f-7bebba3c41a3
PKB::PKB() {}

PKB& PKB::getPKB() {
  static PKB pkb;
  return pkb;
}
// ai-gen end

void PKB::clear() {
  entityManager.clear();
  patternManager.clear();
  relationshipManager.clear();
}

// Entity Manager Methods
void PKB::addVariable(const std::string& var) {
  entityManager.addVariable(var);
}

void PKB::addConstant(const std::string& constant) {
  entityManager.addConstant(constant);
}
void PKB::addProcedure(const std::string& proc) {
  entityManager.addProcedure(proc);
}

void PKB::addStatement(StatementType type, int stmtNo) {
  entityManager.addStatement(type, stmtNo);
}

std::unordered_set<std::string> PKB::getAllVariables() {
  return entityManager.getAllVariables();
};

std::unordered_set<std::string> PKB::getAllConstants() {
  return entityManager.getAllConstants();
};

std::unordered_set<std::string> PKB::getAllProcedures() {
  return entityManager.getAllProcedures();
};

std::unordered_set<int> PKB::getStatements() {
  return entityManager.getStatements();
};

std::unordered_set<int> PKB::getAssigns() {
  return entityManager.getAssigns();
};

std::unordered_set<int> PKB::getReads() { return entityManager.getReads(); };

std::unordered_set<int> PKB::getPrints() { return entityManager.getPrints(); };

std::unordered_set<int> PKB::getCalls() { return entityManager.getCalls(); };

std::unordered_set<int> PKB::getWhiles() { return entityManager.getWhiles(); };

std::unordered_set<int> PKB::getIfs() { return entityManager.getIfs(); };

void PKB::insertStmtCallsProc(int stmtNo, const std::string& procName) {
  entityManager.insertStmtCallsProc(stmtNo, procName);
}

void PKB::insertStmtPrintsVar(int stmtNo, const std::string& var) {
  entityManager.insertStmtPrintsVar(stmtNo, var);
}

void PKB::insertStmtReadsVar(int stmtNo, const std::string& var) {
  entityManager.insertStmtReadsVar(stmtNo, var);
}

std::string PKB::getProcCalledByStmt(int callStmt) {
  return entityManager.getProcCalledByStmt(callStmt);
}

std::unordered_set<int> PKB::getAllStmtsThatCallProc(std::string& procName) {
  return entityManager.getAllStmtsThatCallProc(procName);
}

std::unordered_set<std::pair<int, std::string>, PairHash>
PKB::getAllCallsProcPairs() {
  return entityManager.getAllCallsProcPairs();
}

std::unordered_set<std::string> PKB::getAllProceduresCalledByStmts() {
  return entityManager.getAllProceduresCalledByStmts();
}

std::string PKB::getVarPrintedByStmt(int printStmt) {
  return entityManager.getVarPrintedByStmt(printStmt);
}

std::unordered_set<int> PKB::getAllStmtsThatPrintVar(std::string& var) {
  return entityManager.getAllStmtsThatPrintVar(var);
}

std::unordered_set<std::pair<int, std::string>, PairHash>
PKB::getAllPrintVarPairs() {
  return entityManager.getAllPrintVarPairs();
}

std::unordered_set<std::string> PKB::getAllVarsPrintByStmts() {
  return entityManager.getAllVarsPrintByStmts();
}

std::string PKB::getVarReadByStmt(int readStmt) {
  return entityManager.getVarReadByStmt(readStmt);
}

std::unordered_set<int> PKB::getAllStmtsThatReadVar(std::string& var) {
  return entityManager.getAllStmtsThatReadVar(var);
}
std::unordered_set<std::pair<int, std::string>, PairHash>
PKB::getAllReadVarPairs() {
  return entityManager.getAllReadVarPairs();
}
std::unordered_set<std::string> PKB::getAllVarsReadByStmts() {
  return entityManager.getAllVarsReadByStmts();
}

// Pattern Manager Methods
void PKB::addAssignExpPattern(int stmtNo, const std::string& var,
                              const std::vector<std::string>& exp) {
  patternManager.addAssignExpPattern(stmtNo, var, exp);
}

void PKB::addWhileControlVariable(int stmtNo, const std::string& var) {
  patternManager.addWhileControlVariable(stmtNo, var);
}
void PKB::addIfControlVariable(int stmtNo, const std::string& var) {
  patternManager.addIfControlVariable(stmtNo, var);
}

std::unordered_set<std::pair<std::string, std::string>, PairHash>
PKB::getAllAssignExpPairs() {
  return patternManager.getAllAssignExpPairs();
};

std::unordered_set<std::pair<std::string, std::string>, PairHash>
PKB::getAssignExpPairsPartialMatch(
    const std::string& var, const std::vector<std::string>& infixTokens) {
  return patternManager.getAssignExpPairsPartialMatch(var, infixTokens);
};

std::unordered_set<std::pair<std::string, std::string>, PairHash>
PKB::getAssignExpPairsSynonymPartialMatch(
    const std::vector<std::string>& infixTokens) {
  return patternManager.getAssignExpPairsSynonymPartialMatch(infixTokens);
};

std::unordered_set<std::pair<std::string, std::string>, PairHash>
PKB::getAssignExpPairsExactMatch(const std::string& var,
                                 const std::vector<std::string>& infixTokens) {
  return patternManager.getAssignExpPairsExactMatch(var, infixTokens);
};

std::unordered_set<std::pair<std::string, std::string>, PairHash>
PKB::getAssignExpPairsSynonymExactMatch(
    const std::vector<std::string>& infixTokens) {
  return patternManager.getAssignExpPairsSynonymExactMatch(infixTokens);
};

std::unordered_set<std::string> PKB::getControlVariableOfWhileStmt(int stmtNo) {
  return patternManager.getControlVariableOfWhileStmt(stmtNo);
}

std::unordered_set<int> PKB::getWhileStmtsThatUseControlVariable(
    const std::string& var) {
  return patternManager.getWhileStmtsThatUseControlVariable(var);
}

std::unordered_set<std::pair<int, std::string>, PairHash>
PKB::getAllWhileControlVariablePairs() {
  return patternManager.getAllWhileControlVariablePairs();
}

std::unordered_set<int> PKB::getAllWhileStmtsThatUseControlVariables() {
  return patternManager.getAllWhileStmtsThatUseControlVariables();
}

std::unordered_set<std::string> PKB::getAllWhileControlVariables() {
  return patternManager.getAllWhileControlVariables();
}

std::unordered_set<std::string> PKB::getControlVariableOfIfStmt(int stmtNo) {
  return patternManager.getControlVariableOfIfStmt(stmtNo);
}

std::unordered_set<int> PKB::getIfStmtsThatUseControlVariable(
    const std::string& var) {
  return patternManager.getIfStmtsThatUseControlVariable(var);
}

std::unordered_set<std::pair<int, std::string>, PairHash>
PKB::getAllIfControlVariablePairs() {
  return patternManager.getAllIfControlVariablePairs();
}

std::unordered_set<int> PKB::getAllIfStmtsThatUseControlVariables() {
  return patternManager.getAllIfStmtsThatUseControlVariables();
}

std::unordered_set<std::string> PKB::getAllIfControlVariables() {
  return patternManager.getAllIfControlVariables();
}

// Relationship Manager Methods
// parent
void PKB::insertParentStarRelationship(int parent, int child) {
  relationshipManager.insertParentStarRelationship(parent, child);
}

int PKB::getParent(int child) { return relationshipManager.getParent(child); }

std::unordered_set<int> PKB::getChildren(int parent) {
  return relationshipManager.getChildren(parent);
}

std::unordered_set<std::pair<int, int>, PairHash> PKB::getAllParentPairs() {
  return relationshipManager.getAllParentPairs();
}

std::unordered_set<std::pair<int, int>, PairHash> PKB::getAllParentStarPairs() {
  return relationshipManager.getAllParentStarPairs();
}

void PKB::insertDirectParentChildRelationship(int parentStmtNo,
                                              int childStmtNo) {
  relationshipManager.insertDirectParentChildRelationship(parentStmtNo,
                                                          childStmtNo);
}
std::unordered_set<int> PKB::getAllParents() {
  return relationshipManager.getAllParents();
}
std::unordered_set<int> PKB::getAllChildren() {
  return relationshipManager.getAllChildren();
}

std::unordered_set<int> PKB::getChildrenStar(int parent) {
  return relationshipManager.getChildrenStar(parent);
}

std::unordered_set<int> PKB::getParentsStar(int child) {
  return relationshipManager.getParentStar(child);
}

// follows
void PKB::insertDirectFollowsRelationship(int beforeStmtNo, int afterStmtNo) {
  return relationshipManager.insertDirectFollowsRelationship(beforeStmtNo,
                                                             afterStmtNo);
}

void PKB::insertFollowsStarRelationship(int beforeStmtNo, int afterStmtNo) {
  relationshipManager.insertFollowsStarRelationship(beforeStmtNo, afterStmtNo);
}

int PKB::getStmtThatFollowsAfter(int stmtNo) {
  return relationshipManager.getStmtThatFollowsAfter(stmtNo);
}

int PKB::getStmtThatFollowsBefore(int stmtNo) {
  return relationshipManager.getStmtThatFollowsBefore(stmtNo);
}

std::unordered_set<int> PKB::getAllStmtsThatFollowAfter(int stmtNo) {
  return relationshipManager.getAllStmtsThatFollowAfter(stmtNo);
}

std::unordered_set<int> PKB::getAllStmtsThatFollowBefore(int stmtNo) {
  return relationshipManager.getAllStmtsThatFollowBefore(stmtNo);
}

std::unordered_set<std::pair<int, int>, PairHash> PKB::getAllFollowPairs() {
  return relationshipManager.getAllFollowPairs();
}

std::unordered_set<std::pair<int, int>, PairHash> PKB::getAllFollowStarPairs() {
  return relationshipManager.getAllFollowStarPairs();
}

std::unordered_set<int> PKB::getAllStmtsThatFollowAfterOtherStmts() {
  return relationshipManager.getAllStmtsThatFollowAfterOtherStmts();
}
std::unordered_set<int> PKB::getAllStmtsThatFollowBeforeOtherStmts() {
  return relationshipManager.getAllStmtsThatFollowBeforeOtherStmts();
}

// calls
void PKB::insertCallsRelationship(const std::string& sourceProcName,
                                  const std::string& targetProcName) {
  relationshipManager.insertCallsRelationship(sourceProcName, targetProcName);
}

std::unordered_set<std::string> PKB::getProcsThatIsCalledBy(
    std::string& sourceProcName) {
  return relationshipManager.getProcsThatIsCalledBy(sourceProcName);
}

std::unordered_set<std::string> PKB::getProcsThatCalls(
    std::string& targetProcName) {
  return relationshipManager.getProcsThatCalls(targetProcName);
}

std::unordered_set<std::pair<std::string, std::string>, PairHash>
PKB::getAllCallPairs() {
  return relationshipManager.getAllCallPairs();
}

std::unordered_set<std::string> PKB::getAllProcsThatCallOtherProcs() {
  return relationshipManager.getAllProcsThatCallOtherProcs();
}

std::unordered_set<std::string> PKB::getAllProcsThatGetCalledByOtherProcs() {
  return relationshipManager.getAllProcsThatGetCalledByOtherProcs();
}

// calls*
std::unordered_set<std::string> PKB::getProcsThatIsCalledByStar(
    std::string& sourceProcName) {
  return relationshipManager.getProcsThatIsCalledByStar(sourceProcName);
}

std::unordered_set<std::string> PKB::getProcsThatCallsStar(
    std::string& targetProcName) {
  return relationshipManager.getProcsThatCallsStar(targetProcName);
}

std::unordered_set<std::pair<std::string, std::string>, PairHash>
PKB::getAllCallStarPairs() {
  return relationshipManager.getAllCallStarPairs();
}

// modifies
void PKB::insertModifies(int stmtNo, const std::string& str) {
  relationshipManager.insertModifies(stmtNo, str);
}
std::unordered_set<std::string> PKB::getVarsModifiedByStmt(int stmtNo) {
  return relationshipManager.getVarsModifiedByStmt(stmtNo);
}
std::unordered_set<int> PKB::getStmtsThatModifyVar(std::string var) {
  return relationshipManager.getStmtsThatModifyVar(var);
}
std::unordered_set<std::pair<int, std::string>, PairHash>
PKB::getAllVarModifiedByStmtPairs() {
  return relationshipManager.getAllVarModifiedByStmtPairs();
}
std::unordered_set<int> PKB::getAllStmtsThatModifyVars() {
  return relationshipManager.getAllStmtsThatModifyVars();
}

std::unordered_set<std::string> PKB::getAllVarsModifiedByStmts() {
  return relationshipManager.getAllVarsModifiedByStmts();
}
void PKB::insertModifiesProcedure(const std::string& str1,
                                  const std::string& str2) {
  return relationshipManager.insertModifiesProcedure(str1, str2);
}
std::unordered_set<std::string> PKB::getVarsModifiedByProcedure(
    std::string& procedure) {
  return relationshipManager.getVarsModifiedByProcedure(procedure);
}
std::unordered_set<std::string> PKB::getProceduresThatModifyVar(
    std::string& var) {
  return relationshipManager.getProceduresThatModifyVar(var);
}
std::unordered_set<std::pair<std::string, std::string>, PairHash>
PKB::getAllVarModifiedByProcedurePairs() {
  return relationshipManager.getAllVarModifiedByProcedurePairs();
}
std::unordered_set<std::string> PKB::getAllProceduresThatModifyVars() {
  return relationshipManager.getAllProceduresThatModifyVars();
}
std::unordered_set<std::string> PKB::getAllVarsModifiedByProcedures() {
  return relationshipManager.getAllVarsModifiedByProcedures();
}
// uses
void PKB::insertUses(int stmtNo, const std::string& str) {
  relationshipManager.insertUses(stmtNo, str);
}
std::unordered_set<std::string> PKB::getVarsUsedByStmt(int stmtNo) {
  return relationshipManager.getVarsUsedByStmt(stmtNo);
}
std::unordered_set<int> PKB::getStmtsThatUseVar(std::string var) {
  return relationshipManager.getStmtsThatUseVar(var);
}
std::unordered_set<std::pair<int, std::string>, PairHash>
PKB::getAllVarUsedByStmtPairs() {
  return relationshipManager.getAllVarsUsedByStmtPairs();
}
std::unordered_set<int> PKB::getAllStmtsThatUseVars() {
  return relationshipManager.getAllStmtsThatUseVars();
}
std::unordered_set<std::string> PKB::getAllVarsUsedByStmts() {
  return relationshipManager.getAllVarsUsedByStmts();
}
void PKB::insertUsesProcedure(const std::string& str1,
                              const std::string& str2) {
  relationshipManager.insertUsesProcedure(str1, str2);
}
std::unordered_set<std::string> PKB::getVarsUsedByProcedure(
    std::string procedure) {
  return relationshipManager.getVarsUsedByProcedure(procedure);
}
std::unordered_set<std::string> PKB::getProceduresThatUseVar(std::string var) {
  return relationshipManager.getProceduresThatUseVar(var);
}
std::unordered_set<std::pair<std::string, std::string>, PairHash>
PKB::getAllVarUsedByProcedurePairs() {
  return relationshipManager.getAllVarUsedByProcedurePairs();
}
std::unordered_set<std::string> PKB::getAllProceduresThatUseVars() {
  return relationshipManager.getAllProceduresThatUseVars();
}
std::unordered_set<std::string> PKB::getAllVarsUsedByProcedures() {
  return relationshipManager.getAllVarsUsedByProcedures();
}

// next
void PKB::insertNextRelationship(int previousStmtNo, int nextStmtNo) {
  return relationshipManager.insertNextRelationship(previousStmtNo, nextStmtNo);
}

std::unordered_set<int> PKB::getStmtsNextOf(int stmtNo) {
  return relationshipManager.getStmtsNextOf(stmtNo);
}

std::unordered_set<int> PKB::getStmtsPreviousOf(int stmtNo) {
  return relationshipManager.getStmtsPreviousOf(stmtNo);
}

std::unordered_set<std::pair<int, int>, PairHash> PKB::getAllNextPairs() {
  return relationshipManager.getAllNextPairs();
}

std::unordered_set<int> PKB::getAllStmtsThatAreNextOfOtherStmts() {
  return relationshipManager.getAllStmtsThatAreNextOfOtherStmts();
}

std::unordered_set<int> PKB::getAllStmtsThatArePreviousOfOtherStmts() {
  return relationshipManager.getAllStmtsThatArePreviousOfOtherStmts();
}