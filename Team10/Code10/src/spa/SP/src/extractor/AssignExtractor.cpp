#include "AssignExtractor.h"

#include "DesignExtractor.h"
#include "ExprExtractor.h"
#include "GrammarRule.h"
#include "IStmtExtractor.h"
#include "VariableExtractor.h"
#include "WriteFacade.h"

namespace SP {
AssignExtractor::AssignExtractor(WriteFacade& writer) : writer(writer) {}

void AssignExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  this->extractVarName(it, end);

  // consume '='
  it++;

  this->extractExpression(it, end);
}

void AssignExtractor::extractVarName(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  this->varModifiedName = (*it)->getValue();

  // insert modifies
  this->processModifies(varModifiedName);

  // consume variable
  VariableExtractor variableExtractor{this->writer};
  variableExtractor.extract(it, end);
};

void AssignExtractor::extractExpression(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  // consume expression
  auto exprStart = it;
  ExprExtractor exprExtractor{this->writer};
  exprExtractor.extract(it, end);
  auto exprEnd = it;

  // consume ';'
  it++;

  // insert uses
  this->processUsesAndPattern(exprStart, exprEnd);
}

void AssignExtractor::processModifies(const std::string& varName) {
  int currentStmtNo = DesignExtractor::getStmtNumber();
  this->writer.insertModifies(currentStmtNo, varName);
  this->varModified.insert(varName);
}

void AssignExtractor::processUsesAndPattern(
    std::vector<std::unique_ptr<Token>>::iterator& exprStart,
    std::vector<std::unique_ptr<Token>>::iterator& exprEnd) {
  std::vector<std::string> expr;

  while (exprStart != exprEnd) {
    auto& token = *exprStart;
    expr.push_back(token->getValue());

    if (token->canBeName()) {
      int currentStmtNo = DesignExtractor::getStmtNumber();
      this->writer.insertUses(currentStmtNo, token->getValue());
      this->varUsed.insert(token->getValue());
    }

    exprStart++;
  }

  // insert pattern
  this->writeAssignExprPattern(varModifiedName, expr);
}

void AssignExtractor::writeAssignExprPattern(
    const std::string& var, const std::vector<std::string>& expr) {
  int currentStmtNo = DesignExtractor::getStmtNumber();
  this->writer.addAssignExpPattern(currentStmtNo, var, expr);
}

void AssignExtractor::dumpContentsInto(StmtLstExtractor& stmtListExtractor,
                                       [[maybe_unused]] int currentStmtNo) {
  stmtListExtractor.addVarUsedByStmt(this->varUsed);
  stmtListExtractor.addVarModifiedByStmt(this->varModified);
}
}  // namespace SP
