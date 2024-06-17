#include "validator/syntax_validator/SuchThatClauseValidator.h"

namespace QPS {
void SuchThatClauseValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  if (it == end) {
    throw SyntaxError(GrammarRule::SUCHTHAT_CL);
  }
  consume(it, end, "such", GrammarRule::SUCHTHAT_CL);
  consume(it, end, "that", GrammarRule::SUCHTHAT_CL);
  RelCondValidator relCondValidator;
  relCondValidator.validate(it, end);
};
}  // namespace QPS
