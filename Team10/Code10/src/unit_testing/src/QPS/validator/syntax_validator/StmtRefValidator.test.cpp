#include "validator/syntax_validator/StmtRefValidator.h"

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "../src/spa/QPS/include/tokenizer/Token.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("StmtRef valid scenario", "[QPS][Validator][Success]") {
  StmtRefValidator validator;

  SECTION("Name token") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::NAME, "endOfStmtRef"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfStmtRef");
  }

  SECTION("Wildcard token") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::NAME, "endOfStmtRef"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfStmtRef");
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

TEST_CASE("StmtRef invalid scenario", "[QPS][Validator][Failure]") {
  StmtRefValidator validator;

  SECTION("Empty token list") {
    std::vector<std::shared_ptr<Token>> tokens = {};
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::NAME);
  }

  SECTION("Unexpected token") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::NAME);
  }
}
