#include "validator/syntax_validator/StmtRefAndStmtRefValidator.h"

namespace QPS {
void StmtRefAndStmtRefValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  // consume stmtRef
  StmtRefValidator stmtRefValidator;
  stmtRefValidator.validate(it, end);
  // consume ','
  consume(it, end, TokenType::COMMA, GrammarRule::REL_REF);
  // consume stmtRef
  stmtRefValidator.validate(it, end);
}
}  // namespace QPS
