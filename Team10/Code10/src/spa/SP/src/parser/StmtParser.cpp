#include "StmtParser.h"

#include <memory>

#include "AssignParser.h"
#include "CallParser.h"
#include "GrammarRule.h"
#include "IfParser.h"
#include "PrintParser.h"
#include "ReadParser.h"
#include "SyntaxError.h"
#include "WhileParser.h"

namespace SP {
std::unique_ptr<StmtParser> StmtParser::of(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    std::vector<std::unique_ptr<Token>>::iterator& end) {
  // check if statement list has at least 2 tokens and the first token can be
  // either variable or reserved word
  if (it == end || (it + 1) == end || !(*it)->canBeName()) {
    throw SyntaxError(GrammarRule::STMT);
  }

  // stmt: read | print | call | while | if | assign
  std::unique_ptr<StmtParser> stmtParser;
  TokenType type = (*it)->getType();
  bool isAssign = (*(it + 1))->getType() == TokenType::ASSIGN;
  if (isAssign) {
    stmtParser = std::make_unique<AssignParser>();
    return stmtParser;
  }

  switch (type) {
    case TokenType::READ: {
      stmtParser = std::make_unique<ReadParser>();
      break;
    }
    case TokenType::PRINT: {
      stmtParser = std::make_unique<PrintParser>();
      break;
    }
    case TokenType::IF: {
      stmtParser = std::make_unique<IfParser>();
      break;
    }
    case TokenType::WHILE: {
      stmtParser = std::make_unique<WhileParser>();
      break;
    }
    case TokenType::CALL: {
      stmtParser = std::make_unique<CallParser>();
      break;
    }
    default:
      throw SyntaxError(GrammarRule::STMT);
  }

  return stmtParser;
}

void StmtParser::setProcCalled(std::string& procName) { procCalled = procName; }

std::string StmtParser::getProcCalled() { return procCalled; }
}  // namespace SP
