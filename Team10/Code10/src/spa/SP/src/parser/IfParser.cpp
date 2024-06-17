#include "IfParser.h"

#include "CondExprParser.h"
#include "GrammarRule.h"
#include "StmtLstParser.h"
#include "StmtParser.h"
#include "SyntaxError.h"
#include "TokenType.h"

namespace SP {
void IfParser::parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                     std::vector<std::unique_ptr<Token>>::iterator& end) {
  // if: 'if' '(' cond_expr ')' 'then' '{' stmtLst '}' 'else' '{' stmtLst '}'
  consume(it, end, TokenType::IF, GrammarRule::IF);
  consume(it, end, TokenType::OPEN_BRACKET, GrammarRule::IF);

  CondExprParser conditionalParser{};
  conditionalParser.parse(it, end);

  consume(it, end, TokenType::CLOSE_BRACKET, GrammarRule::IF);
  consume(it, end, TokenType::THEN, GrammarRule::IF);
  consume(it, end, TokenType::OPEN_CURLY_BRACKET, GrammarRule::IF);

  StmtLstParser evalTrueStmtListParser{};
  evalTrueStmtListParser.parse(it, end);

  consume(it, end, TokenType::CLOSE_CURLY_BRACKET, GrammarRule::IF);
  consume(it, end, TokenType::ELSE, GrammarRule::IF);
  consume(it, end, TokenType::OPEN_CURLY_BRACKET, GrammarRule::IF);

  StmtLstParser evalFalseStmtListParser{};
  evalFalseStmtListParser.parse(it, end);

  consume(it, end, TokenType::CLOSE_CURLY_BRACKET, GrammarRule::IF);
}
}  // namespace SP
