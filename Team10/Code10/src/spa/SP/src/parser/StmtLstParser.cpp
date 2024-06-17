#include "StmtLstParser.h"

#include <memory>

#include "GrammarRule.h"
#include "StmtParser.h"
#include "SyntaxError.h"
#include "tokenizer/Token.h"

namespace SP {
void StmtLstParser::parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                          std::vector<std::unique_ptr<Token>>::iterator& end) {
  // stmtLst: stmt+
  if (it == end || !(*it)->canBeName()) {
    throw SyntaxError(GrammarRule::STMT_LIST);
  }

  while (it != end && (*it)->canBeName()) {
    std::unique_ptr<StmtParser> parser = StmtParser::of(it, end);
    parser->parse(it, end);

    std::string procCalled = parser->getProcCalled();
    if (!procCalled.empty()) {
      addProcCalled(procCalled);
    }
  }
}

void StmtLstParser::addProcCalled(std::string& procName) {
  procCalledSet.insert(procName);
}

std::unordered_set<std::string> StmtLstParser::getProcCalledSet() {
  return procCalledSet;
}
}  // namespace SP
