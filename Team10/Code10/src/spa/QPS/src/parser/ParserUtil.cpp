#include "parser/ParserUtil.h"

namespace QPS {
std::pair<std::string, StmtRefType> ParserUtil::parseStmtRef(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::unordered_map<std::string, SynonymType>& declarationsMap) {
  std::string arg = (*it)->getValue();
  StmtRefType argType = ParserUtil::getStmtRefType(
      (*it)->getType(), (*it)->getValue(), declarationsMap);
  return {arg, argType};
}

std::pair<std::string, EntRefType> ParserUtil::parseEntRef(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::unordered_map<std::string, SynonymType>& declarationsMap) {
  EntRefType argType = ParserUtil::getEntRefType(
      (*it)->getType(), (*it)->getValue(), declarationsMap);
  std::string arg;
  if (argType == EntRefType::IDENT) {
    it++;  // skip open double quote
    arg = (*(it))->getValue();
    it++;  // move itr to double quote
  } else {
    arg = (*it)->getValue();
  }
  return {arg, argType};
}

std::pair<std::vector<std::string>, ExprSpecType> ParserUtil::parseExprSpec(
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  ExprSpecType exprType = ParserUtil::getExprSpecType(it);
  if (exprType == ExprSpecType::WILDCARD) {
    return {{(*it)->getValue()}, exprType};
  }
  std::vector<std::string> expression = ParserUtil::getExpr(it);
  if (exprType == ExprSpecType::WILDCARD_EXPR) {
    it++;  // move itr to wildcard
  }
  return {expression, exprType};
}

StmtRefType ParserUtil::getStmtRefType(
    TokenType type, const std::string& value,
    std::unordered_map<std::string, SynonymType> declarationsMap) {
  switch (type) {
    case TokenType::WILDCARD:
      return StmtRefType::WILDCARD;
    case TokenType::INTEGER:
      return StmtRefType::INTEGER;
    case TokenType::NAME:
      return getSynonymStmtType(declarationsMap.at(value));
    default:
      return StmtRefType::INVALID;
  }
}

EntRefType ParserUtil::getEntRefType(
    TokenType type, const std::string& value,
    std::unordered_map<std::string, SynonymType> declarationsMap) {
  switch (type) {
    case TokenType::WILDCARD:
      return EntRefType::WILDCARD;
    case TokenType::DOUBLE_QUOTE:
      return EntRefType::IDENT;
    case TokenType::NAME:
      return getSynonymEntType(declarationsMap.at(value));
    default:
      return EntRefType::INVALID;
  }
}

ExprSpecType ParserUtil::getExprSpecType(
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  TokenType type = (*it)->getType();
  switch (type) {
    case TokenType::DOUBLE_QUOTE:
      it++;  // move itr to expr
      return ExprSpecType::EXPR;
    case TokenType::WILDCARD: {
      TokenType nextTokenType = ((*(++it))->getType());
      if (nextTokenType == TokenType::DOUBLE_QUOTE) {
        it++;  // move itr to expr
        return ExprSpecType::WILDCARD_EXPR;
      } else {
        it--;  // move itr back to wildcard
        return ExprSpecType::WILDCARD;
      }
    }
    default:
      return ExprSpecType::INVALID;
  }
}

StmtRefType ParserUtil::getSynonymStmtType(SynonymType type) {
  return synonymStmtTypeMap.at(type);
}

std::unordered_map<SynonymType, StmtRefType> ParserUtil::synonymStmtTypeMap = {
    {SynonymType::STMT, StmtRefType::STMT},
    {SynonymType::READ, StmtRefType::READ},
    {SynonymType::PRINT, StmtRefType::PRINT},
    {SynonymType::CALL, StmtRefType::CALL},
    {SynonymType::WHILE, StmtRefType::WHILE},
    {SynonymType::IF, StmtRefType::IF},
    {SynonymType::ASSIGN, StmtRefType::ASSIGN},
    {SynonymType::VARIABLE, StmtRefType::VARIABLE},
    {SynonymType::CONSTANT, StmtRefType::CONSTANT},
    {SynonymType::PROCEDURE, StmtRefType::PROCEDURE},
};

EntRefType ParserUtil::getSynonymEntType(SynonymType type) {
  return synonymEntTypeMap.at(type);
}

std::unordered_map<SynonymType, EntRefType> ParserUtil::synonymEntTypeMap = {
    {SynonymType::STMT, EntRefType::STMT},
    {SynonymType::READ, EntRefType::READ},
    {SynonymType::PRINT, EntRefType::PRINT},
    {SynonymType::CALL, EntRefType::CALL},
    {SynonymType::WHILE, EntRefType::WHILE},
    {SynonymType::IF, EntRefType::IF},
    {SynonymType::ASSIGN, EntRefType::ASSIGN},
    {SynonymType::VARIABLE, EntRefType::VARIABLE},
    {SynonymType::CONSTANT, EntRefType::CONSTANT},
    {SynonymType::PROCEDURE, EntRefType::PROCEDURE},
};

std::vector<std::string> ParserUtil::getExpr(
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  std::vector<std::string> expression;
  while ((*it)->getType() != TokenType::DOUBLE_QUOTE) {
    expression.push_back((*it)->getValue());
    it++;
  }
  return expression;
}

void ParserUtil::skipOpenBracket(
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  it++;
}

void ParserUtil::skipComma(std::vector<std::shared_ptr<Token>>::iterator& it) {
  it += 2;
}

void ParserUtil::skipCloseBracket(
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  it += 2;
}

void ParserUtil::skipAngleBracket(
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  it++;
}
}  // namespace QPS