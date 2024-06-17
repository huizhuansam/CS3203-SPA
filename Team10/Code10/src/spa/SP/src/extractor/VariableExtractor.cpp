#include "VariableExtractor.h"

#include <cassert>
#include <vector>

#include "GrammarRule.h"
#include "SyntaxError.h"
#include "WriteFacade.h"
#include "tokenizer/Token.h"

namespace SP {
VariableExtractor::VariableExtractor(WriteFacade& writer) : writer(writer){};

void VariableExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    [[maybe_unused]] const std::vector<std::unique_ptr<Token>>::iterator& end) {
  this->writer.addVariable((*it)->getValue());

  // consume the variable
  it++;
}
}  // namespace SP
