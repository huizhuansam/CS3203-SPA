#include "WhileExtractor.h"

#include "CondExprExtractor.h"
#include "ContainerStmtExtractor.h"
#include "DesignExtractor.h"
#include "GrammarRule.h"
#include "StmtLstExtractor.h"
#include "WriteFacade.h"

namespace SP {
WhileExtractor::WhileExtractor(WriteFacade& writer)
    : ContainerStmtExtractor(writer) {}

void WhileExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  this->thisStmtNo = DesignExtractor::getStmtNumber();  // for next relationship

  // consume 'while', '('
  it += 2;

  this->consumeCondition(it, end);

  // consume ')', '{'
  it += 2;

  this->consumeStmtList(it, end);

  // consume '}'
  it++;
}

std::unordered_set<int> WhileExtractor::getLastExecutedStmtNumbers() {
  // returns back to the start of the while statement
  return {this->thisStmtNo};
}

void WhileExtractor::consumeCondition(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  // extract conditional expression
  CondExprExtractor condExprExtractor(this->writer);
  condExprExtractor.extract(it, end);

  // add variable used + control variable for while condition
  for (auto& var : condExprExtractor.getVarUsed()) {
    this->addVarUsed(var);
    this->writer.addWhileControlVariable(thisStmtNo, var);
  }
}

void WhileExtractor::consumeStmtList(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  // extract statement list
  StmtLstExtractor stmtLstExtractor(this->writer, thisStmtNo);
  stmtLstExtractor.extract(it, end);

  // add variables used, modified and procedures called in the statement list
  this->addAllVarUsedToThisStmt(stmtLstExtractor);
  this->addAllVarModifiedToThisStmt(stmtLstExtractor);
  this->addAllProcCalledToThisStmt(stmtLstExtractor);

  // add statement call map
  this->setStmtCallMap(stmtLstExtractor.getStmtCallMap());

  // insert parent-child relationship to PKB
  this->writeParentChildRelationship(stmtLstExtractor);

  // insert variables used and modified by this while statement to PKB
  this->writeAllVarUsed(thisStmtNo);
  this->writeAllVarModified(thisStmtNo);

  // insert next relationship from last statement in the while statement list to
  // the while statement
  this->writeNextRelationshipToThisStmt(stmtLstExtractor);
}

void WhileExtractor::writeParentChildRelationship(
    StmtLstExtractor& stmtListExtractor) {
  // insert parent-child relationship to PKB
  for (auto& stmtNo : stmtListExtractor.getNonNestedStmtNo()) {
    this->writer.insertDirectParentChildRelationship(thisStmtNo, stmtNo);
  }

  for (int stmtNo = stmtListExtractor.getFirstStmtNo();
       stmtNo <= stmtListExtractor.getLastStmtNo(); stmtNo++) {
    this->writer.insertParentStarRelationship(thisStmtNo, stmtNo);
  }
}

void WhileExtractor::writeNextRelationshipToThisStmt(
    StmtLstExtractor& stmtListExtractor) {
  for (auto& lastStmtNo : stmtListExtractor.getLastExecutedStmtNumbers()) {
    this->writer.insertNextRelationship(lastStmtNo, thisStmtNo);
  }
}
}  // namespace SP
