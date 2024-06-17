#include "RelationshipManager.h"

#include <algorithm>
#include <vector>

// parent
void RelationshipManager::insertDirectParentChildRelationship(int parentStmtNo,
                                                              int childStmtNo) {
  parentStore.insert(parentStmtNo, childStmtNo);
}

std::unordered_set<int> RelationshipManager::getChildren(int parent) {
  return parentStore.getLeftToRight(parent);
}

int RelationshipManager::getParent(int child) {
  std::unordered_set<int> childSet = parentStore.getRightToLeft(child);
  return getIntFromSet(childSet);
}

std::unordered_set<std::pair<int, int>, PairHash>
RelationshipManager::getAllParentPairs() {
  return parentStore.getAllPairs();
}

std::unordered_set<int> RelationshipManager::getAllParents() {
  return parentStore.getAllLefts();
}

std::unordered_set<int> RelationshipManager::getAllChildren() {
  return parentStore.getAllRights();
}

// parent*

void RelationshipManager::insertParentStarRelationship(int parent, int child) {
  parentStarStore.insert(parent, child);
}

std::unordered_set<int> RelationshipManager::getChildrenStar(int parent) {
  return parentStarStore.getLeftToRight(parent);
}

std::unordered_set<int> RelationshipManager::getParentStar(int child) {
  return parentStarStore.getRightToLeft(child);
}

std::unordered_set<std::pair<int, int>, PairHash>
RelationshipManager::getAllParentStarPairs() {
  return parentStarStore.getAllPairs();
}

// follows
void RelationshipManager::insertDirectFollowsRelationship(int beforeStmtNo,
                                                          int afterStmtNo) {
  followsStore.insert(beforeStmtNo, afterStmtNo);
}

int RelationshipManager::getStmtThatFollowsAfter(int stmtNo) {
  std::unordered_set<int> set = followsStore.getLeftToRight(stmtNo);
  return getIntFromSet(set);
}

int RelationshipManager::getStmtThatFollowsBefore(int stmtNo) {
  std::unordered_set<int> set = followsStore.getRightToLeft(stmtNo);
  return getIntFromSet(set);
}

std::unordered_set<std::pair<int, int>, PairHash>
RelationshipManager::getAllFollowPairs() {
  return followsStore.getAllPairs();
}

// follows*

void RelationshipManager::insertFollowsStarRelationship(int beforeStmtNo,
                                                        int afterStmtNo) {
  followsStarStore.insert(beforeStmtNo, afterStmtNo);
}

std::unordered_set<int> RelationshipManager::getAllStmtsThatFollowAfter(
    int stmtNo) {
  return followsStarStore.getLeftToRight(stmtNo);
}

std::unordered_set<int> RelationshipManager::getAllStmtsThatFollowBefore(
    int stmtNo) {
  return followsStarStore.getRightToLeft(stmtNo);
}

std::unordered_set<std::pair<int, int>, PairHash>
RelationshipManager::getAllFollowStarPairs() {
  return followsStarStore.getAllPairs();
}

std::unordered_set<int>
RelationshipManager::getAllStmtsThatFollowBeforeOtherStmts() {
  return followsStarStore.getAllLefts();
}

std::unordered_set<int>
RelationshipManager::getAllStmtsThatFollowAfterOtherStmts() {
  return followsStarStore.getAllRights();
}

// calls
void RelationshipManager::insertCallsRelationship(
    const std::string& sourceProcName, const std::string& targetProcName) {
  callStore.insert(sourceProcName, targetProcName);
  callStarStore.insert(sourceProcName, targetProcName);
}

std::unordered_set<std::string> RelationshipManager::getProcsThatIsCalledBy(
    std::string& sourceProcName) {
  return callStore.getLeftToRight(sourceProcName);
}

std::unordered_set<std::string> RelationshipManager::getProcsThatCalls(
    std::string& targetProcName) {
  return callStore.getRightToLeft(targetProcName);
}

std::unordered_set<std::pair<std::string, std::string>, PairHash>
RelationshipManager::getAllCallPairs() {
  return callStore.getAllPairs();
}

std::unordered_set<std::string>
RelationshipManager::getAllProcsThatCallOtherProcs() {
  return callStore.getAllLefts();
}

std::unordered_set<std::string>
RelationshipManager::getAllProcsThatGetCalledByOtherProcs() {
  return callStore.getAllRights();
}

// calls*
std::unordered_set<std::string> RelationshipManager::getProcsThatIsCalledByStar(
    std::string& sourceProcName) {
  return callStarStore.getLeftToRight(sourceProcName);
}

std::unordered_set<std::string> RelationshipManager::getProcsThatCallsStar(
    std::string& targetProcName) {
  return callStarStore.getRightToLeft(targetProcName);
}

std::unordered_set<std::pair<std::string, std::string>, PairHash>
RelationshipManager::getAllCallStarPairs() {
  return callStarStore.getAllPairs();
}

// modifies
void RelationshipManager::insertModifies(int stmtNo, const std::string& str) {
  modifiesStore.insert(stmtNo, str);
}

