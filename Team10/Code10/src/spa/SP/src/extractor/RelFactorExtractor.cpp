#include "RelFactorExtractor.h"

#include "ExprExtractor.h"
#include "GrammarRule.h"
#include "WriteFacade.h"

namespace SP {
RelFactorExtractor::RelFactorExtractor(WriteFacade& writer) : writer(writer) {}

void RelFactorExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  ExprExtractor exprExtractor{this->writer};
  exprExtractor.extract(it, end);
}
}  // namespace SP
