#include "parser/RelExprParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("RelExpr parser parse valid relational factor correctly",
          "[Parser]") {
  RelExprParser parser{};

  SECTION("Parse LT relational factor correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::LT, "<"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Parse GT relational factor correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::GT, ">"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Parse LTE relational factor correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::LTE, ">="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Parse GTE relational factor correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::GTE, ">="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Parse EQ relational factor correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "hello"));
    tokens.push_back(std::make_unique<Token>(TokenType::MODULO, "*"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "world"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Parse NOT relational factor correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::MODULO, "%"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }
}

TEST_CASE(
    "RelExpr Parser throws error when parsing invalid relational expression",
    "[Parser]") {
  RelExprParser parser{};

  SECTION("Throw error when no relational operator") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "y"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::REL_EXPR);
  }
}

// Other kind of errors are handled by RelFactorParser
