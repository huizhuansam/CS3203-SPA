#include "RelFactorParser.h"

#include "ExprParser.h"
#include "GrammarRule.h"

namespace SP {
void RelFactorParser::parse(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    std::vector<std::unique_ptr<Token>>::iterator& end) {
  // rel_factor: var_name | const_value | expr
  ExprParser exprParser{};
  exprParser.parse(it, end);
}
}  // namespace SP
