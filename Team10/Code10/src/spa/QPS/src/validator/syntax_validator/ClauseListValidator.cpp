#include "validator/syntax_validator/ClauseListValidator.h"

namespace QPS {

std::unordered_map<std::string, std::shared_ptr<IValidator>>
    ClauseListValidator::tokenToValidatorMap = {
        {"such", std::make_shared<SuchThatClauseValidator>()},
        {"pattern", std::make_shared<PatternClauseValidator>()},
        {"with", std::make_shared<WithClauseValidator>()}};

void ClauseListValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  // 0 or more clauses
  if (it == end) {
    return;
  }
  while (it != end) {
    auto& tokenValue = (*it)->getValue();
    if (tokenToValidatorMap.count(tokenValue) == 0) {
      throw SyntaxError(GrammarRule::SELECT_CL);
    }
    auto& validator = tokenToValidatorMap[tokenValue];
    validator->validate(it, end);
  }
}
}  // namespace QPS
