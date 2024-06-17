#include "parser/ProcedureParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"
#include "tokenizer/TokenType.h"

using namespace SP;

TEST_CASE("Procedure parser success", "[SP][Parser][Success]") {
  ProcedureParser parser{};

  SECTION("Parse valid procedure correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "testProcedure"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::NAME, "endOfProcedure"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfProcedure");
  }

  SECTION("Parse procedure with \"procedure\" name") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "procedure"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::NAME, "endOfProcedure"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfProcedure");
  }
}

TEST_CASE("Procedure parser failure", "[SP][Parser][Failure][!mayfail]") {
  ProcedureParser parser{};

  SECTION("Parse procedure with no statements") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "testProcedure"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::STMT_LIST);
  }

  SECTION("Parse procedure with no procedure keyword") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "testProcedure"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::PROCEDURE);
  }

  SECTION("Parse procedure with no following tokens") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(
        (std::make_unique<Token>(TokenType::PROCEDURE, "procedure")));
    tokens.push_back(
        (std::make_unique<Token>(TokenType::NAME, "testProcedure")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::PROCEDURE);
  }

  SECTION("Parse procedure with no opening brace") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "testProcedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::PROCEDURE);
  }

  SECTION("Parse procedure with no closing brace") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "testProcedure"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::PROCEDURE);
  }

  SECTION("Parse procedure with nested procedure") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "outer"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "inner"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::STMT);
  }
}
