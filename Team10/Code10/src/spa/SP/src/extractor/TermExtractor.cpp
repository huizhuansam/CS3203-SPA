#include "TermExtractor.h"

#include "FactorExtractor.h"
#include "GrammarRule.h"
#include "SyntaxError.h"
#include "WriteFacade.h"

namespace SP {
TermExtractor::TermExtractor(WriteFacade& writer) : writer(writer) {}

void TermExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  FactorExtractor factorExtractor{writer};
  factorExtractor.extract(it, end);

  if (it == end) {
    // valid case where the term is only a variable or constant
    return;
  }

  while ((*it)->getType() == TokenType::MULTIPLY ||
         (*it)->getType() == TokenType::DIVIDE ||
         (*it)->getType() == TokenType::MODULO) {
    // consume * or / or %
    it++;

    // consume factor
    factorExtractor.extract(it, end);
  }

  return;
}
}  // namespace SP
