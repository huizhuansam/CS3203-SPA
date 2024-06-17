#include "parser/StmtEntParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "strategy/argument_types/SynonymType.h"

using namespace QPS;

TEST_CASE("StmtEntParser can parse (stmtRef, entRef)", "[QPS][Parser]") {
  std::unordered_map<std::string, SynonymType> map = {
      {"a", SynonymType::ASSIGN}, {"v", SynonymType::VARIABLE}};

  SECTION("Modifies(synonym, wildcard)") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")")};

    auto it = tokens.begin();
    StmtEntArgStrategy actual =
        *(StmtEntParser::parse(StrategyType::MODIFIES_S, it, map));
    REQUIRE(actual.getArg1() == "a");
    REQUIRE(actual.getArg2() == "_");
    REQUIRE(actual.getArgType1() == StmtRefType::ASSIGN);
    REQUIRE(actual.getArgType2() == EntRefType::WILDCARD);
  }

  SECTION("Uses(integer, ident)") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "6"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "var"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")")};

    auto it = tokens.begin();
    StmtEntArgStrategy actual =
        *(StmtEntParser::parse(StrategyType::USES_S, it, map));
    REQUIRE(actual.getArg1() == "6");
    REQUIRE(actual.getArg2() == "var");
    REQUIRE(actual.getArgType1() == StmtRefType::INTEGER);
    REQUIRE(actual.getArgType2() == EntRefType::IDENT);
  }

  SECTION("Modifies(synonym, synonym)") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")")};

    auto it = tokens.begin();
    StmtEntArgStrategy actual =
        *(StmtEntParser::parse(StrategyType::MODIFIES_S, it, map));
    REQUIRE(actual.getArg1() == "a");
    REQUIRE(actual.getArg2() == "v");
    REQUIRE(actual.getArgType1() == StmtRefType::ASSIGN);
    REQUIRE(actual.getArgType2() == EntRefType::VARIABLE);
  }
}