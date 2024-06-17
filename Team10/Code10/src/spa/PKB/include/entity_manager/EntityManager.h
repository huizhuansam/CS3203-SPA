#pragma once

#include <iostream>
#include <string>

#include "EntitySetStore.h"
#include "StatementStore.h"
#include "TwoWayMapManager.h"

class EntityManager {
 private:
  EntitySetStore<std::string> varStore;
  EntitySetStore<std::string> constStore;
  EntitySetStore<std::string> procStore;
  StatementStore stmtStore;
  TwoWayMapManager<int, std::string> callsProcStore;
  TwoWayMapManager<int, std::string> printsVarStore;
  TwoWayMapManager<int, std::string> readsVarStore;

 public:
  // WriteFacade Methods
  void addVariable(const std::string& var);
  void addConstant(const std::string& constant);
  void addProcedure(const std::string& proc);
  void addStatement(StatementType type, int stmtNo);

  void insertStmtCallsProc(int stmtNo, const std::string& procName);
  void insertStmtPrintsVar(int stmtNo, const std::string& var);
  void insertStmtReadsVar(int stmtNo, const std::string& var);

  void clear();

  // ReadFacade Methods
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
};
