#include "../src/spa/QPS/include/parser/Parser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "strategy/BooleanSelectStrategy.h"
#include "strategy/Strategy.h"
#include "strategy/TupleSelectStrategy.h"
#include "strategy/WithStrategy.h"
#include "strategy/strategy_types/EntEntArgStrategy.h"
#include "strategy/strategy_types/PatternStrategy.h"
#include "strategy/strategy_types/StmtEntArgStrategy.h"
#include "strategy/strategy_types/StmtStmtArgStrategy.h"

using namespace QPS;

TEST_CASE("Parser can parse 1 clause correctly", "[QPS][Parser]") {
  SECTION("Select clause with 1 declaration") {
    // assign a; Select a
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a")};

    std::vector<std::shared_ptr<Strategy>> actual = Parser::parse(tokens);
    REQUIRE(actual.size() == 1);
    REQUIRE((*(actual[0])).isSelectStrategy() == true);
  }

  SECTION("Select clause with multiple declarations") {
    // constant a, b; read r; Select a
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "constant"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "b"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "read"),
        std::make_shared<Token>(TokenType::NAME, "r"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a")};

    std::vector<std::shared_ptr<Strategy>> actual = Parser::parse(tokens);
    REQUIRE(actual.size() == 1);
    REQUIRE((*(actual[0])).isSelectStrategy() == true);
  }
}

TEST_CASE("Parser can parse multiple clauses correctly", "[QPS][Parser]") {
  SECTION(
      "Select, assign pattern, ModifiesS, ModifiesP, UsesS, UsesP, Follows, "
      "Follows*, Parent, Parent*, Calls, Calls*, Next, Next*, Affects, with, "
      "if pattern, while pattern,") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "while"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "procedure"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "p1"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "if"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "count"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Modifies"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "4"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Modifies"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Uses"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "12"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Uses"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "main"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Follows"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Follows*"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::INTEGER, "8"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Parent"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Parent*"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Calls"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "procName"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Calls*"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "p1"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Next"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "2"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Next*"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "4"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::INTEGER, "9"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Affects"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "2"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "with"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::NAME, "stmt#"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::NAME, "stmt#"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };

    std::vector<std::shared_ptr<Strategy>> actual = Parser::parse(tokens);
    auto &actualStrategy1 = *actual[0];
    auto &actualStrategy2 = *actual[1];
    auto &actualStrategy3 = *actual[2];
    auto &actualStrategy4 = *actual[3];
    auto &actualStrategy5 = *actual[4];
    auto &actualStrategy6 = *actual[5];
    auto &actualStrategy7 = *actual[6];
    auto &actualStrategy8 = *actual[7];
    auto &actualStrategy9 = *actual[8];
    auto &actualStrategy10 = *actual[9];
    auto &actualStrategy11 = *actual[10];
    auto &actualStrategy12 = *actual[11];
    auto &actualStrategy13 = *actual[12];
    auto &actualStrategy14 = *actual[13];
    auto &actualStrategy15 = *actual[14];
    auto &actualStrategy16 = *actual[15];
    auto &actualStrategy17 = *actual[16];
    auto &actualStrategy18 = *actual[17];
    REQUIRE(actual.size() == 18);
    REQUIRE(actualStrategy1.isSelectStrategy() == true);
    REQUIRE(typeid(actualStrategy2) == typeid(PatternStrategy));
    REQUIRE(typeid(actualStrategy3) == typeid(StmtEntArgStrategy));
    REQUIRE(typeid(actualStrategy4) == typeid(EntEntArgStrategy));
    REQUIRE(typeid(actualStrategy5) == typeid(StmtEntArgStrategy));
    REQUIRE(typeid(actualStrategy6) == typeid(EntEntArgStrategy));
    REQUIRE(typeid(actualStrategy7) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(actualStrategy8) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(actualStrategy9) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(actualStrategy10) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(actualStrategy11) == typeid(EntEntArgStrategy));
    REQUIRE(typeid(actualStrategy12) == typeid(EntEntArgStrategy));
    REQUIRE(typeid(actualStrategy13) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(actualStrategy14) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(actualStrategy15) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(actualStrategy16) == typeid(WithStrategy));
    REQUIRE(typeid(actualStrategy17) == typeid(PatternStrategy));
    REQUIRE(typeid(actualStrategy18) == typeid(PatternStrategy));
  }
}

