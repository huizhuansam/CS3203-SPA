#include "entity_manager/EntityManager.h"

#include <iostream>
#include <string>

void EntityManager::addVariable(const std::string& var) {
  varStore.insert(var);
}

void EntityManager::addConstant(const std::string& constant) {
  constStore.insert(constant);
}

void EntityManager::addProcedure(const std::string& proc) {
  procStore.insert(proc);
}

void EntityManager::addStatement(StatementType type, int stmtNo) {
  stmtStore.addStatement(type, stmtNo);
}

void EntityManager::insertStmtCallsProc(int stmtNo,
                                        const std::string& procName) {
  callsProcStore.insert(stmtNo, procName);
}

void EntityManager::insertStmtPrintsVar(int stmtNo, const std::string& var) {
  printsVarStore.insert(stmtNo, var);
}

void EntityManager::insertStmtReadsVar(int stmtNo, const std::string& var) {
  readsVarStore.insert(stmtNo, var);
}

void EntityManager::clear() {
  varStore.clear();
  constStore.clear();
  procStore.clear();
  stmtStore.clear();
  callsProcStore.clear();
  printsVarStore.clear();
  readsVarStore.clear();
}

std::unordered_set<std::string> EntityManager::getAllVariables() {
  return varStore.getAll();
};

std::unordered_set<std::string> EntityManager::getAllConstants() {
  return constStore.getAll();
};

std::unordered_set<std::string> EntityManager::getAllProcedures() {
  return procStore.getAll();
};

std::unordered_set<int> EntityManager::getStatements() {
  return stmtStore.getStatements();
};

std::unordered_set<int> EntityManager::getAssigns() {
  return stmtStore.getAssigns();
};

std::unordered_set<int> EntityManager::getReads() {
  return stmtStore.getReads();
};

std::unordered_set<int> EntityManager::getPrints() {
  return stmtStore.getPrints();
};

std::unordered_set<int> EntityManager::getCalls() {
  return stmtStore.getCalls();
};

std::unordered_set<int> EntityManager::getWhiles() {
  return stmtStore.getWhiles();
};

std::unordered_set<int> EntityManager::getIfs() { return stmtStore.getIfs(); };

std::string EntityManager::getProcCalledByStmt(int callStmt) {
  return getStringFromSet(callsProcStore.getLeftToRight(callStmt));
}

std::unordered_set<int> EntityManager::getAllStmtsThatCallProc(
    std::string& procName) {
  return callsProcStore.getRightToLeft(procName);
}

std::unordered_set<std::pair<int, std::string>, PairHash>
EntityManager::getAllCallsProcPairs() {
  return callsProcStore.getAllPairs();
}

std::unordered_set<std::string> EntityManager::getAllProceduresCalledByStmts() {
  return callsProcStore.getAllRights();
}

std::string EntityManager::getVarPrintedByStmt(int printStmt) {
  return getStringFromSet(printsVarStore.getLeftToRight(printStmt));
}

std::unordered_set<int> EntityManager::getAllStmtsThatPrintVar(
    std::string& var) {
  return printsVarStore.getRightToLeft(var);
}

std::unordered_set<std::pair<int, std::string>, PairHash>
EntityManager::getAllPrintVarPairs() {
  return printsVarStore.getAllPairs();
}

std::unordered_set<std::string> EntityManager::getAllVarsPrintByStmts() {
  return printsVarStore.getAllRights();
}

std::string EntityManager::getVarReadByStmt(int readStmt) {
  return getStringFromSet(readsVarStore.getLeftToRight(readStmt));
}

std::unordered_set<int> EntityManager::getAllStmtsThatReadVar(
    std::string& var) {
  return readsVarStore.getRightToLeft(var);
}
std::unordered_set<std::pair<int, std::string>, PairHash>
EntityManager::getAllReadVarPairs() {
  return readsVarStore.getAllPairs();
}
std::unordered_set<std::string> EntityManager::getAllVarsReadByStmts() {
  return readsVarStore.getAllRights();
}
