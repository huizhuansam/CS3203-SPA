#include "parser/Parser.h"

#include <vector>

#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("Throw error if tokens are empty", "[Parser]") {
  std::vector<std::unique_ptr<Token>> tokens;
  REQUIRE_THROWS_WITH(Parser::parse(tokens), GrammarRule::PROGRAM);
}
