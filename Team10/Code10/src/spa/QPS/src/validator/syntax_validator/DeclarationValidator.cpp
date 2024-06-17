#include "validator/syntax_validator/DeclarationValidator.h"

namespace QPS {
std::unordered_set<std::string> DeclarationValidator::designEntitySet = {
    "stmt", "read",   "print",    "call",     "while",
    "if",   "assign", "variable", "constant", "procedure"};

void DeclarationValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  if (it == end) {
    throw SyntaxError(GrammarRule::DECLARATION);
  }
  auto& designEntity = (*it)->getValue();

  if (designEntitySet.count(designEntity) == 0) {
    throw SyntaxError(GrammarRule::DESIGN_ENTITY);
  }

  // consume design-entity
  consume(it, end, TokenType::NAME, GrammarRule::DESIGN_ENTITY);

  while (it != end) {
    // consume synonym
    consume(it, end, TokenType::NAME, GrammarRule::NAME);
    if (it == end) {
      throw SyntaxError(GrammarRule::DECLARATION);
    }
    if ((*it)->getType() == TokenType::SEMICOLON) {
      break;
    }
    consume(it, end, TokenType::COMMA, GrammarRule::DECLARATION);
  }
  consume(it, end, TokenType::SEMICOLON, GrammarRule::DECLARATION);
}
}  // namespace QPS
