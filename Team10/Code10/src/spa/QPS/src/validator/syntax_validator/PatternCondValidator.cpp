#include "validator/syntax_validator/PatternCondValidator.h"

namespace QPS {
void PatternCondValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator &it,
    const std::vector<std::shared_ptr<Token>>::iterator &end) {
  // at least 1
  consumeOptional(it, end, "not");
  PatternValidator patternValidator;
  patternValidator.validate(it, end);

  while (it != end && (*it)->getValue() == "and") {
    consume(it, end, "and", GrammarRule::PATTERN_COND);
    consumeOptional(it, end, "not");
    patternValidator.validate(it, end);
  }
}
}  // namespace QPS
