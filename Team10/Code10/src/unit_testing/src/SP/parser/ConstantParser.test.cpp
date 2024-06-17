#include "parser/ConstantParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("Constant parser parses integer token correctly", "[Parser]") {
  ConstantParser parser{};

  SECTION("Do not throw error for integer token") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE(it == end);
  }
}

TEST_CASE("Constant parser throws error for invalid token", "[Parser]") {
  ConstantParser parser{};

  SECTION("Throws error for empty token") {
    std::vector<std::unique_ptr<Token>> tokens{};
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::CONST_VALUE);
  }

  SECTION("Throws error when encounter non integer token") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::SEMICOLON, ";")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::CONST_VALUE);
  }
}
