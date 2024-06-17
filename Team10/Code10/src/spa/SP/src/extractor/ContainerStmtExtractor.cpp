#include "ContainerStmtExtractor.h"

#include "DesignExtractor.h"

namespace SP {
ContainerStmtExtractor::ContainerStmtExtractor(WriteFacade& writer)
    : writer(writer) {}

void ContainerStmtExtractor::addAllVarUsedToThisStmt(
    StmtLstExtractor& stmtListExtractor) {
  for (auto& var : stmtListExtractor.getVarUsed()) {
    this->varUsed.insert(var);
  }
}

void ContainerStmtExtractor::addAllVarModifiedToThisStmt(
    StmtLstExtractor& stmtListExtractor) {
  for (auto& var : stmtListExtractor.getVarModified()) {
    this->varModified.insert(var);
  }
}

void ContainerStmtExtractor::addAllProcCalledToThisStmt(
    StmtLstExtractor& stmtListExtractor) {
  for (auto& proc : stmtListExtractor.getProcCalled()) {
    this->addProcCalled(proc);
  }
}

void ContainerStmtExtractor::writeAllVarUsed(int currentStmtNo) {
  for (auto& var : this->varUsed) {
    this->writer.insertUses(currentStmtNo, var);
  }
}

void ContainerStmtExtractor::writeAllVarModified(int currentStmtNo) {
  for (auto& var : this->varModified) {
    this->writer.insertModifies(currentStmtNo, var);
  }
}

std::unordered_map<int, std::unordered_set<std::string>>&
ContainerStmtExtractor::getStmtCallMap() {
  return this->stmtCallMap;
}

void ContainerStmtExtractor::setStmtCallMap(
    std::unordered_map<int, std::unordered_set<std::string>>& map) {
  this->stmtCallMap = map;
}

void ContainerStmtExtractor::appendToStmtCallMap(
    std::unordered_map<int, std::unordered_set<std::string>>& map) {
  for (const auto& [stmtNo, procs] : map) {
    this->stmtCallMap[stmtNo].insert(procs.begin(), procs.end());
  }
}

void ContainerStmtExtractor::addVarUsed(const std::string& var) {
  this->varUsed.insert(var);
}

void ContainerStmtExtractor::addProcCalled(const std::string& proc) {
  this->procCalled.insert(proc);
}

void ContainerStmtExtractor::dumpContentsInto(
    StmtLstExtractor& stmtListExtractor, int currentStmtNo) {
  stmtListExtractor.appendToStmtCallMap(this->getStmtCallMap());
  stmtListExtractor.addVarUsedByStmt(this->varUsed);
  stmtListExtractor.addVarModifiedByStmt(this->varModified);
  stmtListExtractor.addProcCalledByStmt(this->procCalled);
  stmtListExtractor.addToStmtCallMap(currentStmtNo, this->procCalled);
}
}  // namespace SP
