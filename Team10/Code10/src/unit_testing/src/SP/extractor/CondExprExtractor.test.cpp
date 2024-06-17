#include "extractor/CondExprExtractor.h"

#include <memory>
#include <vector>

#include "WriteFacadeStub.h"
#include "catch.hpp"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE(
    "CondExpr extractor can extract valid relational expression correctly",
    "[Extractor]") {
  WriteFacadeStub writer{};
  CondExprExtractor extractor{writer};

  SECTION("Extract valid NOT condition expression correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NOT, "!"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::EQ, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfCondExpr"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }

  SECTION("Extract valid AND condition expression correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::EQ, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::AND, "&&"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "z"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfCondExpr"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }

  SECTION("Extract valid OR condition expression correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::GTE, ">="));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "aA"));
    tokens.push_back(std::make_unique<Token>(TokenType::MODULO, "%"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "z"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::OR, "||"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::EQ, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfCondExpr"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }

  SECTION("Extract valid relational expression correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfCondExpr"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }

  SECTION("Extract valid relational expression with expression correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::MODULO, "%"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfCondExpr"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }

  SECTION(
      "Extract valid relational expression with first closing bracket "
      "expression "
      "correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfCondExpr"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }

  SECTION(
      "Extract valid relational expression with keyword variable correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfCondExpr"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }
}

TEST_CASE(
    "CondExpr Extract can parse nested valid conditional expression "
    "correctly") {
  WriteFacadeStub writer{};
  CondExprExtractor extractor{writer};

  SECTION("Extract nested relational expression correctly") {
    // ((x > 5) && (y <= 10)) || ( (!(x != 5)) || (z == 0) )
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::GT, ">"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "5"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::AND, "&&"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::LTE, "<="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "10"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::OR, "||"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NOT, "!"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "5"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::OR, "||"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "z"));
    tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfCondExpr"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }
}
