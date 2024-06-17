#include "validator/syntax_validator/FactorValidator.h"

#include <memory>
#include <vector>

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "../src/spa/QPS/include/tokenizer/Token.h"
#include "../src/spa/QPS/include/tokenizer/TokenType.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("Factor validator validate valid constant correctly",
          "[QPS][Validator][Success]") {
  FactorValidator validator{};

  SECTION("Do not throw error when parsing single digit constant") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::INTEGER, "1")};
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Do not throw error when parsing double digits constant") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::INTEGER, "69")};
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Points to correct token after parsing constant") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::INTEGER, "2"),
        std::make_shared<Token>(TokenType::TIMES, "*"),
        std::make_shared<Token>(TokenType::INTEGER, "2"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    validator.validate(it, end);
    REQUIRE((*it)->getType() == TokenType::TIMES);
    REQUIRE((*it)->getValue() == "*");
  }
}

TEST_CASE("Factor validator validate valid variable correctly",
          "[QPS][Validator][Success]") {
  FactorValidator validator{};

  SECTION(
      "Do not throw error when parsing single character "
      "variable") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "z")};
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION(
      "Do not throw error when parsing multiple characters "
      "variable") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "t3slA")};
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Points to correct token after parsing variable") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "xYz"),
        std::make_shared<Token>(TokenType::DIV, "/"),
        std::make_shared<Token>(TokenType::INTEGER, "2"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    validator.validate(it, end);
    REQUIRE((*it)->getType() == TokenType::DIV);
    REQUIRE((*it)->getValue() == "/");
  }
}

TEST_CASE("Factor validator validate valid expression correctly",
          "[QPS][Validator][Success]") {
  FactorValidator validator{};

  SECTION("Do not throw error when parsing valid expression") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::NAME, "b"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Do not throw error when parsing nested expression") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::NAME, "b"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Points to correct token after parsing expression") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::MOD, "%"),
        std::make_shared<Token>(TokenType::INTEGER, "2"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    validator.validate(it, end);
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
    REQUIRE((*it)->getValue() == ";");
  }
}

TEST_CASE("FactorValidator throws error for invalid factor",
          "[QPS][Validator][Success]") {
  FactorValidator validator{};

  SECTION("Throws error when the first token is non-factor") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::FACTOR);
  }

  SECTION("Throws error when no corresponding close bracket ") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::FACTOR);
  }

  SECTION("Throws error when missing close bracket for expression") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::FACTOR);
  }
}
