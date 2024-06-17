#include "PrintParser.h"

#include <vector>

#include "GrammarRule.h"
#include "StmtParser.h"
#include "SyntaxError.h"
#include "VariableParser.h"

namespace SP {
void PrintParser::parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                        std::vector<std::unique_ptr<Token>>::iterator& end) {
  // print: 'print' var_name';'
  consume(it, end, TokenType::PRINT, GrammarRule::PRINT);

  VariableParser variableParser{};
  variableParser.parse(it, end);

  consume(it, end, TokenType::SEMICOLON, GrammarRule::PRINT);
}
}  // namespace SP