TEST_CASE(
    "Parser can parse multi-clause queries connected by \"and\" correctly",
    "[QPS][Parser]") {
  SECTION("Such that clauses") {
    // assign a; while w;
    // Select a such that Modifies (a, "x") and Parent* (w, a) and Next* (1, a)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "while"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Modifies"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "Parent*"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "Next*"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")")};
    std::vector<std::shared_ptr<Strategy>> actual = Parser::parse(tokens);
    auto &actualStrategy1 = *actual[0];
    auto &actualStrategy2 = *actual[1];
    auto &actualStrategy3 = *actual[2];
    auto &actualStrategy4 = *actual[3];
    REQUIRE(actual.size() == 4);
    REQUIRE(typeid(actualStrategy1) == typeid(TupleSelectStrategy));
    REQUIRE(typeid(actualStrategy2) == typeid(StmtEntArgStrategy));
    REQUIRE(typeid(actualStrategy3) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(actualStrategy4) == typeid(StmtStmtArgStrategy));
  }

  SECTION("Pattern clauses") {
    // assign a1, a2; while w; if ifs;
    // Select a2 pattern a1 ("x", _) and a2 ("x", _"x"_) and w ("v", _) and ifs
    // (_, _, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a1"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "a2"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "while"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "if"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a2"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "a1"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "a2"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    std::vector<std::shared_ptr<Strategy>> actual = Parser::parse(tokens);
    auto &actualStrategy1 = *actual[0];
    auto &actualStrategy2 = *actual[1];
    auto &actualStrategy3 = *actual[2];
    auto &actualStrategy4 = *actual[3];
    auto &actualStrategy5 = *actual[4];
    REQUIRE(actual.size() == 5);
    REQUIRE(typeid(actualStrategy1) == typeid(TupleSelectStrategy));
    REQUIRE(typeid(actualStrategy2) == typeid(PatternStrategy));
    REQUIRE(typeid(actualStrategy3) == typeid(PatternStrategy));
    REQUIRE(typeid(actualStrategy4) == typeid(PatternStrategy));
    REQUIRE(typeid(actualStrategy5) == typeid(PatternStrategy));
  }

  SECTION("with clauses") {
    // Select p with v.varName = p.procName and s.stmt# = 8 and p.procName =
    // "Main"
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "procedure"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::NAME, "with"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::NAME, "varName"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::NAME, "procName"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::NAME, "stmt#"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::INTEGER, "8"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::NAME, "procName"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "Main"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
    };
    std::vector<std::shared_ptr<Strategy>> actual = Parser::parse(tokens);
    auto &actualStrategy1 = *actual[0];
    auto &actualStrategy2 = *actual[1];
    auto &actualStrategy3 = *actual[2];
    auto &actualStrategy4 = *actual[3];
    REQUIRE(actual.size() == 4);
    REQUIRE(typeid(actualStrategy1) == typeid(TupleSelectStrategy));
    REQUIRE(typeid(actualStrategy2) == typeid(WithStrategy));
    REQUIRE(typeid(actualStrategy3) == typeid(WithStrategy));
    REQUIRE(typeid(actualStrategy4) == typeid(WithStrategy));
  }

  SECTION("Such that + Pattern + with clauses") {
    // Select a such that Parent* (w, a) and Next* (1, a) pattern a ("x", _)
    // with a.stmt# = s.stmt#
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "while"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Parent*"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "Next*"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "with"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::NAME, "stmt#"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::NAME, "stmt#"),
    };
    std::vector<std::shared_ptr<Strategy>> actual = Parser::parse(tokens);
    auto &actualStrategy1 = *actual[0];
    auto &actualStrategy2 = *actual[1];
    auto &actualStrategy3 = *actual[2];
    auto &actualStrategy4 = *actual[3];
    auto &actualStrategy5 = *actual[4];
    REQUIRE(actual.size() == 5);
    REQUIRE(typeid(actualStrategy1) == typeid(TupleSelectStrategy));
    REQUIRE(typeid(actualStrategy2) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(actualStrategy3) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(actualStrategy4) == typeid(PatternStrategy));
    REQUIRE(typeid(actualStrategy5) == typeid(WithStrategy));
  }
}

