#include "AttrNameTokenCreator.h"

namespace QPS {
const std::unordered_set<std::string> AttrNameTokenCreator::validAttrNameSet = {
    "procName",
    "varName",
    "value",
    "stmt#",
};

std::shared_ptr<Token> AttrNameTokenCreator::createToken(
    std::string::const_iterator& it, std::string::const_iterator& end) {
  // form a name word
  std::string name = StringHandler::formWordString(it, end);

  // handle 'stmt#'
  if (name == "stmt") {
    // check if the next character is #
    if (StringHandler::hasNextChar(it, end) && *(it + 1) == '#') {
      StringHandler::pointNextChar(it);
      // form the name word
      name += *it;
    } else {
      throw SyntaxError("SyntaxError");
    }
  }

  // attrName : 'procName'| 'varName' | 'value' | 'stmt#'
  if (validAttrNameSet.find(name) == validAttrNameSet.end()) {
    throw SyntaxError(GrammarRule::ATTR_NAME);
  }

  return std::make_shared<Token>(TokenType::ATTR_NAME, name);
}
}  // namespace QPS
