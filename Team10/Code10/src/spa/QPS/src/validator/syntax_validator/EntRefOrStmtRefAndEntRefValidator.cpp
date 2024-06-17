#include "validator/syntax_validator/EntRefOrStmtRefAndEntRefValidator.h"

namespace QPS {
void EntRefOrStmtRefAndEntRefValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  // consume either entRef of stmtRef
  EntOrStmtRefValidator entOrStmtRefValidator;
  entOrStmtRefValidator.validate(it, end);
  // consume ','
  consume(it, end, TokenType::COMMA, GrammarRule::REL_REF);
  // consume entRef
  EntRefValidator entRefValidator;
  entRefValidator.validate(it, end);
}
}  // namespace QPS
