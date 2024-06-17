#include "parser/FactorParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("Factor parser parse valid constant correctly", "[Parser]") {
  FactorParser parser{};

  SECTION("Do not throw error when parsing single digit constant") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
  }

  SECTION("Do not throw error when parsing double digits constant") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "69")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
  }

  SECTION("Points to correct token after parsing constant") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    parser.parse(it, end);
    REQUIRE((*it)->getType() == TokenType::MULTIPLY);
    REQUIRE((*it)->getValue() == "*");
  }
}

TEST_CASE("Factor parser parse valid variable correctly", "[Parser]") {
  FactorParser parser{};

  SECTION(
      "Do not throw error when parsing single character "
      "variable") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "z"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
  }

  SECTION(
      "Do not throw error when parsing multiple characters "
      "variable") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "t3slA"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
  }

  SECTION("Do not throw error when parsing reserve word as variable") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
  }

  SECTION("Points to correct token after parsing variable") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "xYz"));
    tokens.push_back(std::make_unique<Token>(TokenType::DIVIDE, "/"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    parser.parse(it, end);
    REQUIRE((*it)->getType() == TokenType::DIVIDE);
    REQUIRE((*it)->getValue() == "/");
  }
}

TEST_CASE("Factor parser parse valid expression correctly", "[Parser]") {
  FactorParser parser{};

  SECTION("Do not throw error when parsing valid expression") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "a"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "b"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
  }

  SECTION("Do not throw error when parsing nested expression") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "a"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "b"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
  }

  SECTION("Points to correct token after parsing expression") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::MODULO, "%"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    parser.parse(it, end);
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
    REQUIRE((*it)->getValue() == ";");
  }
}

TEST_CASE("Throws error for invalid factor", "[Parser]") {
  FactorParser parser{};

  SECTION("Throws error when the first token is non-factor") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "a"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::FACTOR);
  }

  SECTION("Throws error when no corresponding close bracket ") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "a"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::FACTOR);
  }

  SECTION(
      "Throws error when missing close bracket for "
      "expression") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "a"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::FACTOR);
  }
}
