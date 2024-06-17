#include "CallParser.h"

#include "GrammarRule.h"
#include "StmtParser.h"

namespace SP {
void CallParser::parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                       std::vector<std::unique_ptr<Token>>::iterator& end) {
  // read: 'call' proc_name';'
  consume(it, end, TokenType::CALL, GrammarRule::CALL);

  expect(it, end, TokenType::NAME, GrammarRule::CALL);
  std::string procName = (*it)->getValue();
  setProcCalled(procName);
  consume(it, end, TokenType::NAME, GrammarRule::CALL);

  consume(it, end, TokenType::SEMICOLON, GrammarRule::CALL);
}
}  // namespace SP
