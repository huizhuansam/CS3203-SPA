#pragma once

#include "../../exception/GrammarRule.h"
#include "../../validator/IValidator.h"
#include "../../validator/syntax_validator/TupleElemValidator.h"
#include "../../validator/syntax_validator/TupleValidator.h"

namespace QPS {
class SelectResultClauseValidator : public IValidator {
 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
