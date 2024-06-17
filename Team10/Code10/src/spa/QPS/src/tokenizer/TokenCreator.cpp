#include "tokenizer/TokenCreator.h"

#include "tokenizer/AttrNameTokenCreator.h"
#include "tokenizer/IntegerTokenCreator.h"
#include "tokenizer/NameTokenCreator.h"
#include "tokenizer/SymbolTokenCreator.h"
#include "tokenizer/WhitespaceTokenCreator.h"

namespace QPS {
std::unique_ptr<TokenCreator> TokenCreator::of(char character,
                                               bool isLasCharPeriod) {
  if (isLasCharPeriod) {
    return std::make_unique<AttrNameTokenCreator>();
  }

  if (StringHandler::isWhitespace(character)) {
    return std::make_unique<WhitespaceTokenCreator>();
  }
  if (StringHandler::isValidQuerySymbol(character)) {
    return std::make_unique<SymbolTokenCreator>();
  }
  if (StringHandler::isLetter(character)) {
    return std::make_unique<NameTokenCreator>();
  }
  if (StringHandler::isDigit(character)) {
    return std::make_unique<IntegerTokenCreator>();
  }
  throw SyntaxError("SyntaxError");
}
}  // namespace QPS