#include "validator/syntax_validator/EntOrStmtRefValidator.h"

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "../src/spa/QPS/include/tokenizer/Token.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("EntOrStmtRefValidator valid scenario", "[QPS][Validator][Success]") {
  EntOrStmtRefValidator validator;

  SECTION("Name token") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::NAME, "endOfEntRef"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfEntRef");
  }

  SECTION("Wildcard token") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::NAME, "endOfEntRef"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfEntRef");
  }

  SECTION("\"IDENT\" token") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "endOfEntRef"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfEntRef");
  }

  SECTION("Integer token") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::NAME, "endOfStmtRef"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfStmtRef");
  }
}

TEST_CASE("EntOrStmtRefValidator invalid scenario",
          "[QPS][Validator][Failure]") {
  EntOrStmtRefValidator validator;

  SECTION("Empty token list") {
    std::vector<std::shared_ptr<Token>> tokens = {};
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::REL_REF);
  }

  SECTION("Unexpected token") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::NAME);
  }

  SECTION("Incomplete \"IDENT token") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "v"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::NAME);
  }

  SECTION("Incomplete IDENT\" token") {
    // Although not valid, this will not throw an exception here
    // Will be caught by the caller
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }
}
