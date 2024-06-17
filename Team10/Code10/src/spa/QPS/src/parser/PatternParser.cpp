#include "parser/PatternParser.h"

namespace QPS {
std::shared_ptr<PatternStrategy> PatternParser::parse(
    StrategyType strategyType,
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::unordered_map<std::string, SynonymType>& declarationsMap) {
  const std::string synonym = (*it)->getValue();
  it += 2;  // move itr to arg1

  std::pair<std::string, EntRefType> arg1 =
      ParserUtil::parseEntRef(it, declarationsMap);
  std::pair<std::vector<std::string>, ExprSpecType> arg2 = {
      {}, ExprSpecType::INVALID};

  if (strategyType == StrategyType::ASSIGN_PATTERN) {
    ParserUtil::skipComma(it);
    arg2 = ParserUtil::parseExprSpec(it);
    ParserUtil::skipCloseBracket(it);
  }

  if (strategyType == StrategyType::WHILE_PATTERN) {
    it += 4;  // move itr to after close bracket
  }

  if (strategyType == StrategyType::IF_PATTERN) {
    it += 6;  // move itr to after close bracket
  }

  return std::make_shared<PatternStrategy>(
      strategyType, synonym, arg1.first, arg1.second, arg2.first, arg2.second);
}
}  // namespace QPS
