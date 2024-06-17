#include "validator/syntax_validator/SelectResultClauseValidator.h"

namespace QPS {
void SelectResultClauseValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  consume(it, end, "Select", GrammarRule::SELECT_CL);

  // Tuple with multiple elements in <>
  if (it != end && (*it)->getType() == TokenType::OPEN_ANGLE_BRACKET) {
    TupleValidator tupleValidator;
    tupleValidator.validate(it, end);
    return;
  }

  // Tuple with single element without <>
  TupleElemValidator tupleElemValidator;
  tupleElemValidator.validate(it, end);
}
}  // namespace QPS
