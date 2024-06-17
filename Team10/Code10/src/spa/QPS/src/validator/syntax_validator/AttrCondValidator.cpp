#include "validator/syntax_validator/AttrCondValidator.h"

namespace QPS {
void AttrCondValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  // at least 1
  consumeOptional(it, end, "not");
  AttrCompareValidator attrCompareValidator;
  attrCompareValidator.validate(it, end);

  while (it != end && (*it)->getValue() == "and") {
    consume(it, end, "and", GrammarRule::ATTR_COND);
    consumeOptional(it, end, "not");
    attrCompareValidator.validate(it, end);
  }
}
}  // namespace QPS
