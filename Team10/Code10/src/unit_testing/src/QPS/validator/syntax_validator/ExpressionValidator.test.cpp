#include "validator/syntax_validator/ExpressionValidator.h"

#include <memory>
#include <vector>

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "../src/spa/QPS/include/tokenizer/Token.h"
#include "../src/spa/QPS/include/tokenizer/TokenType.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("Expression validator validate single valid expression correctly",
          "[QPS][Validator][Success]") {
  ExpressionValidator validator;

  SECTION("Validate multiply: x + 0 correctly") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::INTEGER, "0"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
  }

  SECTION("Validate divide: 9 - y correctly") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::INTEGER, "9"),
        std::make_shared<Token>(TokenType::MINUS, "-"),
        std::make_shared<Token>(TokenType::NAME, "y"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
  }
}

TEST_CASE("Expression validator validate double valid expression correctly",
          "[QPS][Validator][Success]") {
  ExpressionValidator validator;

  SECTION("Validate x + 0 - 1 correctly") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::INTEGER, "0"),
        std::make_shared<Token>(TokenType::MINUS, "-"),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Validate 9 - y + 6 correctly") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::INTEGER, "9"),
        std::make_shared<Token>(TokenType::MINUS, "-"),
        std::make_shared<Token>(TokenType::NAME, "y"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::INTEGER, "6"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),

    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }
}

TEST_CASE("Expression validator validate complex valid expression correctly",
          "[QPS][Validator][Success]") {
  ExpressionValidator validator;

  SECTION("Validate ((3 * x) + (y / 2)) - ((z - 1) % 4) correctly") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::TIMES, "*"),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "y"),
        std::make_shared<Token>(TokenType::DIV, "/"),
        std::make_shared<Token>(TokenType::INTEGER, "2"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::MINUS, "-"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "z"),
        std::make_shared<Token>(TokenType::MINUS, "-"),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::MOD, "%"),
        std::make_shared<Token>(TokenType::INTEGER, "4"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
  }
}
