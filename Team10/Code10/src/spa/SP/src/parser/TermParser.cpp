#include "TermParser.h"

#include "FactorParser.h"
#include "GrammarRule.h"
#include "SyntaxError.h"

namespace SP {
void TermParser::parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                       std::vector<std::unique_ptr<Token>>::iterator& end) {
  // term: term '*' factor | term '/' factor | term '%' factor | factor
  FactorParser factorParser{};
  factorParser.parse(it, end);

  while (it != end && ((*it)->getType() == TokenType::MULTIPLY ||
                       (*it)->getType() == TokenType::DIVIDE ||
                       (*it)->getType() == TokenType::MODULO)) {
    consume(it, end, (*it)->getType(), GrammarRule::TERM);
    factorParser.parse(it, end);
  }
}
}  // namespace SP
