#include "parser/CondExprParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("CondExpr parser can parse valid relational expression correctly",
          "[Parser]") {
  CondExprParser parser{};

  SECTION("Parse valid NOT condition expression correctly") {
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
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }

  SECTION("Parse valid AND condition expression correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "x")));
    tokens.push_back((std::make_unique<Token>(TokenType::EQ, "=")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "1")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back((std::make_unique<Token>(TokenType::AND, "&&")));
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "y")));
    tokens.push_back((std::make_unique<Token>(TokenType::EQ, "==")));
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "2")));
    tokens.push_back((std::make_unique<Token>(TokenType::MULTIPLY, "*")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "z")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back(
        (std::make_unique<Token>(TokenType::NAME, "endOfCondExpr")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }

  SECTION("Parse valid OR condition expression correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "y")));
    tokens.push_back((std::make_unique<Token>(TokenType::GTE, ">=")));
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "aA")));
    tokens.push_back((std::make_unique<Token>(TokenType::MODULO, "%")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "z")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back((std::make_unique<Token>(TokenType::OR, "||")));
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "x")));
    tokens.push_back((std::make_unique<Token>(TokenType::EQ, "=")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "1")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back(
        (std::make_unique<Token>(TokenType::NAME, "endOfCondExpr")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }

  SECTION("Parse valid relational expression correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "x")));
    tokens.push_back((std::make_unique<Token>(TokenType::NEQ, "!=")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "0")));
    tokens.push_back(
        (std::make_unique<Token>(TokenType::NAME, "endOfCondExpr")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }

  SECTION("Parse valid relational expression with expression correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "x")));
    tokens.push_back((std::make_unique<Token>(TokenType::MODULO, "%")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "2")));
    tokens.push_back((std::make_unique<Token>(TokenType::NEQ, "!=")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "0")));
    tokens.push_back(
        (std::make_unique<Token>(TokenType::NAME, "endOfCondExpr")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }

  SECTION(
      "Parse valid relational expression with first closing bracket expression "
      "correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "x")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back((std::make_unique<Token>(TokenType::NEQ, "!=")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "0")));
    tokens.push_back(
        (std::make_unique<Token>(TokenType::NAME, "endOfCondExpr")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }

  SECTION("Parse valid relational expression with keyword variable correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::PRINT, "print")));
    tokens.push_back((std::make_unique<Token>(TokenType::NEQ, "!=")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "0")));
    tokens.push_back(
        (std::make_unique<Token>(TokenType::NAME, "endOfCondExpr")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }
}

TEST_CASE(
    "CondExpr parser can parse nested valid conditional expression correctly") {
  CondExprParser parser{};

  SECTION("Parse nested relational expression correctly") {
    // ((x > 5) && (y <= 10)) || ( (!(x != 5)) || (z == 0) )
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "x")));
    tokens.push_back((std::make_unique<Token>(TokenType::GT, ">")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "5")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back((std::make_unique<Token>(TokenType::AND, "&&")));
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "y")));
    tokens.push_back((std::make_unique<Token>(TokenType::LTE, "<=")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "10")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back((std::make_unique<Token>(TokenType::OR, "||")));
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NOT, "!")));
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "x")));
    tokens.push_back((std::make_unique<Token>(TokenType::NEQ, "!=")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "5")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back((std::make_unique<Token>(TokenType::OR, "||")));
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "z")));
    tokens.push_back((std::make_unique<Token>(TokenType::EQ, "==")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "0")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back(
        (std::make_unique<Token>(TokenType::NAME, "endOfCondExpr")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfCondExpr");
  }
}

TEST_CASE("CondExpr parser throws error for empty condition expression") {
  CondExprParser parser{};
  std::vector<std::unique_ptr<Token>> tokens;
  auto it = tokens.begin();
  auto end = tokens.end();
  REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::COND_EXPR);
}

TEST_CASE("CondExpr parser throws error for invalid NOT conditionexpression",
          "[Parser]") {
  CondExprParser parser{};

  SECTION("Throw error for missing open bracket after NOT") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::NOT, "!")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "x")));
    tokens.push_back((std::make_unique<Token>(TokenType::EQ, "=")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "1")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::COND_EXPR);
  }

  SECTION("Throw error for missing close bracket after NOT") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::NOT, "!")));
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "x")));
    tokens.push_back((std::make_unique<Token>(TokenType::EQ, "=")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "1")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::COND_EXPR);
  }
}

TEST_CASE(
    "CondExpr parser throws error for invalid logical condition expression",
    "[Parser]") {
  CondExprParser parser{};

  SECTION("Throw error for missing close bracket before AND") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "x")));
    tokens.push_back((std::make_unique<Token>(TokenType::EQ, "==")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "1")));
    tokens.push_back((std::make_unique<Token>(TokenType::AND, "&&")));
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "y")));
    tokens.push_back((std::make_unique<Token>(TokenType::EQ, "==")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "2")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::COND_EXPR);
  }

  SECTION("Throw error for missing open bracket after OR") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "x")));
    tokens.push_back((std::make_unique<Token>(TokenType::EQ, "=")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "1")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back((std::make_unique<Token>(TokenType::OR, "||")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "y")));
    tokens.push_back((std::make_unique<Token>(TokenType::EQ, "=")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "2")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::COND_EXPR);
  }

  SECTION("Throw error for missing close bracket after AND") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "x")));
    tokens.push_back((std::make_unique<Token>(TokenType::EQ, "=")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "1")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back((std::make_unique<Token>(TokenType::AND, "&&")));
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "y")));
    tokens.push_back((std::make_unique<Token>(TokenType::EQ, "=")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "2")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::COND_EXPR);
  }
}

// invalid relational expression will be handled by RelExprParser
