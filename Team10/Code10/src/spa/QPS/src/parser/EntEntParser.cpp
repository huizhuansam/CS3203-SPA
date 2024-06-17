#include "parser/EntEntParser.h"

namespace QPS {
std::shared_ptr<EntEntArgStrategy> EntEntParser::parse(
    StrategyType strategyType,
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::unordered_map<std::string, SynonymType>& declarationsMap) {
  ParserUtil::skipOpenBracket(it);

  std::pair<std::string, EntRefType> arg1 =
      ParserUtil::parseEntRef(it, declarationsMap);
  ParserUtil::skipComma(it);

  std::pair<std::string, EntRefType> arg2 =
      ParserUtil::parseEntRef(it, declarationsMap);
  ParserUtil::skipCloseBracket(it);

  return std::make_shared<EntEntArgStrategy>(
      strategyType, arg1.first, arg1.second, arg2.first, arg2.second);
}
}  // namespace QPS
