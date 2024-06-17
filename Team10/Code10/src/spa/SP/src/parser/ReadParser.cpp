#include "ReadParser.h"

#include "GrammarRule.h"
#include "StmtParser.h"
#include "SyntaxError.h"
#include "VariableParser.h"

namespace SP {
void ReadParser::parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                       std::vector<std::unique_ptr<Token>>::iterator& end) {
  // read: 'read' var_name';'
  consume(it, end, TokenType::READ, GrammarRule::READ);

  VariableParser variableParser{};
  variableParser.parse(it, end);

  consume(it, end, TokenType::SEMICOLON, GrammarRule::READ);
}
}  // namespace SP
