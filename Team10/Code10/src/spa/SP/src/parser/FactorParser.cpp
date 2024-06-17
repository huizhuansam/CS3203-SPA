#include "FactorParser.h"

#include "ConstantParser.h"
#include "ExprParser.h"
#include "GrammarRule.h"
#include "SyntaxError.h"
#include "VariableParser.h"

namespace SP {
void FactorParser::parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                         std::vector<std::unique_ptr<Token>>::iterator& end) {
  // factor: var_name | const_value | '(' expr ')'
  if (it == end) {
    throw SyntaxError(GrammarRule::FACTOR);
  }

  auto currentToken = it->get();
  bool isNameToken = currentToken->canBeName();
  if (isNameToken) {
    VariableParser variableParser{};
    variableParser.parse(it, end);
    return;
  }

  bool isIntegerToken = currentToken->getType() == TokenType::INTEGER;
  if (isIntegerToken) {
    ConstantParser constantParser{};
    constantParser.parse(it, end);
    return;
  }

  bool isFirstTokenOpenBracket =
      currentToken->getType() == TokenType::OPEN_BRACKET;
  if (isFirstTokenOpenBracket) {
    consume(it, end, TokenType::OPEN_BRACKET, GrammarRule::FACTOR);
    ExprParser exprParser{};
    exprParser.parse(it, end);
    consume(it, end, TokenType::CLOSE_BRACKET, GrammarRule::FACTOR);
    return;
  }

  throw SyntaxError(GrammarRule::FACTOR);
}
}  // namespace SP
