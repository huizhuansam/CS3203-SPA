#include "parser/VariableParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("Variable parser", "[Parser]") {
  VariableParser parser{};

  SECTION("Variable parser parses name tokens correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
  }

  SECTION("Variable parser parses reserved word tokens correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
  }
}

TEST_CASE("Variable parser errors when parsing invalid variable token",
          "[Parser]") {
  VariableParser parser{};
  SECTION("Throws error for empty tokens") {
    std::vector<std::unique_ptr<Token>> tokens;
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::VAR_NAME);
  }

  SECTION("Throws error when encounter non name tokens") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "0")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::VAR_NAME);
  }
}
