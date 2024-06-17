#pragma once

#include "../../exception/GrammarRule.h"
#include "../../exception/SyntaxError.h"
#include "../../validator/IValidator.h"

namespace QPS {
class EntOrStmtRefValidator : public IValidator {
 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
