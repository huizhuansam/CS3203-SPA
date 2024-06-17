#include "CondExprParser.h"

#include "GrammarRule.h"
#include "RelExprParser.h"
#include "SyntaxError.h"

namespace SP {
void CondExprParser::parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                           std::vector<std::unique_ptr<Token>>::iterator& end) {
  // cond_expr: rel_expr | '!' '(' cond_expr ')' |
  //           '(' cond_expr ')' '&&' '(' cond_expr ')' |
  //           '(' cond_expr ')' '||' '(' cond_expr ')'
  if (it == end) {
    throw SyntaxError(GrammarRule::COND_EXPR);
  }
  TokenType currentTokenType = it->get()->getType();

  if (currentTokenType == TokenType::NOT) {
    parseNotCondExpr(it, end);
  } else if (currentTokenType == TokenType::OPEN_BRACKET &&
             isOpenBracketOfCondExpr(it)) {
    parseAndOrCondExpr(it, end);
  } else {
    parseRelExpr(it, end);
  }
}

void CondExprParser::parseNotCondExpr(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    std::vector<std::unique_ptr<Token>>::iterator& end) {
  consume(it, end, TokenType::NOT, GrammarRule::COND_EXPR);
  consume(it, end, TokenType::OPEN_BRACKET, GrammarRule::COND_EXPR);
  this->parse(it, end);
  consume(it, end, TokenType::CLOSE_BRACKET, GrammarRule::COND_EXPR);
}

void CondExprParser::parseAndOrCondExpr(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    std::vector<std::unique_ptr<Token>>::iterator& end) {
  consume(it, end, TokenType::OPEN_BRACKET, GrammarRule::COND_EXPR);
  this->parse(it, end);
  consume(it, end, TokenType::CLOSE_BRACKET, GrammarRule::COND_EXPR);

  if (it == end || !((*it)->getType() == TokenType::AND ||
                     (*it)->getType() == TokenType::OR)) {
    throw SyntaxError(GrammarRule::COND_EXPR);
  } else {
    TokenType type = (*it)->getType();
    consume(it, end, type, GrammarRule::COND_EXPR);
  }

  consume(it, end, TokenType::OPEN_BRACKET, GrammarRule::COND_EXPR);
  this->parse(it, end);
  consume(it, end, TokenType::CLOSE_BRACKET, GrammarRule::COND_EXPR);
}

bool CondExprParser::isOpenBracketOfCondExpr(
    std::vector<std::unique_ptr<Token>>::iterator it) {
  int numOpenBrackets = 1;
  auto checkIt = it + 1;

  while (numOpenBrackets > 0) {
    if ((*checkIt)->getType() == TokenType::OPEN_BRACKET) {
      numOpenBrackets++;
    } else if ((*checkIt)->getType() == TokenType::CLOSE_BRACKET) {
      numOpenBrackets--;
    } else if ((*checkIt)->getType() == TokenType::GT ||
               (*checkIt)->getType() == TokenType::LT ||
               (*checkIt)->getType() == TokenType::GTE ||
               (*checkIt)->getType() == TokenType::LTE ||
               (*checkIt)->getType() == TokenType::EQ ||
               (*checkIt)->getType() == TokenType::NEQ) {
      return true;
    }
    checkIt++;
  }

  return false;
}

void CondExprParser::parseRelExpr(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    std::vector<std::unique_ptr<Token>>::iterator& end) {
  RelExprParser relExprParser{};
  relExprParser.parse(it, end);
}
}  // namespace SP
