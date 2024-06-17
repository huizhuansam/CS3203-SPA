#include "validator/syntax_validator/AttrRefValidator.h"

#include <memory>
#include <vector>

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "../src/spa/QPS/include/tokenizer/Token.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("AttrRefValidator valid scenario", "[QPS][Validator][Success]") {
  AttrRefValidator validator;

  std::vector<std::shared_ptr<Token>> tokens = {
      std::make_shared<Token>(TokenType::NAME, "x"),
      std::make_shared<Token>(TokenType::PERIOD, "."),
      std::make_shared<Token>(TokenType::ATTR_NAME, "procName"),
  };

  auto it = tokens.begin();
  auto end = tokens.end();
  REQUIRE_NOTHROW(validator.validate(it, end));
  REQUIRE(it == end);
}

TEST_CASE("AttrRefValidator invalid scenario", "[QPS][Validator][Failure]") {
  AttrRefValidator validator;

  SECTION("Unexpected token") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::REF);
  }

  SECTION("name <end>") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "x"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::REF);
  }

  SECTION("name. <end>") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::REF);
  }
}
