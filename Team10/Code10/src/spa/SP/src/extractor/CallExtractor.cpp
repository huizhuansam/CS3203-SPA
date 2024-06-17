#include "CallExtractor.h"

#include "DesignExtractor.h"

namespace SP {
CallExtractor::CallExtractor(WriteFacade& writer) : writer(writer) {}

void CallExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    [[maybe_unused]] const std::vector<std::unique_ptr<Token>>::iterator& end) {
  // consume 'call'
  it++;

  const auto& procedureName = (*it)->getValue();

  // consume procedure name
  it++;

  // consume ';'
  it++;

  int currentStmtNo = DesignExtractor::getStmtNumber();
  this->writer.insertStmtCallsProc(currentStmtNo, procedureName);
  this->procCalled.insert(procedureName);
}

void CallExtractor::dumpContentsInto(StmtLstExtractor& stmtListExtractor,
                                     int currentStmtNo) {
  stmtListExtractor.addProcCalledByStmt(this->procCalled);
  stmtListExtractor.addToStmtCallMap(currentStmtNo, this->procCalled);
}
}  // namespace SP
