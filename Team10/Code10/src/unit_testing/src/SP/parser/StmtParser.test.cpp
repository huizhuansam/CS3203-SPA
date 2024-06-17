#include "parser/StmtParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("StmtParser parse valid assign correctly", "[Parser]") {
  SECTION("Parse read correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "me"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfStmt"));
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unique_ptr<StmtParser> parser = StmtParser::of(it, end);
    REQUIRE_NOTHROW(parser->parse(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  SECTION("Parse assign correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "mewIng"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfStmt"));
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unique_ptr<StmtParser> parser = StmtParser::of(it, end);
    REQUIRE_NOTHROW(parser->parse(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  SECTION("Parse reserved word as assign correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfStmt"));
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unique_ptr<StmtParser> parser = StmtParser::of(it, end);
    REQUIRE_NOTHROW(parser->parse(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  SECTION("Parse print print statement correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfStmt"));
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unique_ptr<StmtParser> parser = StmtParser::of(it, end);
    REQUIRE_NOTHROW(parser->parse(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  SECTION("Parse print print statement with keyword correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfStmt"));
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unique_ptr<StmtParser> parser = StmtParser::of(it, end);
    REQUIRE_NOTHROW(parser->parse(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  SECTION("Parse if statement correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "10"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "book"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfStmt"));
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unique_ptr<StmtParser> parser = StmtParser::of(it, end);
    REQUIRE_NOTHROW(parser->parse(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  SECTION("Parse if with keyword correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "10"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "book"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfStmt"));
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unique_ptr<StmtParser> parser = StmtParser::of(it, end);
    REQUIRE_NOTHROW(parser->parse(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  SECTION("Parse while statement correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::LT, "<"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "10"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfStmt"));
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unique_ptr<StmtParser> parser = StmtParser::of(it, end);
    REQUIRE_NOTHROW(parser->parse(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  SECTION("Parse while statement with keyword correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::LT, "<"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "10"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfStmt"));
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unique_ptr<StmtParser> parser = StmtParser::of(it, end);
    REQUIRE_NOTHROW(parser->parse(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  // TODO: Test call
}

TEST_CASE("StmtParser throws error when parsing invalid statement",
          "[Parser]") {
  SECTION("Empty statement") {
    std::vector<std::unique_ptr<Token>> tokens{};
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(StmtParser::of(it, end), GrammarRule::STMT);
  }

  SECTION("Not statement starting token type") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(StmtParser::of(it, end), GrammarRule::STMT);
  }

  // error within statement is handled by the respective parser
}
