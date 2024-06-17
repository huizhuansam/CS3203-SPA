#include "ExprParser.h"

#include "GrammarRule.h"
#include "SyntaxError.h"
#include "TermParser.h"

namespace SP {
void ExprParser::parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                       std::vector<std::unique_ptr<Token>>::iterator& end) {
  // expr: expr '+' term | expr '-' term | term
  TermParser termParser{};
  termParser.parse(it, end);

  while (it != end && ((*it)->getType() == TokenType::PLUS ||
                       (*it)->getType() == TokenType::MINUS)) {
    TokenType plusOrMinus = (*it)->getType();
    consume(it, end, plusOrMinus, GrammarRule::EXPR);
    termParser.parse(it, end);
  }
}
}  // namespace SP
