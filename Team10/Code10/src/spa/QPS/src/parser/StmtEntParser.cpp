#include "parser/StmtEntParser.h"

namespace QPS {
std::shared_ptr<StmtEntArgStrategy> StmtEntParser::parse(
    StrategyType strategyType,
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::unordered_map<std::string, SynonymType>& declarationsMap) {
  ParserUtil::skipOpenBracket(it);

  std::pair<std::string, StmtRefType> arg1 =
      ParserUtil::parseStmtRef(it, declarationsMap);
  ParserUtil::skipComma(it);

  std::pair<std::string, EntRefType> arg2 =
      ParserUtil::parseEntRef(it, declarationsMap);
  ParserUtil::skipCloseBracket(it);

  return std::make_shared<StmtEntArgStrategy>(
      strategyType, arg1.first, arg1.second, arg2.first, arg2.second);
}
}  // namespace QPS
