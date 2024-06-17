#include "parser/WithParser.h"

namespace QPS {
std::shared_ptr<WithStrategy> WithParser::parse(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::unordered_map<std::string, SynonymType>& declarationsMap) {
  auto args1 = parseRef(it, declarationsMap);
  it += 2;  // skip '='

  auto args2 = parseRef(it, declarationsMap);
  it++;  // skip arg2

  return std::make_shared<WithStrategy>(args1.first, args1.second, args2.first,
                                        args2.second);
}

std::pair<std::string, RefType> WithParser::parseRef(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::unordered_map<std::string, SynonymType>& declarationsMap) {
  RefType refType;
  std::string arg;
  TokenType tokenType = (*it)->getType();
  switch (tokenType) {
    case TokenType::DOUBLE_QUOTE:
      refType = RefType::IDENT;
      it++;  // skip open double quote
      arg = (*(it))->getValue();
      it++;  // move itr to close double quote
      break;
    case TokenType::INTEGER:
      refType = RefType::INTEGER;
      arg = (*it)->getValue();
      break;
    default:
      return parseAttrRef(it, declarationsMap);
  }
  return std::make_pair(arg, refType);
}

std::pair<std::string, RefType> WithParser::parseAttrRef(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::unordered_map<std::string, SynonymType>& declarationsMap) {
  std::string synonym = (*it)->getValue();

  SynonymType synonymType = declarationsMap.at(synonym);
  it += 2;  // move itr to attrName

  std::string attrName = (*(it))->getValue();
  RefType refType = getRefType(synonymType, attrName);

  return std::make_pair(synonym, refType);
}

RefType WithParser::getRefType(SynonymType type, const std::string& attrName) {
  auto it = typeMap.find({type, attrName});
  if (it != typeMap.end()) {
    return it->second;
  }
  return RefType::NONE;
}

std::unordered_map<std::pair<SynonymType, std::string>, RefType, PairHash>
    WithParser::typeMap = {
        {{SynonymType::PROCEDURE, "procName"}, RefType::PROCEDURE_PROCNAME},
        {{SynonymType::VARIABLE, "varName"}, RefType::VARIABLE_VARNAME},
        {{SynonymType::CONSTANT, "value"}, RefType::CONSTANT_VALUE},
        {{SynonymType::STMT, "stmt#"}, RefType::STMT_STMTNO},
        {{SynonymType::WHILE, "stmt#"}, RefType::WHILE_STMTNO},
        {{SynonymType::IF, "stmt#"}, RefType::IF_STMTNO},
        {{SynonymType::ASSIGN, "stmt#"}, RefType::ASSIGN_STMTNO},
        {{SynonymType::CALL, "procName"}, RefType::CALL_PROCNAME},
        {{SynonymType::CALL, "stmt#"}, RefType::CALL_STMTNO},
        {{SynonymType::READ, "varName"}, RefType::READ_VARNAME},
        {{SynonymType::READ, "stmt#"}, RefType::READ_STMTNO},
        {{SynonymType::PRINT, "varName"}, RefType::PRINT_VARNAME},
        {{SynonymType::PRINT, "stmt#"}, RefType::PRINT_STMTNO},
};
}  // namespace QPS
