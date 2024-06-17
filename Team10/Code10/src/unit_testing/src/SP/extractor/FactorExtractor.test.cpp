#include "extractor/FactorExtractor.h"

#include <memory>
#include <vector>

#include "WriteFacadeStub.h"
#include "catch.hpp"
#include "tokenizer/Token.h"

using namespace SP;

TEST_CASE("Factor extractor extract valid constant correctly", "[Extractor]") {
  WriteFacade writer{};
  FactorExtractor extractor{writer};

  SECTION("Do not throw error when extracting single digit constant") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
  }

  SECTION("Do not throw error when extracting double digits constant") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "69"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
  }

  SECTION("Points to correct token after extracting constant") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getType() == TokenType::MULTIPLY);
    REQUIRE((*it)->getValue() == "*");
  }
}

TEST_CASE("Factor extractor extracts valid variable correctly", "[Extractor]") {
  WriteFacade writer{};
  FactorExtractor extractor{writer};

  SECTION(
      "Do not throw error when extracting single character "
      "variable") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "z"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
  }

  SECTION(
      "Do not throw error when extracting multiple characters "
      "variable") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "t3slA"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
  }

  SECTION("Do not throw error when extracting reserve word as variable") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "else"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
  }

  SECTION("Points to correct token after extracting variable") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "xYz"));
    tokens.push_back(std::make_unique<Token>(TokenType::DIVIDE, "/"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getType() == TokenType::DIVIDE);
    REQUIRE((*it)->getValue() == "/");
  }
}

TEST_CASE("Factor extractor extract valid expression correctly",
          "[Extractor]") {
  WriteFacade writer{};
  FactorExtractor extractor{writer};

  SECTION("Do not throw error when extracting valid expression") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "a")));
    tokens.push_back((std::make_unique<Token>(TokenType::PLUS, "+")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "b")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
  }

  SECTION("Do not throw error when extracting nested expression") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "a")));
    tokens.push_back((std::make_unique<Token>(TokenType::PLUS, "+")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "b")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
  }

  SECTION("Points to correct token after extracting expression") {
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back((std::make_unique<Token>(TokenType::OPEN_BRACKET, "(")));
    tokens.push_back((std::make_unique<Token>(TokenType::NAME, "x")));
    tokens.push_back((std::make_unique<Token>(TokenType::MODULO, "%")));
    tokens.push_back((std::make_unique<Token>(TokenType::INTEGER, "2")));
    tokens.push_back((std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")")));
    tokens.push_back((std::make_unique<Token>(TokenType::SEMICOLON, ";")));
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(extractor.extract(it, end));
    REQUIRE((*it)->getType() == TokenType::SEMICOLON);
    REQUIRE((*it)->getValue() == ";");
  }
}
