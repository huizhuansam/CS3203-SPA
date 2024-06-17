#include <memory>
#include <vector>

#include "WriteFacadeStub.h"
#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "extractor/IStmtExtractorFactory.h"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("StmtExtractor extract valid assign correctly", "[Parser]") {
  WriteFacadeStub writer;

  SECTION("Extract read correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "me"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfStmt"));
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unique_ptr<IExtractor> extractor =
        IStmtExtractorFactory::of(it, writer);
    REQUIRE_NOTHROW(extractor->extract(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  SECTION("Extract assign correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "mewIng"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfStmt"));
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unique_ptr<IExtractor> extractor =
        IStmtExtractorFactory::of(it, writer);
    REQUIRE_NOTHROW(extractor->extract(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  SECTION("Extract reserved word as assign correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfStmt"));
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unique_ptr<IExtractor> extractor =
        IStmtExtractorFactory::of(it, writer);
    REQUIRE_NOTHROW(extractor->extract(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  SECTION("Extract print print statement correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfStmt"));
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unique_ptr<IExtractor> extractor =
        IStmtExtractorFactory::of(it, writer);
    REQUIRE_NOTHROW(extractor->extract(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  SECTION("Extract print print statement with keyword correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfStmt"));
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unique_ptr<IExtractor> extractor =
        IStmtExtractorFactory::of(it, writer);
    REQUIRE_NOTHROW(extractor->extract(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  SECTION("Extract if statement correctly") {
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
    std::unique_ptr<IExtractor> extractor =
        IStmtExtractorFactory::of(it, writer);
    REQUIRE_NOTHROW(extractor->extract(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  SECTION("Extract if with keyword correctly") {
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
    std::unique_ptr<IExtractor> extractor =
        IStmtExtractorFactory::of(it, writer);
    REQUIRE_NOTHROW(extractor->extract(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  SECTION("Extract while statement correctly") {
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
    std::unique_ptr<IExtractor> extractor =
        IStmtExtractorFactory::of(it, writer);
    REQUIRE_NOTHROW(extractor->extract(it, end));
    REQUIRE((*it)->getValue() == "endOfStmt");
  }

  // TODO: Test call
}
