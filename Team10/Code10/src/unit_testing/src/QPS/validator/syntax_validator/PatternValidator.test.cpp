#include "validator/syntax_validator/PatternValidator.h"

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("PatternValidator valid scenario", "[QPS][Validator][Success]") {
  PatternValidator validator;

  SECTION("a(a, \"1 + 1\")") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "1"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::NAME, "1"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("a(a, _\"1 + 1\"_)") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "1"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::NAME, "1"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("a(a, _)") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("a(_, \"1 + 1\")") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "1"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::NAME, "1"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("a(_, _\"1 + 1\"_)") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "1"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::NAME, "1"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("a(_, _)") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("a(\"a\", \"1 + 1\")") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "1"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::NAME, "1"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("a(\"a\", _\"1 + 1\"_)") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "1"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::NAME, "1"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("a(\"a\", _)") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("i(a, _, _)") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "i"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("i(_, _, _)") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "i"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("i(\"a\", _, _)") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "i"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("w(a, _)") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("w(_, _)") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }

  SECTION("w(\"a\", _)") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE(it == end);
  }
}

TEST_CASE("PatternValidator invalid scenario", "[QPS][Validator][Failure]") {
  PatternValidator validator;

  SECTION("Empty token vector") {
    std::vector<std::shared_ptr<Token>> tokens;
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::PATTERN);
  }

  SECTION("Unexpected token") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::COMMA, ","),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::PATTERN);
  }

  SECTION("a") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::PATTERN);
  }

  SECTION("a(") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::NAME);
  }

  SECTION("a(_") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::PATTERN);
  }

  SECTION("a(_,") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        GrammarRule::EXPRESSION_SPEC);
  }

  SECTION("a(_, _") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::PATTERN);
  }

  SECTION("i(a") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "i"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::PATTERN);
  }

  SECTION("i(a,") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "i"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        GrammarRule::EXPRESSION_SPEC);
  }

  SECTION("a(1, _)") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::NAME);
  }

  SECTION("a(_, 1)") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        GrammarRule::EXPRESSION_SPEC);
  }

  SECTION("i(a, _") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "i"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::PATTERN);
  }

  SECTION("i(a, _,") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "i"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::PATTERN);
  }

  SECTION("i(a, _, _") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "i"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::PATTERN);
  }

  SECTION("w(") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::NAME);
  }

  SECTION("w(a") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::PATTERN);
  }

  SECTION("w(a,") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        GrammarRule::EXPRESSION_SPEC);
  }

  SECTION("w(a, _") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::PATTERN);
  }

  SECTION("w(a, a)") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        GrammarRule::EXPRESSION_SPEC);
  }
}
