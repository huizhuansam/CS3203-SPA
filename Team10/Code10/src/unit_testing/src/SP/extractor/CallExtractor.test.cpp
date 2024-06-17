#include "extractor/CallExtractor.h"

#include <memory>
#include <vector>

#include "WriteFacadeStub.h"
#include "catch.hpp"
#include "tokenizer/Token.h"
#include "tokenizer/TokenType.h"

using namespace SP;

TEST_CASE("CallExtractor success scenario", "[SP][Calls][Extractor][Success]") {
  WriteFacadeStub writer{};
  CallExtractor extractor{writer};

  SECTION("extract call statement correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::CALL, "call"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "procName"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfCall"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfCall");
  }

  SECTION("extract call statement with procedure named call correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::CALL, "call"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "call"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfCall"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfCall");
  }

  SECTION("extract call statement with procedure named procedure correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::CALL, "call"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfCall"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfCall");
  }
}
