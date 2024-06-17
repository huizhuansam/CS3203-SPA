#include "validator/syntax_validator/DeclarationListValidator.h"

#include <memory>
#include <vector>

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "../src/spa/QPS/include/tokenizer/Token.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("DeclarationListValidator valid scenario",
          "[QPS][Validator][Success]") {
  DeclarationListValidator validator;

  SECTION("Valid declaration list with one design entity and one synonym") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "Select");
  }

  SECTION(
      "Valid declaration list with one design entity and multiple synonyms") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "b"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "Select");
  }

  SECTION("Valid declaration list with two design entities") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "print"),
        std::make_shared<Token>(TokenType::NAME, "b"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "Select");
  }

  SECTION(
      "Valid declaration list with two design entities and multiple synonyms") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "b"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "print"),
        std::make_shared<Token>(TokenType::NAME, "c"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "d"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "Select");
  }
}

TEST_CASE("DeclarationListValidator invalid scenario",
          "[QPS][Validator][Failure]") {
  DeclarationListValidator validator;

  SECTION("Empty token vector") {
    std::vector<std::shared_ptr<Token>> tokens = {};
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::DECLARATION);
  }

  SECTION("Invalid declaration list with incorrect declaration separator") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "print"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "read"),
        std::make_shared<Token>(TokenType::NAME, "b"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::DECLARATION);
  }

  SECTION("Invalid declaration list with no final semicolon") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "print"),
        std::make_shared<Token>(TokenType::NAME, "a"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::DECLARATION);
  }
}
