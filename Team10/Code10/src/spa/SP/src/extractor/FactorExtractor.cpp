#include "FactorExtractor.h"

#include "ConstantExtractor.h"
#include "ExprExtractor.h"
#include "GrammarRule.h"
#include "SyntaxError.h"
#include "VariableExtractor.h"
#include "WriteFacade.h"

namespace SP {
FactorExtractor::FactorExtractor(WriteFacade& writer) : writer(writer) {}

void FactorExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  switch ((*it)->getType()) {
    case TokenType::NAME: {
      VariableExtractor variableExtractor(writer);
      variableExtractor.extract(it, end);
      break;
    }
    case TokenType::INTEGER: {
      ConstantExtractor constantExtractor(writer);
      constantExtractor.extract(it, end);
      break;
    }
    default: {
      // consume '('
      it++;

      // extract expression
      ExprExtractor exprExtractor(writer);
      exprExtractor.extract(it, end);

      // consume ')'
      it++;
      break;
    }
  }

  return;
}
}  // namespace SP
