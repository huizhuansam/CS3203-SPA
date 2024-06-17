#include "Parser.h"

#include <memory>
#include <vector>

#include "exception/GrammarRule.h"
#include "exception/SyntaxError.h"
#include "parser/ProgramParser.h"
#include "tokenizer/Token.h"

namespace SP {
void Parser::parse(std::vector<std::unique_ptr<Token>>& tokens) {
  if (tokens.empty()) {
    throw SyntaxError(GrammarRule::PROGRAM);
  }

  auto it = tokens.begin();
  auto end = tokens.end();

  ProgramParser programParser{};
  programParser.parse(it, end);
}
}  // namespace SP
