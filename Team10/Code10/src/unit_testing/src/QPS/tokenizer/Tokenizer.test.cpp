#include "../src/spa/QPS/include/tokenizer/Tokenizer.h"

#include <string>

#include "../fixtures/TestQueries.h"
#include "../src/spa/QPS/include/exception/GrammarRule.h"
#include "catch.hpp"

using namespace QPS;

TEST_CASE("Tokenizer can tokenize a valid query correctly", "[Tokenizer]") {
  SECTION("Simple tuple query") {
    std::vector<std::shared_ptr<Token>> tokens = Tokenizer::tokenize(
        const_cast<std::string&>(TestQueries::simpleTupleQuery));
    // assign a; variable v;
    // Select <a, v>
    REQUIRE(tokens.size() == 12);
    REQUIRE(tokens[0]->getType() == TokenType::NAME);
    REQUIRE(tokens[0]->getValue() == "assign");
    REQUIRE(tokens[1]->getType() == TokenType::NAME);
    REQUIRE(tokens[1]->getValue() == "a");
    REQUIRE(tokens[2]->getType() == TokenType::SEMICOLON);
    REQUIRE(tokens[2]->getValue() == ";");
    REQUIRE(tokens[3]->getType() == TokenType::NAME);
    REQUIRE(tokens[3]->getValue() == "variable");
    REQUIRE(tokens[4]->getType() == TokenType::NAME);
    REQUIRE(tokens[4]->getValue() == "v");
    REQUIRE(tokens[5]->getType() == TokenType::SEMICOLON);
    REQUIRE(tokens[5]->getValue() == ";");
    REQUIRE(tokens[6]->getType() == TokenType::NAME);
    REQUIRE(tokens[6]->getValue() == "Select");
    REQUIRE(tokens[7]->getType() == TokenType::OPEN_ANGLE_BRACKET);
    REQUIRE(tokens[7]->getValue() == "<");
    REQUIRE(tokens[8]->getType() == TokenType::NAME);
    REQUIRE(tokens[8]->getValue() == "a");
    REQUIRE(tokens[9]->getType() == TokenType::COMMA);
    REQUIRE(tokens[9]->getValue() == ",");
    REQUIRE(tokens[10]->getType() == TokenType::NAME);
    REQUIRE(tokens[10]->getValue() == "v");
    REQUIRE(tokens[11]->getType() == TokenType::CLOSE_ANGLE_BRACKET);
    REQUIRE(tokens[11]->getValue() == ">");
  }

  SECTION("Simple with query") {
    // stmt s;
    // Select s with s.stmt# = 1
    std::vector<std::shared_ptr<Token>> tokens = Tokenizer::tokenize(
        const_cast<std::string&>(TestQueries::simpleWithQuery));
    REQUIRE(tokens.size() == 11);
    REQUIRE(tokens[0]->getType() == TokenType::NAME);
    REQUIRE(tokens[0]->getValue() == "stmt");
    REQUIRE(tokens[1]->getType() == TokenType::NAME);
    REQUIRE(tokens[1]->getValue() == "s");
    REQUIRE(tokens[2]->getType() == TokenType::SEMICOLON);
    REQUIRE(tokens[2]->getValue() == ";");
    REQUIRE(tokens[3]->getType() == TokenType::NAME);
    REQUIRE(tokens[3]->getValue() == "Select");
    REQUIRE(tokens[4]->getType() == TokenType::NAME);
    REQUIRE(tokens[4]->getValue() == "s");
    REQUIRE(tokens[5]->getType() == TokenType::NAME);
    REQUIRE(tokens[5]->getValue() == "with");
    REQUIRE(tokens[6]->getType() == TokenType::NAME);
    REQUIRE(tokens[6]->getValue() == "s");
    REQUIRE(tokens[7]->getType() == TokenType::PERIOD);
    REQUIRE(tokens[7]->getValue() == ".");
    REQUIRE(tokens[8]->getType() == TokenType::ATTR_NAME);
    REQUIRE(tokens[8]->getValue() == "stmt#");
    REQUIRE(tokens[9]->getType() == TokenType::EQ);
    REQUIRE(tokens[9]->getValue() == "=");
    REQUIRE(tokens[10]->getType() == TokenType::INTEGER);
    REQUIRE(tokens[10]->getValue() == "1");
  }

  SECTION("Tuple query with attribute") {
    std::vector<std::shared_ptr<Token>> tokens = Tokenizer::tokenize(
        const_cast<std::string&>(TestQueries::tupleQueryWithAttr));
    // procedure p; assign a; variable v; constant cnst;
    // Select <p.procName, a.stmt#, v.varName, cnst.value>
    REQUIRE(tokens.size() == 30);
    REQUIRE(tokens[0]->getType() == TokenType::NAME);
    REQUIRE(tokens[0]->getValue() == "procedure");
    REQUIRE(tokens[1]->getType() == TokenType::NAME);
    REQUIRE(tokens[1]->getValue() == "p");
    REQUIRE(tokens[2]->getType() == TokenType::SEMICOLON);
    REQUIRE(tokens[2]->getValue() == ";");
    REQUIRE(tokens[3]->getType() == TokenType::NAME);
    REQUIRE(tokens[3]->getValue() == "assign");
    REQUIRE(tokens[4]->getType() == TokenType::NAME);
    REQUIRE(tokens[4]->getValue() == "a");
    REQUIRE(tokens[5]->getType() == TokenType::SEMICOLON);
    REQUIRE(tokens[5]->getValue() == ";");
    REQUIRE(tokens[6]->getType() == TokenType::NAME);
    REQUIRE(tokens[6]->getValue() == "variable");
    REQUIRE(tokens[7]->getType() == TokenType::NAME);
    REQUIRE(tokens[7]->getValue() == "v");
    REQUIRE(tokens[8]->getType() == TokenType::SEMICOLON);
    REQUIRE(tokens[8]->getValue() == ";");
    REQUIRE(tokens[9]->getType() == TokenType::NAME);
    REQUIRE(tokens[9]->getValue() == "constant");
    REQUIRE(tokens[10]->getType() == TokenType::NAME);
    REQUIRE(tokens[10]->getValue() == "cnst");
    REQUIRE(tokens[11]->getType() == TokenType::SEMICOLON);
    REQUIRE(tokens[11]->getValue() == ";");
    REQUIRE(tokens[12]->getType() == TokenType::NAME);
    REQUIRE(tokens[12]->getValue() == "Select");
    REQUIRE(tokens[13]->getType() == TokenType::OPEN_ANGLE_BRACKET);
    REQUIRE(tokens[13]->getValue() == "<");
    REQUIRE(tokens[14]->getType() == TokenType::NAME);
    REQUIRE(tokens[14]->getValue() == "p");
    REQUIRE(tokens[15]->getType() == TokenType::PERIOD);
    REQUIRE(tokens[15]->getValue() == ".");
    REQUIRE(tokens[16]->getType() == TokenType::ATTR_NAME);
    REQUIRE(tokens[16]->getValue() == "procName");
    REQUIRE(tokens[17]->getType() == TokenType::COMMA);
    REQUIRE(tokens[17]->getValue() == ",");
    REQUIRE(tokens[18]->getType() == TokenType::NAME);
    REQUIRE(tokens[18]->getValue() == "a");
    REQUIRE(tokens[19]->getType() == TokenType::PERIOD);
    REQUIRE(tokens[19]->getValue() == ".");
    REQUIRE(tokens[20]->getType() == TokenType::ATTR_NAME);
    REQUIRE(tokens[20]->getValue() == "stmt#");
    REQUIRE(tokens[21]->getType() == TokenType::COMMA);
    REQUIRE(tokens[21]->getValue() == ",");
    REQUIRE(tokens[22]->getType() == TokenType::NAME);
    REQUIRE(tokens[22]->getValue() == "v");
    REQUIRE(tokens[23]->getType() == TokenType::PERIOD);
    REQUIRE(tokens[23]->getValue() == ".");
    REQUIRE(tokens[24]->getType() == TokenType::ATTR_NAME);
    REQUIRE(tokens[24]->getValue() == "varName");
    REQUIRE(tokens[25]->getType() == TokenType::COMMA);
    REQUIRE(tokens[25]->getValue() == ",");
    REQUIRE(tokens[26]->getType() == TokenType::NAME);
    REQUIRE(tokens[26]->getValue() == "cnst");
    REQUIRE(tokens[27]->getType() == TokenType::PERIOD);
    REQUIRE(tokens[27]->getValue() == ".");
    REQUIRE(tokens[28]->getType() == TokenType::ATTR_NAME);
    REQUIRE(tokens[28]->getValue() == "value");
    REQUIRE(tokens[29]->getType() == TokenType::CLOSE_ANGLE_BRACKET);
    REQUIRE(tokens[29]->getValue() == ">");
  }

  SECTION("Complex valid query with simple pattern") {
    std::vector<std::shared_ptr<Token>> tokens = Tokenizer::tokenize(
        const_cast<std::string&>(TestQueries::complexValidQuery));
    // assign a; while w;
    // Select a such that Parent* (w, a) pattern a ("count", _)
    REQUIRE(tokens.size() == 25);
    REQUIRE(tokens[0]->getType() == TokenType::NAME);
    REQUIRE(tokens[0]->getValue() == "assign");
    REQUIRE(tokens[1]->getType() == TokenType::NAME);
    REQUIRE(tokens[1]->getValue() == "a");
    REQUIRE(tokens[2]->getType() == TokenType::SEMICOLON);
    REQUIRE(tokens[2]->getValue() == ";");
    REQUIRE(tokens[3]->getType() == TokenType::NAME);
    REQUIRE(tokens[3]->getValue() == "while");
    REQUIRE(tokens[4]->getType() == TokenType::NAME);
    REQUIRE(tokens[4]->getValue() == "w");
    REQUIRE(tokens[5]->getType() == TokenType::SEMICOLON);
    REQUIRE(tokens[5]->getValue() == ";");
    REQUIRE(tokens[6]->getType() == TokenType::NAME);
    REQUIRE(tokens[6]->getValue() == "Select");
    REQUIRE(tokens[7]->getType() == TokenType::NAME);
    REQUIRE(tokens[7]->getValue() == "a");
    REQUIRE(tokens[8]->getType() == TokenType::NAME);
    REQUIRE(tokens[8]->getValue() == "such");
    REQUIRE(tokens[9]->getType() == TokenType::NAME);
    REQUIRE(tokens[9]->getValue() == "that");
    REQUIRE(tokens[10]->getType() == TokenType::NAME);
    REQUIRE(tokens[10]->getValue() == "Parent*");
    REQUIRE(tokens[11]->getType() == TokenType::OPEN_BRACKET);
    REQUIRE(tokens[11]->getValue() == "(");
    REQUIRE(tokens[12]->getType() == TokenType::NAME);
    REQUIRE(tokens[12]->getValue() == "w");
    REQUIRE(tokens[13]->getType() == TokenType::COMMA);
    REQUIRE(tokens[13]->getValue() == ",");
    REQUIRE(tokens[14]->getType() == TokenType::NAME);
    REQUIRE(tokens[14]->getValue() == "a");
    REQUIRE(tokens[15]->getType() == TokenType::CLOSE_BRACKET);
    REQUIRE(tokens[15]->getValue() == ")");
    REQUIRE(tokens[16]->getType() == TokenType::NAME);
    REQUIRE(tokens[16]->getValue() == "pattern");
    REQUIRE(tokens[17]->getType() == TokenType::NAME);
    REQUIRE(tokens[17]->getValue() == "a");
    REQUIRE(tokens[18]->getType() == TokenType::OPEN_BRACKET);
    REQUIRE(tokens[18]->getValue() == "(");
    REQUIRE(tokens[19]->getType() == TokenType::DOUBLE_QUOTE);
    REQUIRE(tokens[19]->getValue() == "\"");
    REQUIRE(tokens[20]->getType() == TokenType::NAME);
    REQUIRE(tokens[20]->getValue() == "count");
    REQUIRE(tokens[21]->getType() == TokenType::DOUBLE_QUOTE);
    REQUIRE(tokens[21]->getValue() == "\"");
    REQUIRE(tokens[22]->getType() == TokenType::COMMA);
    REQUIRE(tokens[22]->getValue() == ",");
    REQUIRE(tokens[23]->getType() == TokenType::WILDCARD);
    REQUIRE(tokens[23]->getValue() == "_");
    REQUIRE(tokens[24]->getType() == TokenType::CLOSE_BRACKET);
    REQUIRE(tokens[24]->getValue() == ")");
  }

  SECTION("Complex valid query with complex pattern") {
    std::vector<std::shared_ptr<Token>> tokens = Tokenizer::tokenize(
        const_cast<std::string&>(TestQueries::complexValidQuery2));
    // assign a;
    // Select a pattern a ( "normSq" , _"cenX * cenX"_)
    REQUIRE(tokens.size() == 20);
    REQUIRE(tokens[0]->getType() == TokenType::NAME);
    REQUIRE(tokens[0]->getValue() == "assign");
    REQUIRE(tokens[1]->getType() == TokenType::NAME);
    REQUIRE(tokens[1]->getValue() == "a");
    REQUIRE(tokens[2]->getType() == TokenType::SEMICOLON);
    REQUIRE(tokens[2]->getValue() == ";");
    REQUIRE(tokens[3]->getType() == TokenType::NAME);
    REQUIRE(tokens[3]->getValue() == "Select");
    REQUIRE(tokens[4]->getType() == TokenType::NAME);
    REQUIRE(tokens[4]->getValue() == "a");
    REQUIRE(tokens[5]->getType() == TokenType::NAME);
    REQUIRE(tokens[5]->getValue() == "pattern");
    REQUIRE(tokens[6]->getType() == TokenType::NAME);
    REQUIRE(tokens[6]->getValue() == "a");
    REQUIRE(tokens[7]->getType() == TokenType::OPEN_BRACKET);
    REQUIRE(tokens[7]->getValue() == "(");
    REQUIRE(tokens[8]->getType() == TokenType::DOUBLE_QUOTE);
    REQUIRE(tokens[8]->getValue() == "\"");
    REQUIRE(tokens[9]->getType() == TokenType::NAME);
    REQUIRE(tokens[9]->getValue() == "normSq");
    REQUIRE(tokens[10]->getType() == TokenType::DOUBLE_QUOTE);
    REQUIRE(tokens[10]->getValue() == "\"");
    REQUIRE(tokens[11]->getType() == TokenType::COMMA);
    REQUIRE(tokens[11]->getValue() == ",");
    REQUIRE(tokens[12]->getType() == TokenType::WILDCARD);
    REQUIRE(tokens[12]->getValue() == "_");
    REQUIRE(tokens[13]->getType() == TokenType::DOUBLE_QUOTE);
    REQUIRE(tokens[13]->getValue() == "\"");
    REQUIRE(tokens[14]->getType() == TokenType::NAME);
    REQUIRE(tokens[14]->getValue() == "cenX");
    REQUIRE(tokens[15]->getType() == TokenType::TIMES);
    REQUIRE(tokens[15]->getValue() == "*");
    REQUIRE(tokens[16]->getType() == TokenType::NAME);
    REQUIRE(tokens[16]->getValue() == "cenX");
    REQUIRE(tokens[17]->getType() == TokenType::DOUBLE_QUOTE);
    REQUIRE(tokens[17]->getValue() == "\"");
    REQUIRE(tokens[18]->getType() == TokenType::WILDCARD);
    REQUIRE(tokens[18]->getValue() == "_");
    REQUIRE(tokens[19]->getType() == TokenType::CLOSE_BRACKET);
    REQUIRE(tokens[19]->getValue() == ")");
  }
}

