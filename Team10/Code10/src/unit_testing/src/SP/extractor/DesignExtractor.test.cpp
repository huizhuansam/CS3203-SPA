#include "extractor/DesignExtractor.h"

#include "catch.hpp"

using namespace SP;

TEST_CASE("Design extractor", "[SP][Extractor]") {
  SECTION("Statement number") {
    REQUIRE(DesignExtractor::getStmtNumber() == 0);
    DesignExtractor::incrementStmtNumber();
    REQUIRE(DesignExtractor::getStmtNumber() == 1);
    DesignExtractor::resetStmtNumber();
    REQUIRE(DesignExtractor::getStmtNumber() == 0);
  }

  SECTION("Extract valid program correctly") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "main"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "book"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    REQUIRE_NOTHROW(DesignExtractor::extract(tokens));
  }
}
