#include "RelExprParser.h"

#include "GrammarRule.h"
#include "RelFactorParser.h"
#include "SyntaxError.h"

namespace SP {
void RelExprParser::parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                          std::vector<std::unique_ptr<Token>>::iterator& end) {
  // rel_expr: rel_factor '>' rel_factor | rel_factor '>=' rel_factor |
  //          rel_factor '<' rel_factor | rel_factor '<=' rel_factor |
  //          rel_factor '==' rel_factor | rel_factor '!=' rel_factor
  RelFactorParser relFactorParser{};
  relFactorParser.parse(it, end);

  // expect a relational expression operators
  if (it == end || !((*it)->getType() == TokenType::LT ||
                     (*it)->getType() == TokenType::LTE ||
                     (*it)->getType() == TokenType::GT ||
                     (*it)->getType() == TokenType::GTE ||
                     (*it)->getType() == TokenType::EQ ||
                     (*it)->getType() == TokenType::NEQ)) {
    throw SyntaxError(GrammarRule::REL_EXPR);
  }
  consume(it, end, (*it)->getType(), GrammarRule::REL_EXPR);

  relFactorParser.parse(it, end);
}
}  // namespace SP
