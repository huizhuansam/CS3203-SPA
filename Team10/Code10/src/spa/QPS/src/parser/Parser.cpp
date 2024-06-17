#include "parser/Parser.h"

namespace QPS {
std::unordered_map<std::string, SynonymType> Parser::declarationTypeMap = {};

std::vector<std::shared_ptr<Strategy>> Parser::parse(
    std::vector<std::shared_ptr<Token>>& tokens) {
  auto it = tokens.begin();
  const auto end = tokens.end();

  declarationTypeMap.clear();
  declarationTypeMap = DeclarationParser::parse(it, end);

  std::vector<std::shared_ptr<Strategy>> strategies;
  parseSelect(it, end, strategies);
  parseClauses(it, end, strategies);
  return strategies;
}

SynonymType Parser::getDeclarationType(const std::string& synonym) {
  return declarationTypeMap.at(synonym);
}

void Parser::parseSelect(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end,
    std::vector<std::shared_ptr<Strategy>>& strategies) {
  TokenType resultClType = (*(++it))->getType();
  bool isNameToken = resultClType == TokenType::NAME;
  std::string resultClValue = (*it)->getValue();
  bool isBoolean =
      isNameToken && resultClValue == "BOOLEAN" &&
      declarationTypeMap.find(resultClValue) == declarationTypeMap.end();

  if (isBoolean) {
    strategies.push_back(SelectParser::parseBooleanSelect(it));
  } else {
    strategies.push_back(
        SelectParser::parseTupleSelect(it, end, declarationTypeMap));
  }
}

void Parser::parseClauses(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end,
    std::vector<std::shared_ptr<Strategy>>& strategies) {
  while (it != end) {
    if ((*it)->getValue() == "such") {
      it++;  // move itr to 'that'
      do {
        parseSuchThat(++it, strategies);
      } while (isSameClauseType(it, end));
    } else if ((*it)->getValue() == "pattern") {
      do {
        parsePattern(++it, strategies);
      } while (isSameClauseType(it, end));
    } else if ((*it)->getValue() == "with") {
      do {
        parseWith(++it, strategies);
      } while (isSameClauseType(it, end));
    }
  }
}

void Parser::parseSuchThat(std::vector<std::shared_ptr<Token>>::iterator& it,
                           std::vector<std::shared_ptr<Strategy>>& strategies) {
  // check if there is 'not' before clause
  bool isNegatedClause = isNot(it);

  const std::string relRef = (*it)->getValue();
  auto parseRelRef = parserMap.find(relRef);
  if (parseRelRef != parserMap.end()) {
    parseRelRef->second(it, strategies);
  }

  if (isNegatedClause) {
    strategies.back()->setIsNotStrategy();
  }
}

std::unordered_map<
    std::string,
    std::function<void(std::vector<std::shared_ptr<Token>>::iterator&,
                       std::vector<std::shared_ptr<Strategy>>&)>>
    Parser::
        parserMap =
            {
                {"Modifies",
                 [](std::vector<std::shared_ptr<Token>>::iterator& it,
                    std::vector<std::shared_ptr<Strategy>>& strategies) {
                   parseModifies(it, strategies);
                 }},
                {"Uses",
                 [](std::vector<std::shared_ptr<Token>>::iterator& it,
                    std::vector<std::shared_ptr<Strategy>>& strategies) {
                   parseUses(it, strategies);
                 }},
                {"Follows",
                 [](std::vector<std::shared_ptr<Token>>::iterator& it,
                    std::vector<std::shared_ptr<Strategy>>& strategies) {
                   strategies.push_back(StmtStmtParser::parse(
                       StrategyType::FOLLOWS, ++it, declarationTypeMap));
                 }},
                {"Follows*",
                 [](std::vector<std::shared_ptr<Token>>::iterator& it,
                    std::vector<std::shared_ptr<Strategy>>& strategies) {
                   strategies.push_back(StmtStmtParser::parse(
                       StrategyType::FOLLOWS_T, ++it, declarationTypeMap));
                 }},
                {"Parent",
                 [](std::vector<std::shared_ptr<Token>>::iterator& it,
                    std::vector<std::shared_ptr<Strategy>>& strategies) {
                   strategies.push_back(StmtStmtParser::parse(
                       StrategyType::PARENT, ++it, declarationTypeMap));
                 }},
                {"Parent*",
                 [](std::vector<std::shared_ptr<Token>>::iterator& it,
                    std::vector<std::shared_ptr<Strategy>>& strategies) {
                   strategies.push_back(StmtStmtParser::parse(
                       StrategyType::PARENT_T, ++it, declarationTypeMap));
                 }},
                {"Calls",
                 [](std::vector<std::shared_ptr<Token>>::iterator& it,
                    std::vector<std::shared_ptr<Strategy>>& strategies) {
                   strategies.push_back(EntEntParser::parse(
                       StrategyType::CALLS, ++it, declarationTypeMap));
                 }},
                {"Calls*",
                 [](std::vector<std::shared_ptr<Token>>::iterator& it,
                    std::vector<std::shared_ptr<Strategy>>& strategies) {
                   strategies.push_back(EntEntParser::parse(
                       StrategyType::CALLS_T, ++it, declarationTypeMap));
                 }},
                {"Next",
                 [](std::vector<std::shared_ptr<Token>>::iterator& it,
                    std::vector<std::shared_ptr<Strategy>>& strategies) {
                   strategies.push_back(StmtStmtParser::parse(
                       StrategyType::NEXT, ++it, declarationTypeMap));
                 }},
                {"Next*",
                 [](std::vector<std::shared_ptr<Token>>::iterator& it,
                    std::vector<std::shared_ptr<Strategy>>& strategies) {
                   strategies.push_back(StmtStmtParser::parse(
                       StrategyType::NEXT_T, ++it, declarationTypeMap));
                 }},
                {"Affects",
                 [](std::vector<std::shared_ptr<Token>>::iterator& it,
                    std::vector<std::shared_ptr<Strategy>>& strategies) {
                   strategies.push_back(StmtStmtParser::parse(
                       StrategyType::AFFECTS, ++it, declarationTypeMap));
                 }},
};

void Parser::parseModifies(std::vector<std::shared_ptr<Token>>::iterator& it,
                           std::vector<std::shared_ptr<Strategy>>& strategies) {
  it += 2;  // point to arg1
  if (isProcedure(it)) {
    strategies.push_back(EntEntParser::parse(StrategyType::MODIFIES_P, --it,
                                             declarationTypeMap));
  } else {
    strategies.push_back(StmtEntParser::parse(StrategyType::MODIFIES_S, --it,
                                              declarationTypeMap));
  }
}

void Parser::parseUses(std::vector<std::shared_ptr<Token>>::iterator& it,
                       std::vector<std::shared_ptr<Strategy>>& strategies) {
  it += 2;  // point to arg1
  if (isProcedure(it)) {
    strategies.push_back(
        EntEntParser::parse(StrategyType::USES_P, --it, declarationTypeMap));
  } else {
    strategies.push_back(
        StmtEntParser::parse(StrategyType::USES_S, --it, declarationTypeMap));
  }
}

bool Parser::isProcedure(std::vector<std::shared_ptr<Token>>::iterator& it) {
  if ((*it)->getType() == TokenType::NAME) {
    SynonymType type = declarationTypeMap.at((*it)->getValue());
    return type == SynonymType::PROCEDURE;
  }
  return (*it)->getType() == TokenType::DOUBLE_QUOTE;
}

void Parser::parsePattern(std::vector<std::shared_ptr<Token>>::iterator& it,
                          std::vector<std::shared_ptr<Strategy>>& strategies) {
  // check if there is 'not' before clause
  bool isNegatedClause = isNot(it);

  SynonymType synType = declarationTypeMap.at((*it)->getValue());
  if (synType == SynonymType::ASSIGN) {
    strategies.push_back(PatternParser::parse(StrategyType::ASSIGN_PATTERN, it,
                                              declarationTypeMap));
  } else if (synType == SynonymType::IF) {
    strategies.push_back(
        PatternParser::parse(StrategyType::IF_PATTERN, it, declarationTypeMap));
  } else {
    strategies.push_back(PatternParser::parse(StrategyType::WHILE_PATTERN, it,
                                              declarationTypeMap));
  }

  if (isNegatedClause) {
    strategies.back()->setIsNotStrategy();
  }
}

void Parser::parseWith(std::vector<std::shared_ptr<Token>>::iterator& it,
                       std::vector<std::shared_ptr<Strategy>>& strategies) {
  // check if there is 'not' before clause
  bool isNegatedClause = isNot(it);

  strategies.push_back(WithParser{}.parse(it, declarationTypeMap));

  if (isNegatedClause) {
    strategies.back()->setIsNotStrategy();
  }
}

bool Parser::isSameClauseType(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  return it != end && ((*it)->getValue() == "and");
}

bool Parser::isNot(std::vector<std::shared_ptr<Token>>::iterator& it) {
  return ((*it)->getValue() == "not") && (++it, true);
}
}  // namespace QPS
