#include "extractor/PrintExtractor.h"

#include <memory>
#include <vector>

#include "WriteFacadeStub.h"
#include "catch.hpp"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("Print extractor", "[Extractor]") {
  WriteFacadeStub writer{};
  PrintExtractor printExtractor{writer};

  SECTION("Extracts 'print variable;'") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfPrint"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(printExtractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfPrint");
  }

  SECTION("Extracts 'print print;'") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfPrint"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(printExtractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfPrint");
  }
}