std::unordered_set<std::string> RelationshipManager::getVarsModifiedByStmt(
    int stmtNo) {
  return modifiesStore.getLeftToRight(stmtNo);
}

std::unordered_set<int> RelationshipManager::getStmtsThatModifyVar(
    std::string var) {
  return modifiesStore.getRightToLeft(var);
}

std::unordered_set<std::pair<int, std::string>, PairHash>
RelationshipManager::getAllVarModifiedByStmtPairs() {
  return modifiesStore.getAllPairs();
}

std::unordered_set<int> RelationshipManager::getAllStmtsThatModifyVars() {
  return modifiesStore.getAllLefts();
}

std::unordered_set<std::string>
RelationshipManager::getAllVarsModifiedByStmts() {
  return modifiesStore.getAllRights();
}

void RelationshipManager::insertModifiesProcedure(const std::string& str1,
                                                  const std::string& str2) {
  return modifiesProcedureStore.insert(str1, str2);
}

std::unordered_set<std::string> RelationshipManager::getVarsModifiedByProcedure(
    std::string& procedure) {
  return modifiesProcedureStore.getLeftToRight(procedure);
}

std::unordered_set<std::string> RelationshipManager::getProceduresThatModifyVar(
    std::string& var) {
  return modifiesProcedureStore.getRightToLeft(var);
}

std::unordered_set<std::pair<std::string, std::string>, PairHash>
RelationshipManager::getAllVarModifiedByProcedurePairs() {
  return modifiesProcedureStore.getAllPairs();
}

std::unordered_set<std::string>
RelationshipManager::getAllProceduresThatModifyVars() {
  return modifiesProcedureStore.getAllLefts();
}

std::unordered_set<std::string>
RelationshipManager::getAllVarsModifiedByProcedures() {
  return modifiesProcedureStore.getAllRights();
}

// uses
void RelationshipManager::insertUses(int stmtNo, const std::string& str) {
  usesStore.insert(stmtNo, str);
}
std::unordered_set<std::string> RelationshipManager::getVarsUsedByStmt(
    int stmtNo) {
  return usesStore.getLeftToRight(stmtNo);
}
std::unordered_set<int> RelationshipManager::getStmtsThatUseVar(
    std::string var) {
  return usesStore.getRightToLeft(var);
}
std::unordered_set<std::pair<int, std::string>, PairHash>
RelationshipManager::getAllVarsUsedByStmtPairs() {
  return usesStore.getAllPairs();
}

std::unordered_set<int> RelationshipManager::getAllStmtsThatUseVars() {
  return usesStore.getAllLefts();
}

std::unordered_set<std::string> RelationshipManager::getAllVarsUsedByStmts() {
  return usesStore.getAllRights();
}

void RelationshipManager::insertUsesProcedure(const std::string& str1,
                                              const std::string& str2) {
  usesProcedureStore.insert(str1, str2);
}
std::unordered_set<std::string> RelationshipManager::getVarsUsedByProcedure(
    std::string procedure) {
  return usesProcedureStore.getLeftToRight(procedure);
}
std::unordered_set<std::string> RelationshipManager::getProceduresThatUseVar(
    std::string var) {
  return usesProcedureStore.getRightToLeft(var);
}
std::unordered_set<std::pair<std::string, std::string>, PairHash>
RelationshipManager::getAllVarUsedByProcedurePairs() {
  return usesProcedureStore.getAllPairs();
}

std::unordered_set<std::string>
RelationshipManager::getAllProceduresThatUseVars() {
  return usesProcedureStore.getAllLefts();
}

std::unordered_set<std::string>
RelationshipManager::getAllVarsUsedByProcedures() {
  return usesProcedureStore.getAllRights();
}

void RelationshipManager::insertNextRelationship(int previousStmtNo,
                                                 int nextStmtNo) {
  return nextStore.insert(previousStmtNo, nextStmtNo);
}

std::unordered_set<int> RelationshipManager::getStmtsNextOf(int stmtNo) {
  return nextStore.getLeftToRight(stmtNo);
}

std::unordered_set<int> RelationshipManager::getStmtsPreviousOf(int stmtNo) {
  return nextStore.getRightToLeft(stmtNo);
}

std::unordered_set<std::pair<int, int>, PairHash>
RelationshipManager::getAllNextPairs() {
  return nextStore.getAllPairs();
}

std::unordered_set<int>
RelationshipManager::getAllStmtsThatAreNextOfOtherStmts() {
  return nextStore.getAllRights();
}

std::unordered_set<int>
RelationshipManager::getAllStmtsThatArePreviousOfOtherStmts() {
  return nextStore.getAllLefts();
}

void RelationshipManager::clear() {
  modifiesStore.clear();
  usesStore.clear();
  usesProcedureStore.clear();
  modifiesProcedureStore.clear();
  followsStore.clear();
  parentStore.clear();
  callStore.clear();
  followsStarStore.clear();
  parentStarStore.clear();
  callStarStore.clear();
  nextStore.clear();
}