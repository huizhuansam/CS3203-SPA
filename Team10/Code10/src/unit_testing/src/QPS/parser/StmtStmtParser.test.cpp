#include "parser/StmtStmtParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "strategy/argument_types/SynonymType.h"

using namespace QPS;

TEST_CASE("StmtStmtParser can parse (stmtRef, stmtRef)", "[QPS][Parser]") {
  std::unordered_map<std::string, SynonymType> map = {
      {"a", SynonymType::ASSIGN}};

  SECTION("Follows(synonym, int)") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")")};

    auto it = tokens.begin();
    StmtStmtArgStrategy actual =
        *(StmtStmtParser::parse(StrategyType::FOLLOWS, it, map));
    REQUIRE(actual.getArg1() == "a");
    REQUIRE(actual.getArg2() == "3");
    REQUIRE(actual.getArgType1() == StmtRefType::ASSIGN);
    REQUIRE(actual.getArgType2() == StmtRefType::INTEGER);
  }

  SECTION("Parent(int, wildcard)") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")")};

    auto it = tokens.begin();
    StmtStmtArgStrategy actual =
        *(StmtStmtParser::parse(StrategyType::PARENT, it, map));
    REQUIRE(actual.getArg1() == "3");
    REQUIRE(actual.getArg2() == "_");
    REQUIRE(actual.getArgType1() == StmtRefType::INTEGER);
    REQUIRE(actual.getArgType2() == StmtRefType::WILDCARD);
  }

  SECTION("Affects(wildcard, synonym") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")")};

    auto it = tokens.begin();
    StmtStmtArgStrategy actual =
        *(StmtStmtParser::parse(StrategyType::AFFECTS, it, map));
    REQUIRE(actual.getArg1() == "_");
    REQUIRE(actual.getArg2() == "a");
    REQUIRE(actual.getArgType1() == StmtRefType::WILDCARD);
    REQUIRE(actual.getArgType2() == StmtRefType::ASSIGN);
  }
}