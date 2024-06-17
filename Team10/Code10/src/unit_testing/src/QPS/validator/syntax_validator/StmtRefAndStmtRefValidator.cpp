#include "validator/syntax_validator/StmtRefAndStmtRefValidator.h"

#include <memory>
#include <vector>

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "../src/spa/QPS/include/tokenizer/Token.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("StmtRefAndStmtRefValidator valid scenario",
          "[QPS][Validator][Success]") {
  StmtRefAndStmtRefValidator validator;

  SECTION("Valid arg list with synonym on left and synonym on right") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::NAME, "endOfArgsList"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfArgsList");
  }

  SECTION("Valid arg list with synonym on left and wildcard on right") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::NAME, "endOfArgsList"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfArgsList");
  }

  SECTION("Valid arg list with synonym on left and integer on right") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::NAME, "endOfArgsList"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfArgsList");
  }

  SECTION("Valid arg list with wildcard on left and synonym on right") {
    // Note that this is semantically invalid but syntactically valid
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::NAME, "endOfArgsList"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfArgsList");
  }

  SECTION("Valid arg list with wildcard on left and wildcard on right") {
    // Note that this is semantically invalid but syntactically valid
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::NAME, "endOfArgsList"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfArgsList");
  }

  SECTION("Valid arg list with wildcard on left and integer on right") {
    // Note that this is semantically invalid but syntactically valid
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::NAME, "endOfArgsList"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfArgsList");
  }

  SECTION("Valid arg list with integer on left and synonym on right") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::NAME, "endOfArgsList"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfArgsList");
  }

  SECTION("Valid arg list with integer on left and wildcard on right") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::NAME, "endOfArgsList"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfArgsList");
  }

  SECTION("Valid arg list with integer on left and integer on right") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::NAME, "endOfArgsList"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfArgsList");
  }

  SECTION("Valid arg list with integer on left and synonym on right") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::NAME, "endOfArgsList"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfArgsList");
  }

  SECTION("Valid arg list with integer on left and wildcard on right") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::NAME, "endOfArgsList"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfArgsList");
  }

  SECTION("Valid arg list with integer on left and integer on right") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::INTEGER, "4"),
        std::make_shared<Token>(TokenType::NAME, "endOfArgsList"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfArgsList");
  }
}