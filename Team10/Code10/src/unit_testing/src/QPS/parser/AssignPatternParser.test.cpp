#include <memory>
#include <vector>

#include "catch.hpp"
#include "parser/PatternParser.h"
#include "strategy/argument_types/SynonymType.h"
#include "strategy/strategy_types/PatternStrategy.h"

using namespace QPS;

TEST_CASE("AssignPatternParser can parse assign pattern clause correctly",
          "[QPS][Parser]") {
  SECTION("pattern a (wildcard, wildcard_expression)") {
    // pattern a(_, _"(x + 5) % 2"_)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::INTEGER, "5"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::MOD, "%"),
        std::make_shared<Token>(TokenType::INTEGER, "2"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "endOfPattern")};

    std::unordered_map<std::string, SynonymType> map = {
        {"a", SynonymType::ASSIGN}};
    const std::vector<std::string> expectedExpr = {"(", "x", "+", "5",
                                                   ")", "%", "2"};

    auto it = tokens.begin();
    PatternStrategy actual =
        *(PatternParser::parse(StrategyType::ASSIGN_PATTERN, it, map));
    REQUIRE(actual.getSynonym() == "a");
    REQUIRE(actual.getArg1() == "_");
    REQUIRE(actual.getArgType1() == EntRefType::WILDCARD);
    REQUIRE(actual.getArg2() == expectedExpr);
    REQUIRE(actual.getArgType2() == ExprSpecType::WILDCARD_EXPR);
    REQUIRE((*it)->getValue() == "endOfPattern");
  }

  SECTION("pattern a (synonym, expression)") {
    // pattern a(v, "x + 5")
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::INTEGER, "5"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "endOfPattern")};

    std::unordered_map<std::string, SynonymType> map = {
        {"a", SynonymType::ASSIGN}, {"v", SynonymType::VARIABLE}};
    const std::vector<std::string> expectedExpr = {"x", "+", "5"};

    auto it = tokens.begin();
    PatternStrategy actual =
        *(PatternParser::parse(StrategyType::ASSIGN_PATTERN, it, map));
    REQUIRE(actual.getSynonym() == "a");
    REQUIRE(actual.getArg1() == "v");
    REQUIRE(actual.getArgType1() == EntRefType::VARIABLE);
    REQUIRE(actual.getArg2() == expectedExpr);
    REQUIRE(actual.getArgType2() == ExprSpecType::EXPR);
    REQUIRE((*it)->getValue() == "endOfPattern");
  }

  SECTION("pattern a (ident, wildcard)") {
    // pattern a("var", _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "var"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "endOfPattern")};

    std::unordered_map<std::string, SynonymType> map = {
        {"a", SynonymType::ASSIGN}};
    const std::vector<std::string> expectedExpr = {"_"};

    auto it = tokens.begin();
    PatternStrategy actual =
        *(PatternParser::parse(StrategyType::ASSIGN_PATTERN, it, map));
    REQUIRE(actual.getSynonym() == "a");
    REQUIRE(actual.getArg1() == "var");
    REQUIRE(actual.getArgType1() == EntRefType::IDENT);
    REQUIRE(actual.getArg2() == expectedExpr);
    REQUIRE(actual.getArgType2() == ExprSpecType::WILDCARD);
    REQUIRE((*it)->getValue() == "endOfPattern");
  }
}