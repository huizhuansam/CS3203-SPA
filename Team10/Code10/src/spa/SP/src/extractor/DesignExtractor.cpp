#include "DesignExtractor.h"

#include <memory>
#include <vector>

#include "ProgramExtractor.h"
#include "WriteFacade.h"
#include "tokenizer/Token.h"

namespace SP {
int DesignExtractor::stmtNumber = 0;

void DesignExtractor::extract(std::vector<std::unique_ptr<Token>>& tokens) {
  WriteFacade writer{};
  ProgramExtractor programExtractor{writer};

  auto it = tokens.begin();
  const auto end = tokens.end();
  programExtractor.extract(it, end);

  return;
}

void DesignExtractor::resetStmtNumber() { stmtNumber = 0; }

int DesignExtractor::getStmtNumber() { return stmtNumber; }

void DesignExtractor::incrementStmtNumber() { stmtNumber++; }
}  // namespace SP
