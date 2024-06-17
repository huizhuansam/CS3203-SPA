#include "parser/CallParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("Call parser can parse valid call correctly") {
  CallParser parser{};

  SECTION("Parse normal call statement correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::CALL, "call"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "meBaby"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfCall"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfCall");
  }

  SECTION("Parse call of reserved word variable correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::CALL, "call"));
    tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfCall"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfCall");
  }
}

TEST_CASE("Call parser throws error for invalid assignment", "[Parser]") {
  CallParser parser{};

  SECTION("Throw error for empty tokens") {
    std::vector<std::unique_ptr<Token>> tokens;
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::CALL);
  }

  SECTION("Throw error when first token is not call") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "hehe"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::CALL);
  }

  SECTION("Throw error when last token is not semicolon") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::CALL, "call"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "theRoom"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::CALL);
  }
}
