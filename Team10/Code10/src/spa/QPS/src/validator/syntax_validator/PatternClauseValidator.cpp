#include "validator/syntax_validator/PatternClauseValidator.h"

namespace QPS {
void PatternClauseValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  if (it == end) {
    throw SyntaxError(GrammarRule::PATTERN_CL);
  }
  consume(it, end, "pattern", GrammarRule::PATTERN_CL);
  PatternCondValidator patternCondValidator;
  patternCondValidator.validate(it, end);
}
}  // namespace QPS
