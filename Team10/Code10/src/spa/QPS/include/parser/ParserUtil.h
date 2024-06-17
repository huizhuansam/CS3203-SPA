#pragma once

#include <unordered_map>
#include <vector>

#include "../tokenizer/Token.h"
#include "../tokenizer/TokenType.h"
#include "strategy/Strategy.h"
#include "strategy/argument_types/EntRefType.h"
#include "strategy/argument_types/ExprSpecType.h"
#include "strategy/argument_types/StmtRefType.h"
#include "strategy/argument_types/SynonymType.h"

namespace QPS {
class ParserUtil {
 public:
  static std::pair<std::string, EntRefType> parseEntRef(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::unordered_map<std::string, SynonymType>& declarationsMap);

  static std::pair<std::string, StmtRefType> parseStmtRef(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::unordered_map<std::string, SynonymType>& declarationsMap);

  static std::pair<std::vector<std::string>, ExprSpecType> parseExprSpec(
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static void skipOpenBracket(
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static void skipComma(std::vector<std::shared_ptr<Token>>::iterator& it);

  static void skipCloseBracket(
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static void skipAngleBracket(
      std::vector<std::shared_ptr<Token>>::iterator& it);

 private:
  static StmtRefType getStmtRefType(
      TokenType type, const std::string& value,
      std::unordered_map<std::string, SynonymType> declarationsMap);

  static EntRefType getEntRefType(
      TokenType type, const std::string& value,
      std::unordered_map<std::string, SynonymType> declarationsMap);

  static ExprSpecType getExprSpecType(
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static StmtRefType getSynonymStmtType(SynonymType type);

  static EntRefType getSynonymEntType(SynonymType type);

  static std::vector<std::string> getExpr(
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static std::unordered_map<SynonymType, StmtRefType> synonymStmtTypeMap;
  static std::unordered_map<SynonymType, EntRefType> synonymEntTypeMap;
};
}  // namespace QPS
