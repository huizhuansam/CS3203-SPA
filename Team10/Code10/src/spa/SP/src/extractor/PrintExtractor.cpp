#include "PrintExtractor.h"

#include <vector>

#include "DesignExtractor.h"
#include "IStmtExtractor.h"
#include "VariableExtractor.h"
#include "WriteFacade.h"

namespace SP {
PrintExtractor::PrintExtractor(WriteFacade& writer) : writer(writer) {}

void PrintExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  // consume 'print'
  it++;

  const auto& variablePrint = (*it)->getValue();

  int currentStmtNo = DesignExtractor::getStmtNumber();
  VariableExtractor variableExtractor{this->writer};
  variableExtractor.extract(it, end);

  // consume ';'
  it++;

  this->writer.insertUses(currentStmtNo, variablePrint);
  this->writer.insertStmtPrintsVar(currentStmtNo, variablePrint);
  this->varUsed.insert(variablePrint);
}

void PrintExtractor::dumpContentsInto(StmtLstExtractor& stmtListExtractor,
                                      [[maybe_unused]] int currentStmtNo) {
  stmtListExtractor.addVarUsedByStmt(this->varUsed);
}
}  // namespace SP
