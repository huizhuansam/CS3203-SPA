#include "validator/syntax_validator/EntRefAndEntRefValidator.h"

namespace QPS {
void EntRefAndEntRefValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  // consume stmtRef
  EntRefValidator entRefValidator;
  entRefValidator.validate(it, end);
  // consume ','
  consume(it, end, TokenType::COMMA, GrammarRule::ENT_REF);
  // consume stmtRef
  entRefValidator.validate(it, end);
}
}  // namespace QPS
