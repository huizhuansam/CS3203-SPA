#include "validator/syntax_validator/SyntaxValidator.h"

#include <memory>
#include <vector>

#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "../src/spa/QPS/include/tokenizer/Token.h"
#include "../src/spa/QPS/include/tokenizer/TokenType.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("Syntax validator valid scenraio", "[QPS][Validator][Success]") {
  SyntaxValidator validator;

  std::vector<std::shared_ptr<Token>> tokens{
      std::make_shared<Token>(TokenType::NAME, "assign"),
      std::make_shared<Token>(TokenType::NAME, "a"),
      std::make_shared<Token>(TokenType::SEMICOLON, ";"),
      std::make_shared<Token>(TokenType::NAME, "Select"),
      std::make_shared<Token>(TokenType::NAME, "a"),
      std::make_shared<Token>(TokenType::NAME, "pattern"),
      std::make_shared<Token>(TokenType::NAME, "a"),
      std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
      std::make_shared<Token>(TokenType::WILDCARD, "_"),
      std::make_shared<Token>(TokenType::COMMA, ","),
      std::make_shared<Token>(TokenType::WILDCARD, "_"),
      std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
  };
  auto it = tokens.begin();
  auto end = tokens.end();
  REQUIRE_NOTHROW(validator.validate(it, end));
}
