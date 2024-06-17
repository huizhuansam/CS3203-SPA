#include "parser/PrintParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "exception/GrammarRule.h"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("Print parser success", "[SP][Print][Parser]") {
  PrintParser parser{};

  SECTION("Parse print statement correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfPrint"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfPrint");
  }

  SECTION("Parse print with \"print\" variable correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "endOfPrint"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(parser.parse(it, end));
    REQUIRE((*it)->getValue() == "endOfPrint");
  }
}

TEST_CASE("Print parser failure", "[SP][Print][Parser]") {
  PrintParser parser{};

  SECTION("Parse print with empty tokens") {
    std::vector<std::unique_ptr<Token>> tokens{};
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::PRINT);
  }

  SECTION("Parse print when keyword is not print") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::PRINT);
  }

  SECTION("Parse print when no print keyword") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::PRINT);
  }

  SECTION("Parse print when no semicolon") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(parser.parse(it, end), GrammarRule::PRINT);
  }
}
