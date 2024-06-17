#include "tokenizer/SymbolTokenHandler.h"

#include "catch.hpp"

using namespace SP;

TEST_CASE("Create tokens from valid symbols", "[SymbolTokenHandler]") {
  auto tokenHandler = std::make_shared<SymbolTokenHandler>();

  SECTION(";") {
    std::string input = ";";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::SEMICOLON);
    REQUIRE(token->getValue() == ";");
  }

  SECTION("{") {
    std::string input = "{";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::OPEN_CURLY_BRACKET);
    REQUIRE(token->getValue() == "{");
  }

  SECTION("}") {
    std::string input = "}";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::CLOSE_CURLY_BRACKET);
    REQUIRE(token->getValue() == "}");
  }

  SECTION("(") {
    std::string input = "(";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::OPEN_BRACKET);
    REQUIRE(token->getValue() == "(");
  }

  SECTION(")") {
    std::string input = ")";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::CLOSE_BRACKET);
    REQUIRE(token->getValue() == ")");
  }

  SECTION("+") {
    std::string input = "+";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::PLUS);
    REQUIRE(token->getValue() == "+");
  }

  SECTION("-") {
    std::string input = "-";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::MINUS);
    REQUIRE(token->getValue() == "-");
  }

  SECTION("*") {
    std::string input = "*";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::MULTIPLY);
    REQUIRE(token->getValue() == "*");
  }

  SECTION("/") {
    std::string input = "/";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::DIVIDE);
    REQUIRE(token->getValue() == "/");
  }

  SECTION("%") {
    std::string input = "%";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::MODULO);
    REQUIRE(token->getValue() == "%");
  }

  SECTION("!") {
    std::string input = "!";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::NOT);
    REQUIRE(token->getValue() == "!");
  }

  SECTION("!=") {
    std::string input = "!=";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::NEQ);
    REQUIRE(token->getValue() == "!=");
  }

  SECTION("=") {
    std::string input = "=";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::ASSIGN);
    REQUIRE(token->getValue() == "=");
  }

  SECTION("==") {
    std::string input = "==";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::EQ);
    REQUIRE(token->getValue() == "==");
  }

  SECTION("<") {
    std::string input = "<";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::LT);
    REQUIRE(token->getValue() == "<");
  }

  SECTION("<=") {
    std::string input = "<=";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::LTE);
    REQUIRE(token->getValue() == "<=");
  }

  SECTION(">") {
    std::string input = ">";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::GT);
    REQUIRE(token->getValue() == ">");
  }

  SECTION(">=") {
    std::string input = ">=";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::GTE);
    REQUIRE(token->getValue() == ">=");
  }

  SECTION("&&") {
    std::string input = "&&";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::AND);
    REQUIRE(token->getValue() == "&&");
  }

  SECTION("||") {
    std::string input = "||";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    std::shared_ptr<Token> token = tokenHandler->handleToken(it, end);
    REQUIRE(token->getType() == TokenType::OR);
    REQUIRE(token->getValue() == "||");
  }
}

TEST_CASE("Invalid symbols", "[SymbolTokenHandler]") {
  auto tokenHandler = std::make_shared<SymbolTokenHandler>();

  SECTION("Empty string") {
    std::string input = "";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    REQUIRE_THROWS_WITH(tokenHandler->handleToken(it, end),
                        "Symbol not recognized: ");
  }

  SECTION("&") {
    std::string input = "&";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    REQUIRE_THROWS_WITH(tokenHandler->handleToken(it, end),
                        "Invalid token found: &");
  }

  SECTION("|") {
    std::string input = "|";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    REQUIRE_THROWS_WITH(tokenHandler->handleToken(it, end),
                        "Invalid token found: |");
  }

  SECTION("#") {
    std::string input = "#";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();
    REQUIRE_THROWS_WITH(tokenHandler->handleToken(it, end),
                        "Symbol not recognized: #");
  }
}
