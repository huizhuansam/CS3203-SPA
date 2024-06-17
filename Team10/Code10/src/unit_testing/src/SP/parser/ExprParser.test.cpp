#include "parser/ExprParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("Expression parser parse single valid expression correctly",
          "[Parser]") {
  ExprParser parser{};

  SECTION("Parse multiply: x + 0 correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
  }

  SECTION("Parse divide: 9 - y correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "9"));
    tokens.push_back(std::make_unique<Token>(TokenType::MINUS, "-"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
  }
}

TEST_CASE("Expression parser parse double valid expression correctly",
          "[Parser]") {
  ExprParser parser{};

  SECTION("Parse x + 0 - 1 correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::MINUS, "-"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Parse 9 - y + 6 correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "9"));
    tokens.push_back(std::make_unique<Token>(TokenType::MINUS, "-"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "6"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }
}

TEST_CASE("Expression parser parse complex valid expression correctly",
          "[Parser]") {
  ExprParser parser{};

  SECTION("Parse ((3 * x) + (y / 2)) - ((z - 1) % 4) correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "3"));
    tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::DIVIDE, "/"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::MINUS, "-"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "z"));
    tokens.push_back(std::make_unique<Token>(TokenType::MINUS, "-"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::MODULO, "%"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "4"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
  }
}

// Other kind of errors are handled by TermParser
