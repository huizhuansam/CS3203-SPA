#include "extractor/RelExprExtractor.h"

#include <memory>
#include <vector>

#include "WriteFacadeStub.h"
#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("RelExpr extractor extract valid relational factor correctly",
          "[Parser]") {
  WriteFacadeStub writer;
  RelExprExtractor extractor{writer};

  SECTION("Extract LT relational factor correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::LT, "<"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Extract GT relational factor correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::GT, ">"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Extract LTE relational factor correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::LTE, ">="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Extract GTE relational factor correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::GTE, ">="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Extract EQ relational factor correctly") {
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
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Extract NOT relational factor correctly") {
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
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }
}
