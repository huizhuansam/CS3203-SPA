#include "validator/syntax_validator/SuchThatClauseValidator.h"

#include <memory>
#include <vector>

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "../src/spa/QPS/include/tokenizer/Token.h"
#include "../src/spa/QPS/include/tokenizer/TokenType.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("SuchThatClauseValidator valid scenario",
          "[QPS][Validator][Success]") {
  SuchThatClauseValidator validator;
  SECTION("Valid such that clause") {
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
  }
}

TEST_CASE("SuchThatClauseValidator invalid scenario",
          "[QPS][Validator][Failure]") {
  SuchThatClauseValidator validator;
  SECTION("Invalid such that <end>") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::REL_REF);
  }
}
