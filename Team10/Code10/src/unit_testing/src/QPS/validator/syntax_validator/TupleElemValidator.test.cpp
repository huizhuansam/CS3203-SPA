#include "validator/syntax_validator/TupleElemValidator.h"

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("TupleElemValidator valid scenario", "[QPS][Validator][Success]") {
  TupleElemValidator validator;

  SECTION("Single synonym") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::NAME, "endOfElem"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfElem");
  }

  SECTION("Single synonym with attribute") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "stmt#"),
        std::make_shared<Token>(TokenType::NAME, "endOfElem"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfElem");
  }
}

TEST_CASE("TupleElemValidator invalid scenario", "[QPS][Validator][Failure]") {
  TupleElemValidator validator;

  SECTION("Empty token vector") {
    std::vector<std::shared_ptr<Token>> tokens{};
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::TUPLE);
  }

  SECTION("Unexpected token") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::COMMA, ","),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::TUPLE);
  }

  SECTION("Single synonym with no token after '.'") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::ATTR_NAME);
  }

  SECTION("Single synonym with unexpected token after '.'") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::NAME, "b"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::ATTR_NAME);
  }
}
