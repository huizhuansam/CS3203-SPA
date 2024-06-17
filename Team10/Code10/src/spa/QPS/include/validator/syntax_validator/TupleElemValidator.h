#pragma once

#include "../../exception/GrammarRule.h"
#include "../../validator/IValidator.h"

namespace QPS {
class TupleElemValidator : public IValidator {
 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
