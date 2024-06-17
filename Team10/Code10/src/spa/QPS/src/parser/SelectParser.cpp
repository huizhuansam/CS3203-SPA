#include "parser/SelectParser.h"

namespace QPS {
std::shared_ptr<BooleanSelectStrategy> SelectParser::parseBooleanSelect(
    std::vector<std::shared_ptr<Token>>::iterator &it) {
  it++;  // skip BOOLEAN
  return std::make_shared<BooleanSelectStrategy>();
}

std::shared_ptr<TupleSelectStrategy> SelectParser::parseTupleSelect(
    std::vector<std::shared_ptr<Token>>::iterator &it,
    const std::vector<std::shared_ptr<Token>>::iterator &end,
    const std::unordered_map<std::string, SynonymType> &declarationsMap) {
  bool isTuple = (*it)->getType() == TokenType::OPEN_ANGLE_BRACKET;

  if (isTuple) {
    ParserUtil::skipAngleBracket(it);  // skip open bracket
  }

  std::vector<std::string> synonyms;
  std::vector<SynonymType> synonymTypes;
  std::vector<AttrNameType> attrNameTypes;
  while ((*it)->getType() != TokenType::CLOSE_ANGLE_BRACKET) {
    auto elem = parseElem(it, end, declarationsMap);
    synonyms.push_back(std::get<0>(elem));
    synonymTypes.push_back(std::get<1>(elem));
    attrNameTypes.push_back(std::get<2>(elem));

    if (!isTuple) {
      break;
    }

    if ((*it)->getType() == TokenType::COMMA) {
      it++;  // skip comma
    }
  }

  if (isTuple) {
    ParserUtil::skipAngleBracket(it);  // skip close bracket
  }
  return std::make_shared<TupleSelectStrategy>(synonyms, synonymTypes,
                                               attrNameTypes);
}

std::tuple<std::string, SynonymType, AttrNameType> SelectParser::parseElem(
    std::vector<std::shared_ptr<Token>>::iterator &it,
    const std::vector<std::shared_ptr<Token>>::iterator &end,
    const std::unordered_map<std::string, SynonymType> &declarationsMap) {
  std::string synonym = (*it)->getValue();
  SynonymType synonymType = declarationsMap.at(synonym);
  it++;  // skip synonym

  // check if it is an attrRef
  AttrNameType attrNameType = AttrNameType::NONE;
  if (it != end) {
    TokenType nextTokenType = (*it)->getType();
    if (nextTokenType == TokenType::PERIOD) {
      it++;  // skip period
      attrNameType = getAttrNameType((*it)->getValue());
      it++;  // skip attrName
    }
  }
  return std::make_tuple(synonym, synonymType, attrNameType);
}

AttrNameType SelectParser::getAttrNameType(const std::string &attrName) {
  if (attrName == "procName" || attrName == "varName") {
    return AttrNameType::NAME;
  } else {
    return AttrNameType::INTEGER;
  }
}
}  // namespace QPS
