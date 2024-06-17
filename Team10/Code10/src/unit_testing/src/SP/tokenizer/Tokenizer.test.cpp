#include "tokenizer/Tokenizer.h"

#include <string>

#include "../fixtures/TestSources.h"
#include "catch.hpp"

using namespace SP;

TEST_CASE("Tokenizer can tokenize a valid program correctly", "[Tokenizer]") {
  std::vector<std::unique_ptr<Token>> tokens =
      Tokenizer::tokenize(const_cast<std::string&>(TestSources::validSource));

  SECTION("tokens number are correct") { REQUIRE(tokens.size() == 136); }

  SECTION("token types are in correct order") {
    // touches most token types first
    REQUIRE(tokens[0]->getType() == TokenType::PROCEDURE);
    REQUIRE(tokens[1]->getType() == TokenType::NAME);
    REQUIRE(tokens[2]->getType() == TokenType::OPEN_CURLY_BRACKET);
    REQUIRE(tokens[3]->getType() == TokenType::NAME);
    REQUIRE(tokens[4]->getType() == TokenType::ASSIGN);
    REQUIRE(tokens[5]->getType() == TokenType::INTEGER);
    REQUIRE(tokens[6]->getType() == TokenType::SEMICOLON);
    REQUIRE(tokens[17]->getType() == TokenType::READ);
    REQUIRE(tokens[29]->getType() == TokenType::SEMICOLON);
    // extra whitespaces before the line `print centX`
    REQUIRE(tokens[30]->getType() == TokenType::PRINT);
    REQUIRE(tokens[39]->getType() == TokenType::CLOSE_CURLY_BRACKET);
    // extra next lines before the line `procedure computeCentroid {`
    REQUIRE(tokens[40]->getType() == TokenType::PROCEDURE);
    REQUIRE(tokens[58]->getType() == TokenType::WHILE);
    // double open brackets in while loop
    REQUIRE(tokens[59]->getType() == TokenType::OPEN_BRACKET);
    REQUIRE(tokens[60]->getType() == TokenType::OPEN_BRACKET);
    REQUIRE(tokens[61]->getType() == TokenType::NAME);
    REQUIRE(tokens[62]->getType() == TokenType::NEQ);
    REQUIRE(tokens[65]->getType() == TokenType::AND);
    REQUIRE(tokens[66]->getType() == TokenType::OPEN_BRACKET);
    // double close brackets in while loop
    REQUIRE(tokens[70]->getType() == TokenType::CLOSE_BRACKET);
    REQUIRE(tokens[71]->getType() == TokenType::CLOSE_BRACKET);
    // extra whitespaces before the line `if (count == 0) then {`
    REQUIRE(tokens[95]->getType() == TokenType::IF);
    REQUIRE(tokens[98]->getType() == TokenType::EQ);
    REQUIRE(tokens[101]->getType() == TokenType::THEN);
    REQUIRE(tokens[108]->getType() == TokenType::ELSE);
    REQUIRE(tokens[113]->getType() == TokenType::DIVIDE);
    REQUIRE(tokens[124]->getType() == TokenType::ASSIGN);
    // `centX` at the start of line without preceding whitespace
    REQUIRE(tokens[125]->getType() == TokenType::NAME);
    REQUIRE(tokens[132]->getType() == TokenType::SEMICOLON);
    // extra semicolons at the end of the line `cenX * cenX + cenY * cenY;`
    REQUIRE(tokens[133]->getType() == TokenType::SEMICOLON);
    REQUIRE(tokens[134]->getType() == TokenType::SEMICOLON);
    REQUIRE(tokens[135]->getType() == TokenType::CLOSE_CURLY_BRACKET);
  }
}

TEST_CASE("Tokenizer can throw error if contains invalid token",
          "[Tokenizer]") {
  SECTION("correct error message is thrown") {
    REQUIRE_THROWS_WITH(
        Tokenizer::tokenize(const_cast<std::string&>(TestSources::emptySource)),
        "Empty source");

    REQUIRE_THROWS_WITH(Tokenizer::tokenize(const_cast<std::string&>(
                            TestSources::sourceWithInvalidCharacter)),
                        "Invalid character: #");

    REQUIRE_THROWS_WITH(Tokenizer::tokenize(const_cast<std::string&>(
                            TestSources::sourceWithInvalidVariable)),
                        "Invalid name");

    REQUIRE_THROWS_WITH(Tokenizer::tokenize(const_cast<std::string&>(
                            TestSources::sourceWithInvalidNumber)),
                        "Invalid number");
  }
}
