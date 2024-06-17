#include "ReadExtractor.h"

#include "DesignExtractor.h"
#include "GrammarRule.h"
#include "IStmtExtractor.h"
#include "VariableExtractor.h"
#include "WriteFacade.h"

namespace SP {
ReadExtractor::ReadExtractor(WriteFacade& writer) : writer(writer) {}

void ReadExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  // consume 'read'
  it++;

  const auto& variableRead = (*it)->getValue();

  int currentStmtNo = DesignExtractor::getStmtNumber();
  VariableExtractor variableExtractor(this->writer);
  variableExtractor.extract(it, end);

  // consume ';'
  it++;

  // insert modifies relationship
  this->writer.insertModifies(currentStmtNo, variableRead);

  // insert to varModified
  this->varModified.insert(variableRead);

  // insert to stmt number that reads the variable
  this->writer.insertStmtReadsVar(currentStmtNo, variableRead);
}

void ReadExtractor::dumpContentsInto(StmtLstExtractor& stmtListExtractor,
                                     [[maybe_unused]] int currentStmtNo) {
  stmtListExtractor.addVarModifiedByStmt(this->varModified);
}

}  // namespace SP
