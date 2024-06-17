#include "validator/syntax_validator/RelCondValidator.h"

namespace QPS {
void RelCondValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator &it,
    const std::vector<std::shared_ptr<Token>>::iterator &end) {
  // at least 1
  consumeOptional(it, end, "not");
  RelRefValidator relRefValidator;
  relRefValidator.validate(it, end);

  while (it != end && (*it)->getValue() == "and") {
    consume(it, end, "and", GrammarRule::REL_COND);
    consumeOptional(it, end, "not");
    relRefValidator.validate(it, end);
  }
}
}  // namespace QPS
