#include "../src/spa/QPS/include/parser/Parser.h"
#include "../src/spa/QPS/include/tokenizer/Tokenizer.h"
#include "../src/spa/QPS/include/validator/Validator.h"
#include "catch.hpp"
#include "fixtures/Strategies.h"
#include "fixtures/ValidQueries.h"
#include "strategy/Strategy.h"
#include "strategy/WithStrategy.h"
#include "strategy/strategy_types/EntEntArgStrategy.h"
#include "strategy/strategy_types/PatternStrategy.h"
#include "strategy/strategy_types/StmtEntArgStrategy.h"
#include "strategy/strategy_types/StmtStmtArgStrategy.h"

using namespace QPS;

// QPS::Tokenizer integration with QPS::Validator and QPS::Parser

TEST_CASE("Valid PQL queries", "[QPS:Tokenizer-Validator-Parser]") {
  SECTION("Simple single select query") {
    std::vector<std::shared_ptr<Token>> tokens =
        Tokenizer::tokenize(ValidQueries::simpleSingleSelectQuery);
    REQUIRE_NOTHROW(Validator::validate(tokens));

    std::vector<std::shared_ptr<Strategy>> strategies = Parser::parse(tokens);
    REQUIRE(strategies.size() == 2);
    REQUIRE(strategies[0]->isSelectTupleStrategy() == true);
  }

  SECTION("Simple boolean select query") {
    std::vector<std::shared_ptr<Token>> tokens =
        Tokenizer::tokenize(ValidQueries::simpleBooleanSelectQuery);
    REQUIRE_NOTHROW(Validator::validate(tokens));

    std::vector<std::shared_ptr<Strategy>> strategies = Parser::parse(tokens);
    REQUIRE(strategies.size() == 2);
    REQUIRE(strategies[0]->isSelectBooleanStrategy() == true);
  }

  SECTION("Simple tuple select query") {
    std::vector<std::shared_ptr<Token>> tokens =
        Tokenizer::tokenize(ValidQueries::simpleTupleSelectQuery);
    REQUIRE_NOTHROW(Validator::validate(tokens));

    std::vector<std::shared_ptr<Strategy>> strategies = Parser::parse(tokens);
    REQUIRE(strategies.size() == 2);
    REQUIRE(strategies[0]->isSelectTupleStrategy() == true);
  }

  SECTION("Complex multi clause query") {
    std::vector<std::shared_ptr<Token>> tokens =
        Tokenizer::tokenize(ValidQueries::complexQuery);
    REQUIRE_NOTHROW(Validator::validate(tokens));

    std::vector<std::shared_ptr<Strategy>> strategies = Parser::parse(tokens);
    REQUIRE(strategies.size() == 19);
    // Check that strategy types are correct
    auto &strategy1 = *strategies[0];
    auto &strategy2 = *strategies[1];
    auto &strategy3 = *strategies[2];
    auto &strategy4 = *strategies[3];
    auto &strategy5 = *strategies[4];
    auto &strategy6 = *strategies[5];
    auto &strategy7 = *strategies[6];
    auto &strategy8 = *strategies[7];
    auto &strategy9 = *strategies[8];
    auto &strategy10 = *strategies[9];
    auto &strategy11 = *strategies[10];
    auto &strategy12 = *strategies[11];
    auto &strategy13 = *strategies[12];
    auto &strategy14 = *strategies[13];
    auto &strategy15 = *strategies[14];
    auto &strategy16 = *strategies[15];
    auto &strategy17 = *strategies[16];
    auto &strategy18 = *strategies[17];
    auto &strategy19 = *strategies[18];
    REQUIRE(strategy1.isSelectTupleStrategy() == true);
    REQUIRE(typeid(strategy2) == typeid(PatternStrategy));
    REQUIRE(typeid(strategy3) == typeid(StmtEntArgStrategy));
    REQUIRE(typeid(strategy4) == typeid(EntEntArgStrategy));
    REQUIRE(typeid(strategy5) == typeid(StmtEntArgStrategy));
    REQUIRE(typeid(strategy6) == typeid(EntEntArgStrategy));
    REQUIRE(typeid(strategy7) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(strategy8) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(strategy9) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(strategy10) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(strategy11) == typeid(EntEntArgStrategy));
    REQUIRE(typeid(strategy12) == typeid(EntEntArgStrategy));
    REQUIRE(typeid(strategy13) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(strategy14) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(strategy15) == typeid(StmtStmtArgStrategy));
    REQUIRE(typeid(strategy16) == typeid(WithStrategy));
    REQUIRE(typeid(strategy17) == typeid(WithStrategy));
    REQUIRE(typeid(strategy18) == typeid(PatternStrategy));
    REQUIRE(typeid(strategy19) == typeid(PatternStrategy));
  }

  SECTION("Query with whitespaces") {
    std::vector<std::shared_ptr<Token>> tokens =
        Tokenizer::tokenize(ValidQueries::queryWithWhitespaces);
    REQUIRE_NOTHROW(Validator::validate(tokens));

    std::vector<std::shared_ptr<Strategy>> strategies = Parser::parse(tokens);
    REQUIRE(strategies.size() == 2);
  }

  SECTION("Query with keywords as synonyms") {
    std::vector<std::shared_ptr<Token>> tokens =
        Tokenizer::tokenize(ValidQueries::queryWithKeywordsAsSynonyms);
    REQUIRE_NOTHROW(Validator::validate(tokens));

    std::vector<std::shared_ptr<Strategy>> strategies = Parser::parse(tokens);
    REQUIRE(strategies.size() == 6);
  }
}
