#include "tokenizer/NameTokenCreator.h"

namespace QPS {
std::shared_ptr<Token> NameTokenCreator::createToken(
    std::string::const_iterator& it, std::string::const_iterator& end) {
  // form a name word
  std::string name = StringHandler::formWordString(it, end);

  // handle Follows*, Parent*, Calls*, Next* cases
  if (name == "Follows" || name == "Parent" || name == "Calls" ||
      name == "Next") {
    // check if the next character is *
    if (StringHandler::hasNextChar(it, end) && *(it + 1) == '*') {
      StringHandler::pointNextChar(it);
      // form the name word
      name += *it;
    }
  }
  return std::make_shared<Token>(TokenType::NAME, name);
}
}  // namespace QPS
