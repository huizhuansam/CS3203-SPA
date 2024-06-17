#include "parser/RelFactorParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("RelFactor parser parse valid constant correctly", "[Parser]") {
  RelFactorParser parser{};

  SECTION("Do not throw error when parsing single digit constant") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
    REQUIRE((*it)->getValue() == ";");
  }

  SECTION("Do not throw error when parsing double digits constant") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "69"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
    REQUIRE((*it)->getValue() == ")");
  }
}

TEST_CASE("RelFactor parser parse valid variable correctly", "[Parser]") {
  RelFactorParser parser{};

  SECTION(
      "Do not throw error when parsing single character "
      "variable") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "z"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
    REQUIRE((*it)->getValue() == ";");
  }

  SECTION(
      "Do not throw error when parsing multiple characters "
      "variable") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "t3slA"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
    REQUIRE((*it)->getValue() == ")");
  }

  SECTION("Do not throw error when parsing reserve word variable") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::CALL, "call"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
    REQUIRE((*it)->getValue() == ")");
  }
}

TEST_CASE("RelFactor parser parse valid expression correctly", "[Parser]") {
  RelFactorParser parser{};

  SECTION("Parse (1 + 2) correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
    REQUIRE((*it)->getValue() == ";");
  }

  SECTION("Parse ((1 + a) * b) / (3) % c correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "a"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "b"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::DIVIDE, "/"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "3"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::MODULO, "%"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "c"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
    REQUIRE((*it)->getValue() == ";");
  }
}

// Other kind of errors are handled by VariableParser, ConstantParser and
// ExprParser