TEST_CASE("Parser can parse boolean select clause correctly", "[QPS][Parser]") {
  // variable v; assign a;
  // Select BOOLEAN pattern a(v, _)
  SECTION("Boolean select clause") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };

    std::vector<std::shared_ptr<Strategy>> actual = Parser::parse(tokens);
    auto &actualStrategy1 = *actual[0];
    auto &actualStrategy2 = *actual[1];
    REQUIRE(actual.size() == 2);
    REQUIRE(typeid(actualStrategy1) == typeid(BooleanSelectStrategy));
    REQUIRE(typeid(actualStrategy2) == typeid(PatternStrategy));
  }

  SECTION("Boolean select clause with declared BOOLEAN synonym") {
    // variable BOOLEAN; assign a;
    // Select BOOLEAN pattern a(BOOLEAN, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };

    std::vector<std::shared_ptr<Strategy>> actual = Parser::parse(tokens);
    auto &actualStrategy1 = *actual[0];
    auto &actualStrategy2 = *actual[1];
    REQUIRE(actual.size() == 2);
    REQUIRE(typeid(actualStrategy1) == typeid(TupleSelectStrategy));
    REQUIRE(typeid(actualStrategy2) == typeid(PatternStrategy));
  }
}

TEST_CASE("Parser can parse tuple select clause correctly", "[QPS][Parser]") {
  SECTION("Select tuple with synonym and attrRef") {
    // procedure p; assign a;
    // Select <p, a.stmt#> pattern a(_, "x")
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "procedure"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "stmt#"),
        std::make_shared<Token>(TokenType::CLOSE_ANGLE_BRACKET, ">"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };

    std::vector<std::shared_ptr<Strategy>> actual = Parser::parse(tokens);
    auto &actualStrategy1 = *actual[0];
    auto &actualStrategy2 = *actual[1];
    REQUIRE(actual.size() == 2);
    REQUIRE(typeid(actualStrategy1) == typeid(TupleSelectStrategy));
    REQUIRE(typeid(actualStrategy2) == typeid(PatternStrategy));
  }
}

TEST_CASE("Parser can parse not correctly", "[QPS][Parser]") {
  SECTION("such that not") {
    // procedure p;
    // Select p such that not Calls* (p, "Third") and Next*(1,_)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "procedure"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "not"),
        std::make_shared<Token>(TokenType::NAME, "Calls*"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "Third"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "Next*"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };

    std::vector<std::shared_ptr<Strategy>> actual = Parser::parse(tokens);
    auto &actualStrategy1 = *actual[0];
    auto &actualStrategy2 = *actual[1];
    auto &actualStrategy3 = *actual[2];
    REQUIRE(actual.size() == 3);
    REQUIRE(typeid(actualStrategy1) == typeid(TupleSelectStrategy));
    REQUIRE(typeid(actualStrategy2) == typeid(EntEntArgStrategy));
    REQUIRE(typeid(actualStrategy3) == typeid(StmtStmtArgStrategy));
    REQUIRE(actualStrategy2.isNotStrategy() == true);
    REQUIRE(actualStrategy3.isNotStrategy() == false);
  }

  SECTION("pattern not") {
    // while w; assign a; variable v;
    // Select w pattern a (_,_) and not w("v", _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "while"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "not"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };

    std::vector<std::shared_ptr<Strategy>> actual = Parser::parse(tokens);
    auto &actualStrategy1 = *actual[0];
    auto &actualStrategy2 = *actual[1];
    auto &actualStrategy3 = *actual[2];
    REQUIRE(actual.size() == 3);
    REQUIRE(typeid(actualStrategy1) == typeid(TupleSelectStrategy));
    REQUIRE(typeid(actualStrategy2) == typeid(PatternStrategy));
    REQUIRE(typeid(actualStrategy3) == typeid(PatternStrategy));
    REQUIRE(actualStrategy2.isNotStrategy() == false);
    REQUIRE(actualStrategy3.isNotStrategy() == true);
  }

  SECTION("with not") {
    // variable v; procedure p;
    // Select p with not v.varName = p.procName and 8 = 8
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "procedure"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::NAME, "with"),
        std::make_shared<Token>(TokenType::NAME, "not"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::NAME, "varName"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::NAME, "procName"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::INTEGER, "8"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::INTEGER, "8"),
    };
    std::vector<std::shared_ptr<Strategy>> actual = Parser::parse(tokens);
    auto &actualStrategy1 = *actual[0];
    auto &actualStrategy2 = *actual[1];
    auto &actualStrategy3 = *actual[2];
    REQUIRE(actual.size() == 3);
    REQUIRE(typeid(actualStrategy1) == typeid(TupleSelectStrategy));
    REQUIRE(typeid(actualStrategy2) == typeid(WithStrategy));
    REQUIRE(typeid(actualStrategy3) == typeid(WithStrategy));
    REQUIRE(actualStrategy2.isNotStrategy() == true);
    REQUIRE(actualStrategy3.isNotStrategy() == false);
  }
}
