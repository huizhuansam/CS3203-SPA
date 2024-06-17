#include "validator/syntax_validator/WithClauseValidator.h"

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("WithClauseValidator valid scenario", "[QPS][Validator][Success]") {
  WithClauseValidator validator;

  SECTION("with 1 = 1") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "with"),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }
}

TEST_CASE("WithClauseValidator invalid scenario", "[QPS][Validator][Failure]") {
  WithClauseValidator validator;

  SECTION("Empty token vector") {
    std::vector<std::shared_ptr<Token>> tokens;
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::WITH_CL);
  }

  SECTION("Missing 'with'") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::WITH_CL);
  }

  SECTION("Unexpected token") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::COMMA, ","),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::WITH_CL);
  }
}
