#include "validator/syntax_validator/AttrCondValidator.h"

#include <memory>
#include <vector>

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "../src/spa/QPS/include/tokenizer/Token.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("AttrCondValidator valid scenario", "[QPS][Validator][Success]") {
  AttrCondValidator validator;

  SECTION("1 = 1") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("not 1 = 1") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "not"),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("1 = 1 and \"x\" = \"x\"") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("1 = 1 and not \"x\" = \"x\"") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "not"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }
}

TEST_CASE("AttrCondValidator invalid scenario", "[QPS][Validator][Failure]") {
  AttrCondValidator validator;

  SECTION("Empty token list") {
    std::vector<std::shared_ptr<Token>> tokens = {};
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::REF);
  }

  SECTION("Unexpected token") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::REF);
  }

  SECTION("1 = 1 and not") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "not"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::REF);
  }
}
