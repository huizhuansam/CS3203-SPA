#include "IfExtractor.h"

#include "CondExprExtractor.h"
#include "ContainerStmtExtractor.h"
#include "DesignExtractor.h"
#include "GrammarRule.h"
#include "StmtLstExtractor.h"
#include "WriteFacade.h"

namespace SP {
IfExtractor::IfExtractor(WriteFacade& writer)
    : ContainerStmtExtractor(writer) {}

void IfExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  int currentStmtNo = DesignExtractor::getStmtNumber();

  // consume 'if', '('
  it += 2;
  this->consumeCondition(it, end);
  // consume ')', 'then', '{'
  it += 3;
  StmtLstExtractor trueBranchStmtLstExtractor{this->writer, currentStmtNo};
  this->consumeTrueBranch(it, end, currentStmtNo, trueBranchStmtLstExtractor);
  // consume '}', 'else', '{'
  it += 3;
  StmtLstExtractor falseBranchStmtLstExtractor{this->writer, currentStmtNo};
  this->consumeFalseBranch(it, end, currentStmtNo, falseBranchStmtLstExtractor);
  // consume '}'
  it++;

  // insert variables used and modified by this if statement to PKB
  this->writeAllVarUsed(currentStmtNo);
  this->writeAllVarModified(currentStmtNo);
}

std::unordered_set<int> IfExtractor::getLastExecutedStmtNumbers() {
  std::unordered_set<int> lastExecutedStmtNumbers;
  lastExecutedStmtNumbers.insert(
      this->trueBranchLastExecutedStmtNumbers.begin(),
      this->trueBranchLastExecutedStmtNumbers.end());
  lastExecutedStmtNumbers.insert(
      this->falseBranchLastExecutedStmtNumbers.begin(),
      this->falseBranchLastExecutedStmtNumbers.end());
  return lastExecutedStmtNumbers;
}

void IfExtractor::consumeCondition(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  CondExprExtractor conditionalExtractor{this->writer};
  conditionalExtractor.extract(it, end);

  // add variable used + control variable for if condition
  for (auto& var : conditionalExtractor.getVarUsed()) {
    this->addVarUsed(var);
    this->writer.addIfControlVariable(DesignExtractor::getStmtNumber(), var);
  }
}

void IfExtractor::consumeTrueBranch(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end, int currentStmtNo,
    StmtLstExtractor& stmtListExtractor) {
  stmtListExtractor.extract(it, end);
  // for next relationship
  this->trueBranchLastExecutedStmtNumbers =
      stmtListExtractor.getLastExecutedStmtNumbers();
  this->consumeEntities(stmtListExtractor, currentStmtNo);
  this->setStmtCallMap(stmtListExtractor.getStmtCallMap());
}

void IfExtractor::consumeFalseBranch(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end, int currentStmtNo,
    StmtLstExtractor& stmtListExtractor) {
  stmtListExtractor.extract(it, end);
  // for next relationship
  this->falseBranchLastExecutedStmtNumbers =
      stmtListExtractor.getLastExecutedStmtNumbers();
  this->consumeEntities(stmtListExtractor, currentStmtNo);
  this->appendToStmtCallMap(stmtListExtractor.getStmtCallMap());
}

void IfExtractor::writeParentChildRelationship(
    StmtLstExtractor& stmtListExtractor, int currentStmtNo) {
  // insert parent-child relationship to PKB
  for (auto& stmtNo : stmtListExtractor.getNonNestedStmtNo()) {
    this->writer.insertDirectParentChildRelationship(currentStmtNo, stmtNo);
  }

  // insert parent*-child relationship to PKB
  for (int stmtNo = stmtListExtractor.getFirstStmtNo();
       stmtNo <= stmtListExtractor.getLastStmtNo(); stmtNo++) {
    this->writer.insertParentStarRelationship(currentStmtNo, stmtNo);
  }
}

void IfExtractor::consumeEntities(StmtLstExtractor& stmtListExtractor,
                                  int currentStmtNo) {
  // add variables used, modified and procedures called in the branch
  this->addAllVarUsedToThisStmt(stmtListExtractor);
  this->addAllVarModifiedToThisStmt(stmtListExtractor);
  this->addAllProcCalledToThisStmt(stmtListExtractor);
  this->writeParentChildRelationship(stmtListExtractor, currentStmtNo);
}
}  // namespace SP
