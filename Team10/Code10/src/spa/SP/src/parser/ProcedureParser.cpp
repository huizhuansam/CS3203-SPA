#include "ProcedureParser.h"

#include <utility>

#include "GrammarRule.h"
#include "StmtLstParser.h"
#include "SyntaxError.h"
#include "tokenizer/TokenType.h"

namespace SP {
void ProcedureParser::parse(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    std::vector<std::unique_ptr<Token>>::iterator& end) {
  // procedure: 'procedure' proc_name '{' stmtLst '}'
  consume(it, end, TokenType::PROCEDURE, GrammarRule::PROCEDURE);

  expect(it, end, TokenType::NAME, GrammarRule::PROCEDURE);
  this->procedureName = (*it)->getValue();
  consume(it, end, TokenType::NAME, GrammarRule::PROCEDURE);

  consume(it, end, TokenType::OPEN_CURLY_BRACKET, GrammarRule::PROCEDURE);

  StmtLstParser parser{};
  parser.parse(it, end);

  setProcCalledSet(parser.getProcCalledSet());

  consume(it, end, TokenType::CLOSE_CURLY_BRACKET, GrammarRule::PROCEDURE);
}

std::string ProcedureParser::getProcedureName() { return this->procedureName; }

void ProcedureParser::setProcCalledSet(std::unordered_set<std::string> set) {
  procCalledSet = std::move(set);
}

std::unordered_set<std::string> ProcedureParser::getProcCalledSet() {
  return procCalledSet;
}
}  // namespace SP
