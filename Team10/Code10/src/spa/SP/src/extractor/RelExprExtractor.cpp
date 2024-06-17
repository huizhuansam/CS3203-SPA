#include "RelExprExtractor.h"

#include "GrammarRule.h"
#include "RelFactorExtractor.h"
#include "SyntaxError.h"
#include "WriteFacade.h"

namespace SP {
RelExprExtractor::RelExprExtractor(WriteFacade& writer) : writer(writer) {}

void RelExprExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  // consume the first relational factor
  RelFactorExtractor relFactorExtractor{writer};
  relFactorExtractor.extract(it, end);

  // consume the operator
  it++;

  // consume the next relational factor
  relFactorExtractor.extract(it, end);

  return;
}
}  // namespace SP
