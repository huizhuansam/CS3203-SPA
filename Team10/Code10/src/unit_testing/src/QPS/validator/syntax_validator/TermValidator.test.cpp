#include "validator/syntax_validator/TermValidator.h"

#include <memory>
#include <vector>

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "../src/spa/QPS/include/tokenizer/Token.h"
#include "../src/spa/QPS/include/tokenizer/TokenType.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("TermValidator validate single valid term correctly",
          "[QPS][Validator][Success]") {
  TermValidator validator;

  SECTION("Validate x * 0 correctly") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::TIMES, "*"),
        std::make_shared<Token>(TokenType::INTEGER, "0"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
  }

  SECTION("Validate divide: 9 / y correctly") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::INTEGER, "9"),
        std::make_shared<Token>(TokenType::DIV, "/"),
        std::make_shared<Token>(TokenType::NAME, "y"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
  }

  SECTION("Validate modulo: z % 2 correctly") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::INTEGER, "z"),
        std::make_shared<Token>(TokenType::MOD, "%"),
        std::make_shared<Token>(TokenType::NAME, "2"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
  }
}

TEST_CASE("Term validator validate double valid term correctly",
          "[QPS][Validator][Success]") {
  TermValidator validator;

  SECTION("Validate x * 0 / 1 correctly") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::TIMES, "*"),
        std::make_shared<Token>(TokenType::INTEGER, "0"),
        std::make_shared<Token>(TokenType::DIV, "/"),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Validate x * 1 % y correctly") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::MOD, "*"),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::MOD, "%"),
        std::make_shared<Token>(TokenType::NAME, "y"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),

    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Validate 9 / y * 6 correctly") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::INTEGER, "9"),
        std::make_shared<Token>(TokenType::DIV, "/"),
        std::make_shared<Token>(TokenType::NAME, "y"),
        std::make_shared<Token>(TokenType::TIMES, "*"),
        std::make_shared<Token>(TokenType::INTEGER, "6"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),

    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Validate 8 / z % 6 correctly") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::INTEGER, "8"),
        std::make_shared<Token>(TokenType::DIV, "/"),
        std::make_shared<Token>(TokenType::NAME, "z"),
        std::make_shared<Token>(TokenType::MOD, "%"),
        std::make_shared<Token>(TokenType::INTEGER, "6"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),

    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Validate z % 2 * 10 correctly") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::INTEGER, "z"),
        std::make_shared<Token>(TokenType::MOD, "%"),
        std::make_shared<Token>(TokenType::INTEGER, "2"),
        std::make_shared<Token>(TokenType::TIMES, "*"),
        std::make_shared<Token>(TokenType::INTEGER, "10"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),

    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Validate 3 % x * z correctly") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::MOD, "%"),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::TIMES, "*"),
        std::make_shared<Token>(TokenType::NAME, "z"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),

    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }
}

TEST_CASE("Term validator validate complex valid term correctly",
          "[QPS][Validator][Success]") {
  TermValidator validator;

  SECTION("Validate ((a * 2) + (3 - b)) / (c % d) correctly") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::MOD, "*"),
        std::make_shared<Token>(TokenType::INTEGER, "2"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::MINUS, "-"),
        std::make_shared<Token>(TokenType::NAME, "b"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::DIV, "/"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "c"),
        std::make_shared<Token>(TokenType::MOD, "%"),
        std::make_shared<Token>(TokenType::NAME, "d"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "endOfTerm"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfTerm");
  }
}
