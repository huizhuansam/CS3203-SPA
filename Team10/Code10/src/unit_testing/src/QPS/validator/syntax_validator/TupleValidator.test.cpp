#include "validator/syntax_validator/TupleValidator.h"

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("TupleValidator valid scenario", "[QPS][Validator][Success]") {
  TupleValidator validator;

  SECTION("Valid tuple with single synonym") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::CLOSE_ANGLE_BRACKET, ">"),
        std::make_shared<Token>(TokenType::NAME, "endOfTuple"),

    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfTuple");
  }

  SECTION("Valid tuple with single attrRef") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "stmt#"),
        std::make_shared<Token>(TokenType::CLOSE_ANGLE_BRACKET, ">"),
        std::make_shared<Token>(TokenType::NAME, "endOfTuple"),

    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfTuple");
  }

  SECTION("Valid tuple with attrRef and synonym") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "stmt#"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "b"),
        std::make_shared<Token>(TokenType::CLOSE_ANGLE_BRACKET, ">"),
        std::make_shared<Token>(TokenType::NAME, "endOfTuple"),

    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfTuple");
  }

  SECTION("Valid tuple with synonym and attrRef") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "b"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "stmt#"),
        std::make_shared<Token>(TokenType::CLOSE_ANGLE_BRACKET, ">"),
        std::make_shared<Token>(TokenType::NAME, "endOfTuple"),

    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfTuple");
  }

  SECTION("Valid tuple with three synonyms") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "b"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "c"),
        std::make_shared<Token>(TokenType::CLOSE_ANGLE_BRACKET, ">"),
        std::make_shared<Token>(TokenType::NAME, "endOfTuple"),

    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
    REQUIRE((*it)->getValue() == "endOfTuple");
  }
}

TEST_CASE("TupleValidator invalid scenario", "[QPS][Validator][Failure]") {
  TupleValidator validator;

  SECTION("Empty token vector") {
    std::vector<std::shared_ptr<Token>> tokens;
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::TUPLE);
  }

  SECTION("Invalid token sequence: '<'") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::TUPLE);
  }

  SECTION("Invalid token sequence: '<''a'") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "a"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::TUPLE);
  }

  SECTION("Invalid token sequence: '<''a''b'") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::NAME, "b"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::TUPLE);
  }

  SECTION("Invalid token sequence: '<''a' ','") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::TUPLE);
  }

  SECTION("Invalid token sequence: '<''a' ',' 'b'") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "b"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::TUPLE);
  }

  SECTION("Unexpected token: '<''a' '/'") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::DIV, "/"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::TUPLE);
  }

  SECTION("Invalid token sequence: '<''>'") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::CLOSE_ANGLE_BRACKET, ">"),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::TUPLE);
  }

  SECTION("Unexpected token: ','") {
    std::vector<std::shared_ptr<Token>> tokens{
        std::make_shared<Token>(TokenType::COMMA, ","),
    };
    std::vector<std::shared_ptr<Token>>::iterator it = tokens.begin();
    std::vector<std::shared_ptr<Token>>::iterator end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end), GrammarRule::TUPLE);
  }
}
