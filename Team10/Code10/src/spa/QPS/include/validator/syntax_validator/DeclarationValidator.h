#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../../exception/GrammarRule.h"
#include "../../exception/SyntaxError.h"
#include "../../tokenizer/Token.h"
#include "../../validator/IValidator.h"

namespace QPS {
class DeclarationValidator : public IValidator {
 private:
  static std::unordered_set<std::string> designEntitySet;

 public:
  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;
};
}  // namespace QPS
