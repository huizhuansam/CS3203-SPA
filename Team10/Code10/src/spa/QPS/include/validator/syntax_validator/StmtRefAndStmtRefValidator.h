#pragma once

#include <memory>
#include <string>

#include "../../exception/GrammarRule.h"
#include "../../tokenizer/Token.h"
#include "../../tokenizer/TokenType.h"
#include "../../validator/syntax_validator/RelRefValidator.h"
#include "../../validator/syntax_validator/StmtRefValidator.h"

namespace QPS {
class StmtRefAndStmtRefValidator : public IValidator {
 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
