#include <memory>

#include "ReadFacadeStub.h"
#include "catch.hpp"
#include "result/Result.h"
#include "strategy/Strategy.h"
#include "strategy/TupleSelectStrategy.h"
#include "strategy/argument_types/SynonymType.h"

using namespace QPS;

namespace TupleSelectStrategyTest {
ReadFacadeStub readFacadeStub = ReadFacadeStub();

std::shared_ptr<Strategy> STMT = std::make_shared<TupleSelectStrategy>(
    std::vector<std::string>{"s"}, std::vector<SynonymType>{SynonymType::STMT},
    std::vector<AttrNameType>{AttrNameType::NONE});
std::shared_ptr<Strategy> READ = std::make_shared<TupleSelectStrategy>(
    std::vector<std::string>{"r"}, std::vector<SynonymType>{SynonymType::READ},
    std::vector<AttrNameType>{AttrNameType::NONE});
std::shared_ptr<Strategy> PRINT = std::make_shared<TupleSelectStrategy>(
    std::vector<std::string>{"p"}, std::vector<SynonymType>{SynonymType::PRINT},
    std::vector<AttrNameType>{AttrNameType::NONE});
std::shared_ptr<Strategy> CALL = std::make_shared<TupleSelectStrategy>(
    std::vector<std::string>{"c"}, std::vector<SynonymType>{SynonymType::CALL},
    std::vector<AttrNameType>{AttrNameType::NONE});
std::shared_ptr<Strategy> WHILE = std::make_shared<TupleSelectStrategy>(
    std::vector<std::string>{"w"}, std::vector<SynonymType>{SynonymType::WHILE},
    std::vector<AttrNameType>{AttrNameType::NONE});
std::shared_ptr<Strategy> IF = std::make_shared<TupleSelectStrategy>(
    std::vector<std::string>{"i"}, std::vector<SynonymType>{SynonymType::IF},
    std::vector<AttrNameType>{AttrNameType::NONE});
std::shared_ptr<Strategy> ASSIGN = std::make_shared<TupleSelectStrategy>(
    std::vector<std::string>{"a"},
    std::vector<SynonymType>{SynonymType::ASSIGN},
    std::vector<AttrNameType>{AttrNameType::NONE});
std::shared_ptr<Strategy> VARIABLE = std::make_shared<TupleSelectStrategy>(
    std::vector<std::string>{"v"},
    std::vector<SynonymType>{SynonymType::VARIABLE},
    std::vector<AttrNameType>{AttrNameType::NONE});
std::shared_ptr<Strategy> CONSTANT = std::make_shared<TupleSelectStrategy>(
    std::vector<std::string>{"c"},
    std::vector<SynonymType>{SynonymType::CONSTANT},
    std::vector<AttrNameType>{AttrNameType::NONE});
std::shared_ptr<Strategy> PROCEDURE = std::make_shared<TupleSelectStrategy>(
    std::vector<std::string>{"p"},
    std::vector<SynonymType>{SynonymType::PROCEDURE},
    std::vector<AttrNameType>{AttrNameType::NONE});

Result STMT_EXPECTED = Result(
    {
        {"s", 0},
    },
    {{"1"}, {"2"}, {"3"}, {"4"}, {"5"}, {"6"}});
Result READ_EXPECTED = Result(
    {
        {"r", 0},
        {"r.varName", 1},
    },
    {{"14", "v"}, {"16", "v"}, {"17", "v"}});
Result PRINT_EXPECTED = Result(
    {
        {"p", 0},
        {"p.varName", 1},
    },
    {{"1", "v"}, {"2", "v"}, {"12", "v"}, {"15", "v"}});
Result CALL_EXPECTED = Result(
    {
        {"c", 0},
        {"c.procName", 1},
    },
    {{"7", "proc"}, {"8", "proc"}, {"9", "proc"}});
Result WHILE_EXPECTED = Result(
    {
        {"w", 0},
    },
    {{"3"}, {"10"}, {"11"}});
Result IF_EXPECTED = Result({{"i", 0}}, {{"4"}, {"8"}});
Result ASSIGN_EXPECTED = Result(
    {
        {"a", 0},
    },
    {
        {"1"},
        {"2"},
        {"5"},
        {"6"},
        {"7"},
        {"9"},
        {"10"},
        {"13"},
    });
Result VARIABLE_EXPECTED = Result(
    {
        {"v", 0},
    },
    {{"a"}, {"b"}, {"c"}});
Result CONSTANT_EXPECTED = Result(
    {
        {"c", 0},
    },
    {
        {"0"},
        {"7"},
        {"8"},
        {"9"},
        {"20"},
        {"1"},
        {"2"},
    });
Result PROCEDURE_EXPECTED = Result(
    {
        {"p", 0},
    },
    {{"main"}, {"call"}, {"b"}});

std::list<std::string> flattenAndSortResult(std::vector<std::string> headers,
                                            Result& result) {
  std::list<std::list<std::string>> resultData;
  result.getDataByHeaderNames(headers, resultData);
  std::list<std::string> flatResult;
  Result::flattenData(resultData, flatResult);
  flatResult.sort();
  return flatResult;
}

TEST_CASE("TupleSelectStrategy calls correct endpoints.",
          "[QPS] [Strategy] [Select] [Single]") {
  SECTION("STMT") {
    Result result = STMT->evaluateValues(readFacadeStub);
    std::list<std::string> flatResult = flattenAndSortResult({"s"}, result);
    std::list<std::string> flatExpected =
        flattenAndSortResult({"s"}, STMT_EXPECTED);
    REQUIRE(result.getHeaders() == STMT_EXPECTED.getHeaders());
    REQUIRE(flatResult == flatExpected);
  }

  SECTION("READ") {
    Result result = READ->evaluateValues(readFacadeStub);
    std::list<std::string> flatResult = flattenAndSortResult({"r"}, result);
    std::list<std::string> flatExpected =
        flattenAndSortResult({"r"}, READ_EXPECTED);
    REQUIRE(result.getHeaders() == READ_EXPECTED.getHeaders());
    REQUIRE(flatResult == flatExpected);
  }

  SECTION("PRINT") {
    Result result = PRINT->evaluateValues(readFacadeStub);
    std::list<std::string> flatResult = flattenAndSortResult({"p"}, result);
    std::list<std::string> flatExpected =
        flattenAndSortResult({"p"}, PRINT_EXPECTED);
    REQUIRE(result.getHeaders() == PRINT_EXPECTED.getHeaders());
    REQUIRE(flatResult == flatExpected);
  }

  SECTION("CALL") {
    Result result = CALL->evaluateValues(readFacadeStub);
    std::list<std::string> flatResult = flattenAndSortResult({"c"}, result);
    std::list<std::string> flatExpected =
        flattenAndSortResult({"c"}, CALL_EXPECTED);
    REQUIRE(result.getHeaders() == CALL_EXPECTED.getHeaders());
    REQUIRE(flatResult == flatExpected);
  }

  SECTION("WHILE") {
    Result result = WHILE->evaluateValues(readFacadeStub);
    std::list<std::string> flatResult = flattenAndSortResult({"w"}, result);
    std::list<std::string> flatExpected =
        flattenAndSortResult({"w"}, WHILE_EXPECTED);
    REQUIRE(result.getHeaders() == WHILE_EXPECTED.getHeaders());
    REQUIRE(flatResult == flatExpected);
  }

  SECTION("IF") {
    Result result = IF->evaluateValues(readFacadeStub);
    std::list<std::string> flatResult = flattenAndSortResult({"i"}, result);
    std::list<std::string> flatExpected =
        flattenAndSortResult({"i"}, IF_EXPECTED);
    REQUIRE(result.getHeaders() == IF_EXPECTED.getHeaders());
    REQUIRE(flatResult == flatExpected);
  }

  SECTION("ASSIGN") {
    Result result = ASSIGN->evaluateValues(readFacadeStub);
    std::list<std::string> flatResult = flattenAndSortResult({"a"}, result);
    std::list<std::string> flatExpected =
        flattenAndSortResult({"a"}, ASSIGN_EXPECTED);
    REQUIRE(result.getHeaders() == ASSIGN_EXPECTED.getHeaders());
    REQUIRE(flatResult == flatExpected);
  }

  SECTION("VARIABLE") {
    Result result = VARIABLE->evaluateValues(readFacadeStub);
    std::list<std::string> flatResult = flattenAndSortResult({"v"}, result);
    std::list<std::string> flatExpected =
        flattenAndSortResult({"v"}, VARIABLE_EXPECTED);
    REQUIRE(result.getHeaders() == VARIABLE_EXPECTED.getHeaders());
    REQUIRE(flatResult == flatExpected);
  }

  SECTION("CONSTANT") {
    Result result = CONSTANT->evaluateValues(readFacadeStub);
    std::list<std::string> flatResult = flattenAndSortResult({"c"}, result);
    std::list<std::string> flatExpected =
        flattenAndSortResult({"c"}, CONSTANT_EXPECTED);
    REQUIRE(result.getHeaders() == CONSTANT_EXPECTED.getHeaders());
    REQUIRE(flatResult == flatExpected);
  }

  SECTION("PROCEDURE") {
    Result result = PROCEDURE->evaluateValues(readFacadeStub);
    std::list<std::string> flatResult = flattenAndSortResult({"p"}, result);
    std::list<std::string> flatExpected =
        flattenAndSortResult({"p"}, PROCEDURE_EXPECTED);
    REQUIRE(result.getHeaders() == PROCEDURE_EXPECTED.getHeaders());
    REQUIRE(flatResult == flatExpected);
  }
}
}  // namespace TupleSelectStrategyTest