TEST_CASE("Tokenizer can throw error query cannot be tokenized correctly",
          "[Tokenizer]") {
  SECTION("Empty query") {
    REQUIRE_THROWS_WITH(
        Tokenizer::tokenize(const_cast<std::string&>(TestQueries::emptyQuery)),
        "SyntaxError");
  }

  SECTION("Whitespace only query") {
    REQUIRE_THROWS_WITH(Tokenizer::tokenize(const_cast<std::string&>(
                            TestQueries::whitespaceQuery)),
                        "SyntaxError");
  }

  SECTION("Invalid char within query") {
    REQUIRE_THROWS_WITH(Tokenizer::tokenize(const_cast<std::string&>(
                            TestQueries::queryWithInvalidChar)),
                        "SyntaxError");
  }

  SECTION("Invalid name within query") {
    REQUIRE_THROWS_WITH(Tokenizer::tokenize(const_cast<std::string&>(
                            TestQueries::queryWithInvalidName)),
                        GrammarRule::NAME);
  }

  SECTION("Invalid integer within query") {
    REQUIRE_THROWS_WITH(Tokenizer::tokenize(const_cast<std::string&>(
                            TestQueries::queryWithInvalidInteger)),
                        GrammarRule::INTEGER);
  }

  SECTION("Invalid attribute name") {
    REQUIRE_THROWS_WITH(Tokenizer::tokenize(const_cast<std::string&>(
                            TestQueries::tupleQueryWithInvalidAttr)),
                        GrammarRule::ATTR_NAME);
  }

  SECTION("No attribute name after period") {
    REQUIRE_THROWS_WITH(Tokenizer::tokenize(const_cast<std::string&>(
                            TestQueries::tupleQueryWithoutAttrAfterPeriod)),
                        GrammarRule::ATTR_NAME);
  }
}