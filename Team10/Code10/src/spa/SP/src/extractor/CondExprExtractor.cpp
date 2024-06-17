#include "CondExprExtractor.h"

#include "GrammarRule.h"
#include "RelExprExtractor.h"
#include "SyntaxError.h"
#include "WriteFacade.h"

namespace SP {
CondExprExtractor::CondExprExtractor(WriteFacade& writer) : writer(writer) {}

std::unordered_set<std::string> CondExprExtractor::getVarUsed() {
  return this->varUsed;
}

void CondExprExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  TokenType currentTokenType = (*it)->getType();
  auto firstCondExprToken = it;
  if (currentTokenType == TokenType::NOT) {
    // consume NOT
    it++;

    // consume open bracket
    it++;

    // consume condition expression
    extract(it, end);

    // consume close bracket
    it++;
  } else if (currentTokenType == TokenType::OPEN_BRACKET &&
             isOpenBracketOfCondExpr(it)) {
    // consume open bracket
    it++;

    // consume condition expression
    extract(it, end);

    // consume close bracket
    it++;

    // consume 'AND' or 'OR
    it++;

    // consume open bracket
    it++;

    // consume condition expression
    extract(it, end);

    // consume close bracket
    it++;
  } else {
    RelExprExtractor relExprExtractor{writer};
    relExprExtractor.extract(it, end);
  }

  // add all variables used in the condition expression
  auto lastCondExprToken = it;

  while (firstCondExprToken != lastCondExprToken) {
    auto& t = *firstCondExprToken;

    if (t->canBeName()) {
      this->varUsed.insert(t->getValue());
    }
    firstCondExprToken++;
  }
}

bool CondExprExtractor::isOpenBracketOfCondExpr(
    const std::vector<std::unique_ptr<Token>>::iterator& it) {
  int numOpenBrackets = 1;
  auto checkIt = it + 1;

  while (numOpenBrackets > 0) {
    if ((*checkIt)->getType() == TokenType::OPEN_BRACKET) {
      numOpenBrackets++;
    } else if ((*checkIt)->getType() == TokenType::CLOSE_BRACKET) {
      numOpenBrackets--;
    } else if ((*checkIt)->getType() == TokenType::GT ||
               (*checkIt)->getType() == TokenType::LT ||
               (*checkIt)->getType() == TokenType::GTE ||
               (*checkIt)->getType() == TokenType::LTE ||
               (*checkIt)->getType() == TokenType::EQ ||
               (*checkIt)->getType() == TokenType::NEQ) {
      return true;
    }
    checkIt++;
  }

  return false;
}
}  // namespace SP
