#pragma once

#include <memory>
#include <vector>

#include "../tokenizer/Token.h"
#include "../validator/semantic_validator/SemanticValidator.h"
#include "../validator/syntax_validator/SyntaxValidator.h"

namespace QPS {
class Validator {
 public:
  Validator() = delete;

  static void validate(std::vector<std::shared_ptr<Token>>& tokens);
};
}  // namespace QPS
