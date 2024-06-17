#include "ProcedureExtractor.h"

#include "StmtLstExtractor.h"
#include "WriteFacade.h"

namespace SP {
ProcedureExtractor::ProcedureExtractor(WriteFacade& writer) : writer(writer){};

void ProcedureExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  // consume 'procedure'
  it++;
  std::string procedureName = (*it)->getValue();
  this->nameOfProcedureExtracted = procedureName;
  this->writer.addProcedure(procedureName);

  // consume procedeure name
  it++;

  // consume '{'
  it++;

  StmtLstExtractor statementListExtractor{this->writer};
  statementListExtractor.extract(it, end);
  this->stmtCallMap = statementListExtractor.getStmtCallMap();

  // consume '}'
  it++;

  // insert uses relationship
  for (const auto& var : statementListExtractor.getVarUsed()) {
    this->varUsed.insert(var);
    this->writer.insertUsesProcedure(procedureName, var);
  }

  // insert modifies relationship
  for (const auto& var : statementListExtractor.getVarModified()) {
    this->varModified.insert(var);
    this->writer.insertModifiesProcedure(procedureName, var);
  }

  // insert calls relationship
  for (const auto& proc : statementListExtractor.getProcCalled()) {
    this->procCalled.insert(proc);
    this->writer.insertCallsRelationship(procedureName, proc);
  }
}

std::string ProcedureExtractor::getNameOfProcedureExtracted() {
  return this->nameOfProcedureExtracted;
}

std::unordered_set<std::string>& ProcedureExtractor::getVarUsed() {
  return this->varUsed;
}

std::unordered_set<std::string>& ProcedureExtractor::getVarModified() {
  return this->varModified;
}

std::unordered_set<std::string>& ProcedureExtractor::getProcCalled() {
  return this->procCalled;
}

std::unordered_map<int, std::unordered_set<std::string>>&
ProcedureExtractor::getStmtCallMap() {
  return this->stmtCallMap;
}
}  // namespace SP
