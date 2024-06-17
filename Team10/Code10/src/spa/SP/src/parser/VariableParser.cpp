#include "VariableParser.h"

#include <cassert>
#include <vector>

#include "GrammarRule.h"
#include "SyntaxError.h"
#include "tokenizer/Token.h"

namespace SP {
void VariableParser::parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                           std::vector<std::unique_ptr<Token>>::iterator& end) {
  consume(it, end, TokenType::NAME, GrammarRule::VAR_NAME);
}
}  // namespace SP
