#include "FileReader.h"
#include "catch.hpp"
#include "parser/Parser.h"
#include "tokenizer/Tokenizer.h"

using namespace SP;
const std::string sourceDir =
    "../src/integration_testing/src/SP/fixtures/source/";

TEST_CASE("Valid source input", "[SP:Tokenizer-Parser]") {
  SECTION("Single procedure with all statement types except call") {
    std::string sourceFile = sourceDir + "valid-source.txt";
    FileReader fileReader{sourceFile};
    std::string source = fileReader.getContent();
    std::vector<std::unique_ptr<Token>> tokens = Tokenizer::tokenize(source);
    REQUIRE_NOTHROW(Parser::parse(tokens));
  }

  SECTION("Multiple procedures with all statement types except call") {
    std::string sourceFile = sourceDir + "valid-source-2.txt";
    FileReader fileReader{sourceFile};
    std::string source = fileReader.getContent();
    std::vector<std::unique_ptr<Token>> tokens = Tokenizer::tokenize(source);
    REQUIRE_NOTHROW(Parser::parse(tokens));
  }

  SECTION("Mix of weird but valid usage of whitespaces") {
    std::string sourceFile = sourceDir + "valid-source-3.txt";
    FileReader fileReader{sourceFile};
    std::string source = fileReader.getContent();
    std::vector<std::unique_ptr<Token>> tokens = Tokenizer::tokenize(source);
    REQUIRE_NOTHROW(Parser::parse(tokens));
  }

  SECTION("Procedure and variable names same as keywords") {
    std::string sourceFile = sourceDir + "valid-source-4.txt";
    FileReader fileReader{sourceFile};
    std::string source = fileReader.getContent();
    std::vector<std::unique_ptr<Token>> tokens = Tokenizer::tokenize(source);
    REQUIRE_NOTHROW(Parser::parse(tokens));
    // keyword token types are now NAME
    REQUIRE(tokens[1]->getType() == TokenType::NAME);
    REQUIRE(tokens[1]->getValue() == "procedure");
    REQUIRE(tokens[4]->getType() == TokenType::NAME);
    REQUIRE(tokens[4]->getValue() == "print");
    REQUIRE(tokens[7]->getType() == TokenType::NAME);
    REQUIRE(tokens[7]->getValue() == "read");
    REQUIRE(tokens[9]->getType() == TokenType::NAME);
    REQUIRE(tokens[9]->getValue() == "if");
    REQUIRE(tokens[11]->getType() == TokenType::NAME);
    REQUIRE(tokens[11]->getValue() == "then");
    REQUIRE(tokens[13]->getType() == TokenType::NAME);
    REQUIRE(tokens[13]->getValue() == "else");
    REQUIRE(tokens[17]->getType() == TokenType::NAME);
    REQUIRE(tokens[17]->getValue() == "if");
    REQUIRE(tokens[19]->getType() == TokenType::NAME);
    REQUIRE(tokens[19]->getValue() == "if");
    REQUIRE(tokens[22]->getType() == TokenType::NAME);
    REQUIRE(tokens[22]->getValue() == "if");
    REQUIRE(tokens[24]->getType() == TokenType::NAME);
    REQUIRE(tokens[24]->getValue() == "if");
    REQUIRE(tokens[31]->getType() == TokenType::NAME);
    REQUIRE(tokens[31]->getValue() == "while");
    REQUIRE(tokens[33]->getType() == TokenType::NAME);
    REQUIRE(tokens[33]->getValue() == "while");
    REQUIRE(tokens[41]->getType() == TokenType::NAME);
    REQUIRE(tokens[41]->getValue() == "then");
    REQUIRE(tokens[50]->getType() == TokenType::NAME);
    REQUIRE(tokens[50]->getValue() == "else");
  }

  SECTION("Deeply nested container statement") {
    std::string sourceFile = sourceDir + "valid-source-5.txt";
    FileReader fileReader{sourceFile};
    std::string source = fileReader.getContent();
    std::vector<std::unique_ptr<Token>> tokens = Tokenizer::tokenize(source);
    REQUIRE_NOTHROW(Parser::parse(tokens));
  }

  SECTION("Complex conditional expression with complex expression nested") {
    std::string sourceFile = sourceDir + "valid-source-6.txt";
    FileReader fileReader{sourceFile};
    std::string source = fileReader.getContent();
    std::vector<std::unique_ptr<Token>> tokens = Tokenizer::tokenize(source);
    REQUIRE_NOTHROW(Parser::parse(tokens));
  }
}
