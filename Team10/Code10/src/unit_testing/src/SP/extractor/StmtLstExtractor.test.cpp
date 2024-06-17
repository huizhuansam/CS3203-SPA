#include "extractor/StmtLstExtractor.h"

#include <memory>
#include <vector>

#include "WriteFacadeStub.h"
#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("StmtLstExtractor can extract valid statement list correctly",
          "[Parser]") {
  WriteFacadeStub writer;
  StmtLstExtractor extractor{writer};

  SECTION("Parse single statement correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET,
                                             "endOfStmtLst"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfStmtLst");
  }

  SECTION("Parse multiple statements correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "book"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET,
                                             "endOfStmtLst"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfStmtLst");
  }

  SECTION("Parse multiple statements with nested statement list correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    // x = 0;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    // read book;
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "book"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    // while (x < 10) { x = x + 1; }
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
    // if (x == 10) then { print book; } else { x = 1; }
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
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET,
                                             "endOfStmtLst"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfStmtLst");
  }
}
