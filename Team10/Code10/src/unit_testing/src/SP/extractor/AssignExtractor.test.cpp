#include "extractor/AssignExtractor.h"

#include <memory>
#include <vector>

#include "WriteFacadeStub.h"
#include "catch.hpp"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("Assign extractor", "[Extractor]") {
  WriteFacadeStub writer{};
  AssignExtractor assignExtractor{writer};

  SECTION("Extract constant assignment correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfAssign"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(assignExtractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfAssign");
  }

  SECTION("Extract variable assignment correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "a"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "b"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfAssign"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(assignExtractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfAssign");
  }

  SECTION("Extract expression assignment correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "a"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfAssign"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(assignExtractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfAssign");
  }

  SECTION("Extract assignment with keyword variable correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfAssign"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(assignExtractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfAssign");
  }

  SECTION("Extract nested expression assignment correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "a"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "-"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "z"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfAssign"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(assignExtractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfAssign");
  }
}
