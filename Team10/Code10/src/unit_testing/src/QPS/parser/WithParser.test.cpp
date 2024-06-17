#include "parser/WithParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "strategy/WithStrategy.h"

using namespace QPS;

TEST_CASE("WithParser can parse with clause correctly", "[QPS][Parser]") {
  WithParser parser{};

  SECTION("attrRef = ident") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::NAME, "procName"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "Third"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\"")};

    std::unordered_map<std::string, SynonymType> map = {
        {"p", SynonymType::PROCEDURE}};

    auto it = tokens.begin();
    WithStrategy actual = *(parser.parse(it, map));
    REQUIRE(actual.getArg1() == "p");
    REQUIRE(actual.getArg2() == "Third");
    REQUIRE(actual.getArgType1() == RefType::PROCEDURE_PROCNAME);
    REQUIRE(actual.getArgType2() == RefType::IDENT);
  }

  SECTION("integer = integer") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::INTEGER, "12"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::INTEGER, "12")};

    auto it = tokens.begin();
    WithStrategy actual = *(parser.parse(it, {}));
    REQUIRE(actual.getArg1() == "12");
    REQUIRE(actual.getArg2() == "12");
    REQUIRE(actual.getArgType1() == RefType::INTEGER);
    REQUIRE(actual.getArgType2() == RefType::INTEGER);
  }

  SECTION("ident = attrRef") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "first"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::NAME, "varName"),
    };

    std::unordered_map<std::string, SynonymType> map = {
        {"v", SynonymType::VARIABLE}};

    auto it = tokens.begin();
    WithStrategy actual = *(parser.parse(it, map));
    REQUIRE(actual.getArg1() == "first");
    REQUIRE(actual.getArg2() == "v");
    REQUIRE(actual.getArgType1() == RefType::IDENT);
    REQUIRE(actual.getArgType2() == RefType::VARIABLE_VARNAME);
  }
}