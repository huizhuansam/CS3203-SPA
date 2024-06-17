#include <memory>
#include <vector>

#include "catch.hpp"
#include "parser/PatternParser.h"
#include "strategy/argument_types/SynonymType.h"
#include "strategy/strategy_types/PatternStrategy.h"

using namespace QPS;

TEST_CASE("PatternStrategy can parse while pattern clause correctly",
          "[QPS][Parser]") {
  SECTION("pattern w (v, _)") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "endOfPattern")};

    std::unordered_map<std::string, SynonymType> map = {
        {"w", SynonymType::WHILE}, {"v", SynonymType::VARIABLE}};

    auto it = tokens.begin();
    PatternStrategy actual =
        *(PatternParser::parse(StrategyType::WHILE_PATTERN, it, map));
    REQUIRE(actual.getSynonym() == "w");
    REQUIRE(actual.getArg1() == "v");
    REQUIRE(actual.getArgType1() == EntRefType::VARIABLE);
    REQUIRE((*it)->getValue() == "endOfPattern");
  }

  SECTION("pattern w (_, _)") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "endOfPattern")};

    std::unordered_map<std::string, SynonymType> map = {
        {"w", SynonymType::WHILE}};

    auto it = tokens.begin();
    PatternStrategy actual =
        *(PatternParser::parse(StrategyType::WHILE_PATTERN, it, map));
    REQUIRE(actual.getSynonym() == "w");
    REQUIRE(actual.getArg1() == "_");
    REQUIRE(actual.getArgType1() == EntRefType::WILDCARD);
    REQUIRE((*it)->getValue() == "endOfPattern");
  }

  SECTION("pattern w (ident, _)") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "var"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "endOfPattern")};

    std::unordered_map<std::string, SynonymType> map = {
        {"w", SynonymType::WHILE}};

    auto it = tokens.begin();
    PatternStrategy actual =
        *(PatternParser::parse(StrategyType::WHILE_PATTERN, it, map));
    REQUIRE(actual.getSynonym() == "w");
    REQUIRE(actual.getArg1() == "var");
    REQUIRE(actual.getArgType1() == EntRefType::IDENT);
    REQUIRE((*it)->getValue() == "endOfPattern");
  }
}
