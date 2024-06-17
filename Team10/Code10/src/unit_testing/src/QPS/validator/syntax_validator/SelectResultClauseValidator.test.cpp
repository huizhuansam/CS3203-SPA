#include "validator/syntax_validator/SelectResultClauseValidator.h"

#include <memory>
#include <vector>

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "../src/spa/QPS/include/tokenizer/Token.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("SelectResultClauseValidator valid scenario",
          "[QPS][Validator][Success]") {
  SelectResultClauseValidator validator;

  SECTION("Valid select synonym") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::NAME, "endOfSelect"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfSelect");
  }

  SECTION("Valid select synonym with synonym name of keyword") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "endOfSelect"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfSelect");
  }

  SECTION("Valid select BOOLEAN") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
        std::make_shared<Token>(TokenType::NAME, "endOfSelect"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfSelect");
  }

  SECTION("Valid select BOOLEAN.varName") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "varName"),
        std::make_shared<Token>(TokenType::NAME, "endOfSelect"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfSelect");
  }

  SECTION("Valid select tuple with single synonym") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::CLOSE_ANGLE_BRACKET, ">"),
        std::make_shared<Token>(TokenType::NAME, "endOfSelect"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfSelect");
  }

  SECTION("Valid select tuple with two synonyms") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "b"),
        std::make_shared<Token>(TokenType::CLOSE_ANGLE_BRACKET, ">"),
        std::make_shared<Token>(TokenType::NAME, "endOfSelect"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfSelect");
  }

  SECTION("Valid select tuple with three synonyms") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "b"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "c"),
        std::make_shared<Token>(TokenType::CLOSE_ANGLE_BRACKET, ">"),
        std::make_shared<Token>(TokenType::NAME, "endOfSelect"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfSelect");
  }
}

TEST_CASE("SelectResultClauseValidator invalid scenario",
          "[QPS][Validator][Failure]") {
  SelectResultClauseValidator validator;

  SECTION("Empty token vector") {
    std::vector<std::shared_ptr<Token>> tokens = {};
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::SELECT_CL);
  }

  SECTION("Invalid select with unknown token") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "VERYBIGGORILLA"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::SELECT_CL);
  }

  SECTION("Invalid select with no synonym") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "Select"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::TUPLE);
  }

  SECTION("Invalid select with invalid token") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::COMMA, ","),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::TUPLE);
  }
}
