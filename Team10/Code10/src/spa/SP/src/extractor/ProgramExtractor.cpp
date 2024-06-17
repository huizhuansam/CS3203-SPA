#include "ProgramExtractor.h"

#include "ProcedureExtractor.h"
#include "WriteFacade.h"

namespace SP {
ProgramExtractor::ProgramExtractor(WriteFacade& writer) : writer(writer){};

void ProgramExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  while (it < end) {
    ProcedureExtractor procedureExtractor{this->writer};
    procedureExtractor.extract(it, end);
    // store the procedure name and its corresponding set of procedures called,
    // variables used and variables modified
    std::string procName = procedureExtractor.getNameOfProcedureExtracted();
    procCallMap[procName] = procedureExtractor.getProcCalled();
    procVarUsedMap[procName] = procedureExtractor.getVarUsed();
    procVarModifiedMap[procName] = procedureExtractor.getVarModified();

    // store the  number and its corresponding set of procedures called
    auto stmtCallMapFromProc = procedureExtractor.getStmtCallMap();
    for (const auto& stmt : stmtCallMapFromProc) {
      stmtCallMap[stmt.first].insert(stmt.second.begin(), stmt.second.end());
    }
  }

  // get all the variables modified and used by the procedures
  for (const auto& proc : procCallMap) {
    getAllVarModifiedByProc(proc.first);
    getAllVarUsedByProc(proc.first);
  }

  // insert all the variables modified by the procedures into PKB
  for (const auto& proc : procVarModifiedMap) {
    for (const auto& var : proc.second) {
      writer.insertModifiesProcedure(proc.first, var);
    }
  }

  // insert all the variables used by the procedures into PKB
  for (const auto& proc : procVarUsedMap) {
    for (const auto& var : proc.second) {
      writer.insertUsesProcedure(proc.first, var);
    }
  }

  // insert all the variables modified through call into PKB
  for (const auto& stmt : stmtCallMap) {
    for (const auto& proc : stmt.second) {
      for (const auto& var : procVarModifiedMap[proc]) {
        writer.insertModifies(stmt.first, var);
      }
    }
  }

  // insert all the variables used through call into PKB
  for (const auto& stmt : stmtCallMap) {
    for (const auto& proc : stmt.second) {
      for (const auto& var : procVarUsedMap[proc]) {
        writer.insertUses(stmt.first, var);
      }
    }
  }
}

std::unordered_set<std::string> ProgramExtractor::getAllVarModifiedByProc(
    const std::string& procName) {
  if (procModifiesMemo.find(procName) != procModifiesMemo.end()) {
    return procModifiesMemo[procName];
  }

  std::unordered_set<std::string> calledProcs = procCallMap[procName];

  // If this procedure does not call any other procedures,
  // return the set of variables modified by this procedure (skip for loop
  // below) Otherwise, get all the variables modified by the called procedures
  // then, insert them into the set of variables modified by this procedure
  for (const auto& calledProc : calledProcs) {
    std::unordered_set<std::string> calledProcVarModified =
        getAllVarModifiedByProc(calledProc);
    procVarModifiedMap[procName].insert(calledProcVarModified.begin(),
                                        calledProcVarModified.end());
  }

  procModifiesMemo[procName] = procVarModifiedMap[procName];
  return procVarModifiedMap[procName];
}

std::unordered_set<std::string> ProgramExtractor::getAllVarUsedByProc(
    const std::string& procName) {
  if (procUsesMemo.find(procName) != procUsesMemo.end()) {
    return procUsesMemo[procName];
  }

  std::unordered_set<std::string> calledProcs = procCallMap[procName];

  // If this procedure does not call any other procedures,
  // return the set of variables used by this procedure (skip for loop
  // below) Otherwise, get all the variables used by the called procedures
  // then, insert them into the set of variables used by this procedure
  for (const auto& calledProc : calledProcs) {
    std::unordered_set<std::string> calledProcVarUsed =
        getAllVarUsedByProc(calledProc);
    procVarUsedMap[procName].insert(calledProcVarUsed.begin(),
                                    calledProcVarUsed.end());
  }

  procUsesMemo[procName] = procVarUsedMap[procName];
  return procVarUsedMap[procName];
}
}  // namespace SP
