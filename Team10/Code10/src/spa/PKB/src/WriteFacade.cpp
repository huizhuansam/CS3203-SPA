#include "WriteFacade.h"

#include <iostream>
#include <string>
#include <vector>

// Entity Manager Methods

void WriteFacade::clearPKB() { pkb.clear(); }

void WriteFacade::addVariable(const std::string& var) { pkb.addVariable(var); };

void WriteFacade::addConstant(const std::string& constant) {
  pkb.addConstant(constant);
};

void WriteFacade::addProcedure(const std::string& proc) {
  pkb.addProcedure(proc);
};

void WriteFacade::addStatement(StatementType type, int stmtNo) {
  pkb.addStatement(type, stmtNo);
}

void WriteFacade::insertStmtCallsProc(int stmtNo, const std::string& procName) {
  pkb.insertStmtCallsProc(stmtNo, procName);
}

void WriteFacade::insertStmtPrintsVar(int stmtNo, const std::string& var) {
  pkb.insertStmtPrintsVar(stmtNo, var);
}

void WriteFacade::insertStmtReadsVar(int stmtNo, const std::string& var) {
  pkb.insertStmtReadsVar(stmtNo, var);
}

// Pattern Manager methods
void WriteFacade::addAssignExpPattern(int stmtNo, const std::string& var,
                                      const std::vector<std::string>& exp) {
  pkb.addAssignExpPattern(stmtNo, var, exp);
}

void WriteFacade::addWhileControlVariable(int stmtNo, const std::string& var) {
  pkb.addWhileControlVariable(stmtNo, var);
}
void WriteFacade::addIfControlVariable(int stmtNo, const std::string& var) {
  pkb.addIfControlVariable(stmtNo, var);
}

// Relationship Manager methods
// parent
void WriteFacade::insertDirectParentChildRelationship(int parentStmtNo,
                                                      int childStmtNo) {
  pkb.insertDirectParentChildRelationship(parentStmtNo, childStmtNo);
}
void WriteFacade::insertParentStarRelationship(int parent, int child) {
  pkb.insertParentStarRelationship(parent, child);
}

// follows
void WriteFacade::insertDirectFollowsRelationship(int beforeStmtNo,
                                                  int afterStmtNo) {
  pkb.insertDirectFollowsRelationship(beforeStmtNo, afterStmtNo);
}
void WriteFacade::insertFollowsStarRelationship(int beforeStmtNo,
                                                int afterStmtNo) {
  pkb.insertFollowsStarRelationship(beforeStmtNo, afterStmtNo);
}

//  call
void WriteFacade::insertCallsRelationship(const std::string& sourceProcName,
                                          const std::string& targetProcName) {
  pkb.insertCallsRelationship(sourceProcName, targetProcName);
}

// modifies
void WriteFacade::insertModifies(int stmtNo, const std::string& str) {
  pkb.insertModifies(stmtNo, str);
}
void WriteFacade::insertModifiesProcedure(const std::string& str1,
                                          const std::string& str2) {
  pkb.insertModifiesProcedure(str1, str2);
}

// uses
void WriteFacade::insertUsesProcedure(const std::string& str1,
                                      const std::string& str2) {
  pkb.insertUsesProcedure(str1, str2);
}
void WriteFacade::insertUses(int stmtNo, const std::string& str) {
  pkb.insertUses(stmtNo, str);
}

// next
void WriteFacade::insertNextRelationship(int previousStmtNo, int nextStmtNo) {
  return pkb.insertNextRelationship(previousStmtNo, nextStmtNo);
}