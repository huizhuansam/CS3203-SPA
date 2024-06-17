#include "parser/EntEntParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "strategy/argument_types/SynonymType.h"

using namespace QPS;

TEST_CASE("EntEntParser can parse (entRef, entRef)", "[QPS][Parser]") {
  std::unordered_map<std::string, SynonymType> map = {
      {"p", SynonymType::PROCEDURE}, {"v", SynonymType::VARIABLE}};

  SECTION("Modifies(ident, synonym)") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "proc"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")")};

    auto it = tokens.begin();
    EntEntArgStrategy actual =
        *(EntEntParser::parse(StrategyType::MODIFIES_P, it, map));
    REQUIRE(actual.getArg1() == "proc");
    REQUIRE(actual.getArg2() == "v");
    REQUIRE(actual.getArgType1() == EntRefType::IDENT);
    REQUIRE(actual.getArgType2() == EntRefType::VARIABLE);
  }

  SECTION("Calls(wildcard, ident)") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "procA"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")")};

    auto it = tokens.begin();
    EntEntArgStrategy actual =
        *(EntEntParser::parse(StrategyType::CALLS, it, map));
    REQUIRE(actual.getArg1() == "_");
    REQUIRE(actual.getArg2() == "procA");
    REQUIRE(actual.getArgType1() == EntRefType::WILDCARD);
    REQUIRE(actual.getArgType2() == EntRefType::IDENT);
  }

  SECTION("Uses(synonym, wildcard)") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")")};

    auto it = tokens.begin();
    EntEntArgStrategy actual =
        *(EntEntParser::parse(StrategyType::USES_P, it, map));
    REQUIRE(actual.getArg1() == "p");
    REQUIRE(actual.getArg2() == "_");
    REQUIRE(actual.getArgType1() == EntRefType::PROCEDURE);
    REQUIRE(actual.getArgType2() == EntRefType::WILDCARD);
  }
}