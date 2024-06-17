#include "validator/syntax_validator/PatternCondValidator.h"

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("PatternCondValidator valid scenario", "[QPS][Validator][Success]") {
  PatternCondValidator validator;

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

  SECTION("not a(a, \"1 + 1\")") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::NAME, "not"),
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

  SECTION("a(a, \"1 + 1\") and w(a, _)") {
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
        std::make_shared<Token>(TokenType::NAME, "and"),
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

  SECTION("a(a, \"1 + 1\") and not w(a, _)") {
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
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "not"),
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

  SECTION("a(a, \"1 + 1\") and not w(a, _) and not i(a, _, _)") {
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
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "not"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "not"),
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
}

TEST_CASE("PatternCondValidator invalid scenario",
          "[QPS][Validator][Failure]") {
  PatternCondValidator validator;

  SECTION("Empty token list") {
    std::vector<std::shared_ptr<Token>> tokens{};
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

  SECTION("a(a, \"1 + 1\") and") {
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
        std::make_shared<Token>(TokenType::NAME, "and"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::PATTERN);
  }

  SECTION("a(a, \"1 + 1\") and not") {
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
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "not"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::PATTERN);
  }
}
