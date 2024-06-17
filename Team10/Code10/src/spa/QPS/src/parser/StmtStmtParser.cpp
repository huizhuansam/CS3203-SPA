#include "parser/StmtStmtParser.h"

namespace QPS {
std::shared_ptr<StmtStmtArgStrategy> StmtStmtParser::parse(
    StrategyType strategyType,
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::unordered_map<std::string, SynonymType>& declarationsMap) {
  ParserUtil::skipOpenBracket(it);

  std::pair<std::string, StmtRefType> arg1 =
      ParserUtil::parseStmtRef(it, declarationsMap);
  ParserUtil::skipComma(it);

  std::pair<std::string, StmtRefType> arg2 =
      ParserUtil::parseStmtRef(it, declarationsMap);
  ParserUtil::skipCloseBracket(it);

  return std::make_shared<StmtStmtArgStrategy>(
      strategyType, arg1.first, arg1.second, arg2.first, arg2.second);
}
}  // namespace QPS
