#include "extractor/ConstantExtractor.h"

#include <memory>
#include <vector>

#include "WriteFacadeStub.h"
#include "catch.hpp"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("Constant extractor extracts integer token correctly",
          "[Extractor]") {
  WriteFacadeStub writer{};
  ConstantExtractor extractor{writer};

  SECTION("Iterator consumes integer token") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE(it == end);
  }
}
