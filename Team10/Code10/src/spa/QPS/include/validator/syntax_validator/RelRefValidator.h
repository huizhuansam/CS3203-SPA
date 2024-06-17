#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "../../exception/GrammarRule.h"
#include "../../exception/SyntaxError.h"
#include "../../tokenizer/Token.h"
#include "../../tokenizer/TokenType.h"
#include "../../validator/IValidator.h"
#include "../../validator/syntax_validator/EntRefOrStmtRefAndEntRefValidator.h"
#include "../../validator/syntax_validator/StmtRefAndStmtRefValidator.h"

namespace QPS {
class RelRefValidator : public IValidator {
 private:
  static std::unordered_set<std::string> relRefSet;

 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
