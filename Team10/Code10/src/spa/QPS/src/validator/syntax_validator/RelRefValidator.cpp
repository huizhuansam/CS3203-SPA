#include "validator/syntax_validator/RelRefValidator.h"

#include "validator/syntax_validator/EntRefAndEntRefValidator.h"

namespace QPS {
std::unordered_set<std::string> RelRefValidator::relRefSet = {
    "Follows", "Follows*", "Parent", "Parent*", "Uses",   "Modifies",
    "Calls",   "Calls*",   "Next",   "Next*",   "Affects"};

void RelRefValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator &it,
    const std::vector<std::shared_ptr<Token>>::iterator &end) {
  if (it == end || relRefSet.find((*it)->getValue()) == relRefSet.end()) {
    throw SyntaxError(GrammarRule::REL_REF);
  }
  auto &relRef = (*it)->getValue();
  // consume the relRef token
  consume(it, end, TokenType::NAME, GrammarRule::REL_REF);
  // consume '('
  consume(it, end, TokenType::OPEN_BRACKET, GrammarRule::REL_REF);
  if (relRef == "Modifies" || relRef == "Uses") {
    EntRefOrStmtRefAndEntRefValidator stmtOrProcAndVarArgsValidator;
    stmtOrProcAndVarArgsValidator.validate(it, end);
  } else if (relRef == "Follows" || relRef == "Follows*" ||
             relRef == "Parent" || relRef == "Parent*" || relRef == "Next" ||
             relRef == "Next*" || relRef == "Affects") {
    StmtRefAndStmtRefValidator stmtRefAndStmtRefValidator;
    stmtRefAndStmtRefValidator.validate(it, end);
  } else if (relRef == "Calls" || relRef == "Calls*") {
    EntRefAndEntRefValidator entRefAndEntRefValidator;
    entRefAndEntRefValidator.validate(it, end);
  }
  // consume ')'
  consume(it, end, TokenType::CLOSE_BRACKET, GrammarRule::REL_REF);
}
}  // namespace QPS
