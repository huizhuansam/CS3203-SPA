#include "AssignParser.h"

#include "ExprParser.h"
#include "GrammarRule.h"
#include "StmtParser.h"
#include "VariableParser.h"

namespace SP {
void AssignParser::parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                         std::vector<std::unique_ptr<Token>>::iterator& end) {
  // assign: var_name '=' expr ';'
  VariableParser variableParser{};
  variableParser.parse(it, end);

  consume(it, end, TokenType::ASSIGN, GrammarRule::ASSIGN);

  ExprParser exprParser{};
  exprParser.parse(it, end);

  consume(it, end, TokenType::SEMICOLON, GrammarRule::ASSIGN);
}
}  // namespace SP
