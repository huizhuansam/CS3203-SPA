#include "validator/Validator.h"

namespace QPS {
void Validator::validate(std::vector<std::shared_ptr<Token>>& tokens) {
  auto it = tokens.begin();
  const auto end = tokens.end();
  SyntaxValidator syntaxValidator;
  syntaxValidator.validate(it, end);
  SemanticValidator semanticValidator;
  it = tokens.begin();
  semanticValidator.validate(it, end);
}
}  // namespace QPS
