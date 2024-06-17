#include "ConstantExtractor.h"

#include <vector>

#include "GrammarRule.h"
#include "SyntaxError.h"
#include "WriteFacade.h"
#include "tokenizer/Token.h"

namespace SP {
ConstantExtractor::ConstantExtractor(WriteFacade& writer) : writer(writer){};

void ConstantExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    [[maybe_unused]] const std::vector<std::unique_ptr<Token>>::iterator& end) {
  this->writer.addConstant((*it)->getValue());
  // consume the constant
  it++;
}
}  // namespace SP
