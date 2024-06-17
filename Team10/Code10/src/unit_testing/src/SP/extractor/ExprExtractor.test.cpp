#include "extractor/ExprExtractor.h"

#include <memory>
#include <vector>

#include "WriteFacadeStub.h"
#include "catch.hpp"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("Expression extractor extract single valid expression correctly",
          "[Extractor]") {
  WriteFacadeStub writer{};
  ExprExtractor extractor{writer};

  SECTION("Extract multiply: x + 0 correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
  }

  SECTION("Parse divide: 9 - y correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "9"));
    tokens.push_back(std::make_unique<Token>(TokenType::MINUS, "-"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
  }
}

TEST_CASE("Expression extractor extracts double valid expression correctly",
          "[Extractor]") {
  WriteFacadeStub writer{};
  ExprExtractor extractor{writer};

  SECTION("Parse x + 0 - 1 correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::MINUS, "-"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }

  SECTION("Parse 9 - y + 6 correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "9"));
    tokens.push_back(std::make_unique<Token>(TokenType::MINUS, "-"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "6"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getType() == TokenType::CLOSE_BRACKET);
  }
}

TEST_CASE("Expression extractor extracts complex valid expression correctly",
          "[Extractor]") {
  WriteFacadeStub writer{};
  ExprExtractor extractor{writer};

  SECTION("Parse ((3 * x) + (y / 2)) - ((z - 1) % 4) correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "3"));
    tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::DIVIDE, "/"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::MINUS, "-"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "z"));
    tokens.push_back(std::make_unique<Token>(TokenType::MINUS, "-"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::MODULO, "%"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "4"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
  }
}
