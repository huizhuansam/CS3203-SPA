#include "validator/syntax_validator/ClauseListValidator.h"

#include <memory>
#include <vector>

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "../src/spa/QPS/include/tokenizer/Token.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("ClauseListValidator valid scenario", "[QPS][Validator][Success]") {
  ClauseListValidator validator;

  SECTION("One such that clause") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Modifies"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("Two such that clauses") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Modifies"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Modifies"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("One such that clause and one pattern clause") {
    // todo: write these tests
  }
}

TEST_CASE("ClauseListValidator invalid scenario", "[QPS][Validator][Failure]") {
  ClauseListValidator validator;

  SECTION("Unexpected token") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "BigGorilla"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::SELECT_CL);
  }

  SECTION("such <end>") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "such"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::SUCHTHAT_CL);
  }
}
