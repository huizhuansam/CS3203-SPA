#include "extractor/VariableExtractor.h"

#include <memory>
#include <vector>

#include "WriteFacadeStub.h"
#include "catch.hpp"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("Variable extractor", "[Extractor]") {
  WriteFacadeStub writer{};
  VariableExtractor extractor{writer};

  SECTION("Variable extractor parses name tokens correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfName"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfName");
  }

  SECTION("Variable extractor parses reserved word tokens correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfName"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getValue() == "endOfName");
  }
}
