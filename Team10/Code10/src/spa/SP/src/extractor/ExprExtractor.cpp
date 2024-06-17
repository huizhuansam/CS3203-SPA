#include "ExprExtractor.h"

#include "GrammarRule.h"
#include "SyntaxError.h"
#include "TermExtractor.h"
#include "WriteFacade.h"

namespace SP {
ExprExtractor::ExprExtractor(WriteFacade& writer) : writer(writer) {}

void ExprExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  TermExtractor termExtractor{writer};
  termExtractor.extract(it, end);

  if (it == end) {
    // valid case where the expression is only a variable or constant
    return;
  }

  while ((*it)->getType() == TokenType::PLUS ||
         (*it)->getType() == TokenType::MINUS) {
    // consume + or -
    it++;

    // consume factor
    termExtractor.extract(it, end);
  }
}
}  // namespace SP
