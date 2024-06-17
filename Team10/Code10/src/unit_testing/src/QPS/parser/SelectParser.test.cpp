#include "parser/SelectParser.h"

#include <memory>
#include <vector>

#include "catch.hpp"
#include "strategy/argument_types/SynonymType.h"

using namespace QPS;

TEST_CASE("SelectParser can parse select elem clause correctly",
          "[QPS][Parser]") {
  SECTION("Single select synonym clause") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "a")};

    std::unordered_map<std::string, SynonymType> map = {
        {"a", SynonymType::ASSIGN}};

    std::vector<std::string> expectedSynonym = {"a"};
    std::vector<SynonymType> expectedSynonymType = {SynonymType::ASSIGN};
    std::vector<AttrNameType> expectedAttrNameType = {AttrNameType::NONE};

    auto it = tokens.begin();
    const auto end = tokens.end();
    TupleSelectStrategy actual =
        *(SelectParser::parseTupleSelect(it, end, map));
    REQUIRE(typeid(actual) == typeid(TupleSelectStrategy));
    REQUIRE(actual.getTupleSynonyms() == expectedSynonym);
    REQUIRE(actual.getSynonymTypes() == expectedSynonymType);
    REQUIRE(actual.getAttrNameTypes() == expectedAttrNameType);
  }

  SECTION("Single select synonym.stmt# clause") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "stmt#")};

    std::unordered_map<std::string, SynonymType> map = {
        {"a", SynonymType::ASSIGN}};

    std::vector<std::string> expectedSynonym = {"a"};
    std::vector<SynonymType> expectedSynonymType = {SynonymType::ASSIGN};
    std::vector<AttrNameType> expectedAttrNameType = {AttrNameType::INTEGER};

    auto it = tokens.begin();
    const auto end = tokens.end();
    TupleSelectStrategy actual =
        *(SelectParser::parseTupleSelect(it, end, map));
    REQUIRE(actual.getTupleSynonyms() == expectedSynonym);
    REQUIRE(actual.getSynonymTypes() == expectedSynonymType);
    REQUIRE(actual.getAttrNameTypes() == expectedAttrNameType);
  }

  SECTION("Single select synonym.value clause") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "cnst"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "value")};

    std::unordered_map<std::string, SynonymType> map = {
        {"cnst", SynonymType::CONSTANT}};

    std::vector<std::string> expectedSynonym = {"cnst"};
    std::vector<SynonymType> expectedSynonymType = {SynonymType::CONSTANT};
    std::vector<AttrNameType> expectedAttrNameType = {AttrNameType::INTEGER};

    auto it = tokens.begin();
    const auto end = tokens.end();
    TupleSelectStrategy actual =
        *(SelectParser::parseTupleSelect(it, end, map));
    REQUIRE(actual.getTupleSynonyms() == expectedSynonym);
    REQUIRE(actual.getSynonymTypes() == expectedSynonymType);
    REQUIRE(actual.getAttrNameTypes() == expectedAttrNameType);
  }

  SECTION("Single select synonym.procName clause") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "call"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "procName")};

    std::unordered_map<std::string, SynonymType> map = {
        {"call", SynonymType::CALL}};

    std::vector<std::string> expectedSynonym = {"call"};
    std::vector<SynonymType> expectedSynonymType = {SynonymType::CALL};
    std::vector<AttrNameType> expectedAttrNameType = {AttrNameType::NAME};

    auto it = tokens.begin();
    const auto end = tokens.end();
    TupleSelectStrategy actual =
        *(SelectParser::parseTupleSelect(it, end, map));
    REQUIRE(actual.getTupleSynonyms() == expectedSynonym);
    REQUIRE(actual.getSynonymTypes() == expectedSynonymType);
    REQUIRE(actual.getAttrNameTypes() == expectedAttrNameType);
  }

  SECTION("Single select synonym.varName clause") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "r"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "varName")};

    std::unordered_map<std::string, SynonymType> map = {
        {"r", SynonymType::READ}};

    std::vector<std::string> expectedSynonym = {"r"};
    std::vector<SynonymType> expectedSynonymType = {SynonymType::READ};
    std::vector<AttrNameType> expectedAttrNameType = {AttrNameType::NAME};

    auto it = tokens.begin();
    const auto end = tokens.end();
    TupleSelectStrategy actual =
        *(SelectParser::parseTupleSelect(it, end, map));
    REQUIRE(actual.getTupleSynonyms() == expectedSynonym);
    REQUIRE(actual.getSynonymTypes() == expectedSynonymType);
    REQUIRE(actual.getAttrNameTypes() == expectedAttrNameType);
  }
}

TEST_CASE("SelectParser can parse select boolean clause correctly",
          "[QPS][Parser]") {
  SECTION("Boolean select clause") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN")};

    auto it = tokens.begin();
    BooleanSelectStrategy actual = *(SelectParser::parseBooleanSelect(it));
    REQUIRE(typeid(actual) == typeid(BooleanSelectStrategy));
  }
}

TEST_CASE("SelectParser can parse select tuple clause correctly",
          "[QPS][Parser]") {
  SECTION("Select tuple of synonyms") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "q"),
        std::make_shared<Token>(TokenType::CLOSE_ANGLE_BRACKET, ">")};

    std::unordered_map<std::string, SynonymType> map = {
        {"p", SynonymType::PROCEDURE}, {"q", SynonymType::PROCEDURE}};

    std::vector<std::string> expectedSynonyms = {"p", "q"};
    std::vector<SynonymType> expectedSynonymTypes = {SynonymType::PROCEDURE,
                                                     SynonymType::PROCEDURE};
    std::vector<AttrNameType> expectedAttrNameTypes = {AttrNameType::NONE,
                                                       AttrNameType::NONE};

    auto it = tokens.begin();
    const auto end = tokens.end();
    TupleSelectStrategy actual =
        *(SelectParser::parseTupleSelect(it, end, map));
    REQUIRE(actual.getTupleSynonyms() == expectedSynonyms);
    REQUIRE(actual.getSynonymTypes() == expectedSynonymTypes);
    REQUIRE(actual.getAttrNameTypes() == expectedAttrNameTypes);
  }

  SECTION("Select tuple of attrRefs") {
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "procName"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "stmt#"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "varName"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "cnst"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "value"),
        std::make_shared<Token>(TokenType::CLOSE_ANGLE_BRACKET, ">")};

    std::unordered_map<std::string, SynonymType> map = {
        {"p", SynonymType::PROCEDURE},
        {"a", SynonymType::ASSIGN},
        {"v", SynonymType::VARIABLE},
        {"cnst", SynonymType::CONSTANT}};

    std::vector<std::string> expectedSynonyms = {"p", "a", "v", "cnst"};
    std::vector<SynonymType> expectedSynonymTypes = {
        SynonymType::PROCEDURE, SynonymType::ASSIGN, SynonymType::VARIABLE,
        SynonymType::CONSTANT};
    std::vector<AttrNameType> expectedAttrNameTypes = {
        AttrNameType::NAME, AttrNameType::INTEGER, AttrNameType::NAME,
        AttrNameType::INTEGER};

    auto it = tokens.begin();
    const auto end = tokens.end();
    TupleSelectStrategy actual =
        *(SelectParser::parseTupleSelect(it, end, map));
    REQUIRE(actual.getTupleSynonyms() == expectedSynonyms);
    REQUIRE(actual.getSynonymTypes() == expectedSynonymTypes);
    REQUIRE(actual.getAttrNameTypes() == expectedAttrNameTypes);
  }
}
