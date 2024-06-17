#pragma once

#include <memory>
#include <string>

#include "../../exception/GrammarRule.h"
#include "../../tokenizer/Token.h"
#include "../../tokenizer/TokenType.h"
#include "../../validator/syntax_validator/EntOrStmtRefValidator.h"
#include "../../validator/syntax_validator/EntRefValidator.h"
#include "../../validator/syntax_validator/RelRefValidator.h"

namespace QPS {
class EntRefOrStmtRefAndEntRefValidator : public IValidator {
 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
