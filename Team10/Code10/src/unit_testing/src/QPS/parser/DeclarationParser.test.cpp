#include "parser/DeclarationParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "tokenizer/Token.h"

using namespace QPS;

TEST_CASE("DeclarationParser can parse declarations correctly",
          "[QPS][Parser]") {
  SECTION("Valid declaration list with one design entity and one synonym") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
    };

    std::unordered_map<std::string, SynonymType> expected = {
        {"a", SynonymType::ASSIGN}};
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unordered_map<std::string, SynonymType> actual =
        DeclarationParser::parse(it, end);
    REQUIRE(actual == expected);
  }

  SECTION("Valid declaration list with one design entity and two synonyms") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "b"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
    };

    std::unordered_map<std::string, SynonymType> expected = {
        {"a", SynonymType::ASSIGN}, {"b", SynonymType::ASSIGN}};
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unordered_map<std::string, SynonymType> actual =
        DeclarationParser::parse(it, end);
    REQUIRE(actual == expected);
  }

  SECTION("Valid declaration list with two design entities and two synonyms") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "b"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "y"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
    };

    std::unordered_map<std::string, SynonymType> expected = {
        {"a", SynonymType::ASSIGN},
        {"b", SynonymType::ASSIGN},
        {"x", SynonymType::VARIABLE},
        {"y", SynonymType::VARIABLE}};
    auto it = tokens.begin();
    auto end = tokens.end();
    std::unordered_map<std::string, SynonymType> actual =
        DeclarationParser::parse(it, end);
    REQUIRE(actual == expected);
  }
}
