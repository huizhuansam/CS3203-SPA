#include "parser/ReadParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("Read parser can parse valid read correctly") {
  ReadParser parser{};

  SECTION("Parse normal read statement correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "meBaby"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfAssign"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfAssign");
  }

  SECTION("Parse read of reserved word variable correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfAssign"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfAssign");
  }
}

TEST_CASE("Read parser throws error for invalid assignment", "[Parser]") {
  ReadParser parser{};

  SECTION("Throw error for empty tokens") {
    std::vector<std::unique_ptr<Token>> tokens;
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::READ);
  }

  SECTION("Throw error when first token is not read") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "hehe"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::READ);
  }

  SECTION("Throw error when last token is not semicolon") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "theRoom"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::READ);
  }
}
