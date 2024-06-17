#include "pattern_manager/PatternManager.h"

#include <iostream>
#include <string>

void PatternManager::addAssignExpPattern(int stmtNo, const std::string& var,
                                         const std::vector<std::string>& exp) {
  assignExpPatternStore.addExp(stmtNo, var, exp);
}

void PatternManager::addWhileControlVariable(int stmtNo,
                                             const std::string& var) {
  whileExpPatternStore.insert(stmtNo, var);
}
void PatternManager::addIfControlVariable(int stmtNo, const std::string& var) {
  ifExpPatternStore.insert(stmtNo, var);
}

void PatternManager::clear() {
  assignExpPatternStore.clear();
  whileExpPatternStore.clear();
  ifExpPatternStore.clear();
}

std::unordered_set<std::pair<std::string, std::string>, PairHash>
PatternManager::getAllAssignExpPairs() {
  return assignExpPatternStore.getAllExpPairs();
};

std::unordered_set<std::pair<std::string, std::string>, PairHash>
PatternManager::getAssignExpPairsPartialMatch(
    const std::string& var, const std::vector<std::string>& infixTokens) {
  return assignExpPatternStore.getExpPairsPartialMatch(var, infixTokens);
};

std::unordered_set<std::pair<std::string, std::string>, PairHash>
PatternManager::getAssignExpPairsSynonymPartialMatch(
    const std::vector<std::string>& infixTokens) {
  return assignExpPatternStore.getExpPairsSynonymPartialMatch(infixTokens);
};

std::unordered_set<std::pair<std::string, std::string>, PairHash>
PatternManager::getAssignExpPairsExactMatch(
    const std::string& var, const std::vector<std::string>& infixTokens) {
  return assignExpPatternStore.getExpPairsExactMatch(var, infixTokens);
};

std::unordered_set<std::pair<std::string, std::string>, PairHash>
PatternManager::getAssignExpPairsSynonymExactMatch(
    const std::vector<std::string>& infixTokens) {
  return assignExpPatternStore.getExpPairsSynonymExactMatch(infixTokens);
};

std::unordered_set<std::string> PatternManager::getControlVariableOfWhileStmt(
    int stmtNo) {
  return whileExpPatternStore.getLeftToRight(stmtNo);
}

std::unordered_set<int> PatternManager::getWhileStmtsThatUseControlVariable(
    const std::string& var) {
  return whileExpPatternStore.getRightToLeft(var);
}

std::unordered_set<std::pair<int, std::string>, PairHash>
PatternManager::getAllWhileControlVariablePairs() {
  return whileExpPatternStore.getAllPairs();
}

std::unordered_set<int>
PatternManager::getAllWhileStmtsThatUseControlVariables() {
  return whileExpPatternStore.getAllLefts();
}

std::unordered_set<std::string> PatternManager::getAllWhileControlVariables() {
  return whileExpPatternStore.getAllRights();
}

std::unordered_set<std::string> PatternManager::getControlVariableOfIfStmt(
    int stmtNo) {
  return ifExpPatternStore.getLeftToRight(stmtNo);
}

std::unordered_set<int> PatternManager::getIfStmtsThatUseControlVariable(
    const std::string& var) {
  return ifExpPatternStore.getRightToLeft(var);
}

std::unordered_set<std::pair<int, std::string>, PairHash>
PatternManager::getAllIfControlVariablePairs() {
  return ifExpPatternStore.getAllPairs();
}

std::unordered_set<int> PatternManager::getAllIfStmtsThatUseControlVariables() {
  return ifExpPatternStore.getAllLefts();
}

std::unordered_set<std::string> PatternManager::getAllIfControlVariables() {
  return ifExpPatternStore.getAllRights();
}