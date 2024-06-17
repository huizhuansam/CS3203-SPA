#include "ConstantParser.h"

#include <vector>

#include "GrammarRule.h"
#include "SyntaxError.h"
#include "tokenizer/Token.h"

namespace SP {
void ConstantParser::parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                           std::vector<std::unique_ptr<Token>>::iterator& end) {
  // const_value: INTEGER
  consume(it, end, TokenType::INTEGER, GrammarRule::CONST_VALUE);
}
}  // namespace SP
