#include "TokenHandler.h"

#include <memory>
#include <stdexcept>

#include "IntegerTokenHandler.h"
#include "StringHandler.h"
#include "SymbolTokenHandler.h"
#include "WhitespaceTokenHandler.h"
#include "WordTokenHandler.h"

namespace SP {
std::unique_ptr<TokenHandler> TokenHandler::of(char character) {
  if (StringHandler::isWhitespace(character)) {
    return std::make_unique<WhitespaceTokenHandler>();
  }
  if (StringHandler::isValidSourceSymbol(character)) {
    return std::make_unique<SymbolTokenHandler>();
  }
  if (StringHandler::isLetter(character)) {
    return std::make_unique<WordTokenHandler>();
  }
  if (StringHandler::isDigit(character)) {
    return std::make_unique<IntegerTokenHandler>();
  }
  throw std::runtime_error("Invalid character: " + std::string(1, character));
}
}  // namespace SP
