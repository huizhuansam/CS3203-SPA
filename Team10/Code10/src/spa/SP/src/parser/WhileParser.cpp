#include "WhileParser.h"

#include "CondExprParser.h"
#include "GrammarRule.h"
#include "StmtLstParser.h"
#include "StmtParser.h"

namespace SP {
void WhileParser::parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                        std::vector<std::unique_ptr<Token>>::iterator& end) {
  // while: 'while' '(' cond_expr ')' '{' stmtLst '}'
  consume(it, end, TokenType::WHILE, GrammarRule::WHILE);
  consume(it, end, TokenType::OPEN_BRACKET, GrammarRule::WHILE);

  CondExprParser condExprParser{};
  condExprParser.parse(it, end);

  consume(it, end, TokenType::CLOSE_BRACKET, GrammarRule::WHILE);
  consume(it, end, TokenType::OPEN_CURLY_BRACKET, GrammarRule::WHILE);

  StmtLstParser stmtLstParser{};
  stmtLstParser.parse(it, end);

  consume(it, end, TokenType::CLOSE_CURLY_BRACKET, GrammarRule::WHILE);
}
}  // namespace SP
