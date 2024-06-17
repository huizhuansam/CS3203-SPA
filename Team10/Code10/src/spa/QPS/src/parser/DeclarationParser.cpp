#include "parser/DeclarationParser.h"

namespace QPS {
std::unordered_map<std::string, SynonymType> DeclarationParser::parse(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  std::unordered_map<std::string, SynonymType> declarationsMap;
  while (it != end && (*it)->getValue() != "Select") {
    SynonymType type = getSynonymType((*it)->getValue());
    declarationsMap[(*(++it))->getValue()] = type;
    for (it++; it != end && (*it)->getType() != TokenType::SEMICOLON; it++) {
      declarationsMap[(*(++it))->getValue()] = type;
    }
    it++;  // move itr to next synonym type
  }
  return declarationsMap;
}

SynonymType DeclarationParser::getSynonymType(const std::string& type) {
  return synonymTypeMap.at(type);
}

std::unordered_map<std::string, SynonymType> DeclarationParser::synonymTypeMap =
    {
        {"stmt", SynonymType::STMT},
        {"read", SynonymType::READ},
        {"print", SynonymType::PRINT},
        {"call", SynonymType::CALL},
        {"while", SynonymType::WHILE},
        {"if", SynonymType::IF},
        {"assign", SynonymType::ASSIGN},
        {"variable", SynonymType::VARIABLE},
        {"constant", SynonymType::CONSTANT},
        {"procedure", SynonymType::PROCEDURE},
};
}  // namespace QPS