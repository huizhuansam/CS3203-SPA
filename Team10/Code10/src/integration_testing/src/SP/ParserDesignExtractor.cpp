#include "catch.hpp"
#include "extractor/DesignExtractor.h"
#include "fixtures/tokens/ValidUnParsedTokens.hpp"
#include "parser/Parser.h"

using namespace SP;

TEST_CASE("Valid tokens input for Parser-DesignExtractor",
          "[SP:Parser-DesignExtractor]") {
  SECTION("Single procedure with all statement types except call") {
    std::vector<std::unique_ptr<Token>>& tokens =
        ValidUnParsedTokens::valid_unparsed_tokens;
    Parser::parse(tokens);
    REQUIRE_NOTHROW(DesignExtractor::extract(tokens));
  }

  SECTION("Multiple procedures with all statement types except call") {
    std::vector<std::unique_ptr<Token>>& tokens =
        ValidUnParsedTokens::valid_unparsed_tokens_2;
    Parser::parse(tokens);
    REQUIRE_NOTHROW(DesignExtractor::extract(tokens));
  }

  SECTION("Procedure and variable names same as keywords") {
    std::vector<std::unique_ptr<Token>>& tokens =
        ValidUnParsedTokens::valid_unparsed_tokens_3;
    Parser::parse(tokens);
    REQUIRE_NOTHROW(DesignExtractor::extract(tokens));
  }

  SECTION("Deeply nested container statement") {
    std::vector<std::unique_ptr<Token>>& tokens =
        ValidUnParsedTokens::valid_unparsed_tokens_4;
    Parser::parse(tokens);
    REQUIRE_NOTHROW(DesignExtractor::extract(tokens));
  }

  SECTION("Complex conditional expression with complex expression nested") {
    std::vector<std::unique_ptr<Token>>& tokens =
        ValidUnParsedTokens::valid_unparsed_tokens_5;
    Parser::parse(tokens);
    REQUIRE_NOTHROW(DesignExtractor::extract(tokens));
  }
}
