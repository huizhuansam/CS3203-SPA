#include "result/Result.h"

#include <memory>

#include "catch.hpp"

using namespace QPS;

// same examples in Week 6 lecture videos
const std::unique_ptr<Result> Uses1 = std::make_unique<Result>(
    std::unordered_map<std::string, int>{{"s3", 0}, {"v1", 1}},
    std::vector<std::vector<std::string>>{
        {"5", "y"}, {"5", "z"}, {"7", "x"}, {"8", "y"}, {"2", "y"}});

const std::unique_ptr<Result> Modifies1 = std::make_unique<Result>(
    std::unordered_map<std::string, int>{{"s3", 0}},
    std::vector<std::vector<std::string>>{{"6"}, {"5"}, {"7"}});

const std::unique_ptr<Result> Follows1 = std::make_unique<Result>(
    std::unordered_map<std::string, int>{{"s1", 0}, {"s2", 1}},
    std::vector<std::vector<std::string>>{
        {"6", "20"}, {"3", "4"}, {"10", "15"}, {"8", "11"}});

const std::unique_ptr<Result> Parent1 = std::make_unique<Result>(
    std::unordered_map<std::string, int>{{"s3", 0}, {"s1", 1}},
    std::vector<std::vector<std::string>>{
        {"5", "6"}, {"5", "8"}, {"2", "7"}, {"2", "3"}, {"7", "6"}});

const std::unique_ptr<Result> Uses2 = std::make_unique<Result>(
    std::unordered_map<std::string, int>{{"s2", 0}, {"v1", 1}},
    std::vector<std::vector<std::string>>{{"11", "y"},
                                          {"20", "x"},
                                          {"4", "x"},
                                          {"20", "y"},
                                          {"11", "z"},
                                          {"10", "z"}});

TEST_CASE("getDataByHeaderNames", "[Result]") {
  std::vector<std::string> headerNames = {"s3"};
  std::list<std::list<std::string>> expectedData = {
      {"5"}, {"5"}, {"7"}, {"8"}, {"2"}};
  std::list<std::list<std::string>> actualData;
  Uses1->getDataByHeaderNames(headerNames, actualData);
  REQUIRE(actualData == expectedData);
}

TEST_CASE("getTupleByHeaderIndices", "[Result]") {
  std::vector<int> headerIndices = {0};
  std::vector<std::string> expectedTuple = {"5"};
  std::vector<std::string> actualTuple;
  std::vector<std::string> secondRow = Modifies1->getData()[1];
  Modifies1->getTupleByHeaderIndices(secondRow, headerIndices, actualTuple);
  REQUIRE(actualTuple == expectedTuple);
}

TEST_CASE("getCommonHeaders", "[Result]") {
  std::vector<std::string> expectedCommonHeaders = {"s1"};
  std::vector<std::string> actualCommonHeaders;
  Result::getCommonHeaders(*Follows1, *Parent1, actualCommonHeaders);
  REQUIRE(actualCommonHeaders == expectedCommonHeaders);
}

TEST_CASE("getUncommonHeaders", "[Result]") {
  std::vector<std::string> expectedUncommonR2Headers = {"s3"};
  std::vector<std::string> actualUncommonR2Headers;
  Result::getUncommonHeaders(*Follows1, *Parent1, actualUncommonR2Headers);
  REQUIRE(actualUncommonR2Headers == expectedUncommonR2Headers);
}

TEST_CASE("flattenData", "[Result]") {
  std::list<std::string> expectedFlattenedData = {
      "11", "y", "20", "x", "4", "x", "20", "y", "11", "z", "10", "z"};
  std::list<std::string> actualFlattenedData;
  std::list<std::list<std::string>> resultData;
  std::vector<std::string> headers = {"s2", "v1"};
  Uses2->getDataByHeaderNames(headers, resultData);
  Result::flattenData(resultData, actualFlattenedData);
  REQUIRE(actualFlattenedData == expectedFlattenedData);
}

TEST_CASE("innerJoin", "[Result]") {
  std::unordered_map<std::string, int> expectedJoinedHeaders = {{"s3", 0},
                                                                {"v1", 1}};
  std::vector<std::vector<std::string>> expectedJoinedData = {
      {"5", "y"}, {"5", "z"}, {"7", "x"}};

  std::vector<std::string> commonHeaders = {"s3"};
  Result joinedTable = Result();
  Result::innerJoin(*Uses1, *Modifies1, commonHeaders, joinedTable);

  std::unordered_map<std::string, int> actualJoinedHeaders =
      joinedTable.getHeaders();
  std::vector<std::vector<std::string>> actualJoinedData =
      joinedTable.getData();

  REQUIRE(actualJoinedHeaders == expectedJoinedHeaders);
  REQUIRE(actualJoinedData == expectedJoinedData);
}

TEST_CASE("crossProduct", "[Result]") {
  std::unique_ptr<Result> Uses1JoinedModifies1 = std::make_unique<Result>(
      std::unordered_map<std::string, int>{{"s3", 0}, {"v1", 1}},
      std::vector<std::vector<std::string>>{
          {"5", "y"}, {"5", "z"}, {"7", "x"}});

  std::unordered_map<std::string, int> expectedCrossProductHeaders = {
      {"s3", 0}, {"v1", 1}, {"s1", 2}, {"s2", 3}};
  std::vector<std::vector<std::string>> expectedCrossProductData = {
      {"5", "y", "6", "20"},  {"5", "z", "6", "20"},  {"7", "x", "6", "20"},

      {"5", "y", "3", "4"},   {"5", "z", "3", "4"},   {"7", "x", "3", "4"},

      {"5", "y", "10", "15"}, {"5", "z", "10", "15"}, {"7", "x", "10", "15"},

      {"5", "y", "8", "11"},  {"5", "z", "8", "11"},  {"7", "x", "8", "11"},
  };

  Result crossProductTable = Result();
  Result::crossProduct(*Uses1JoinedModifies1, *Follows1, crossProductTable);

  std::unordered_map<std::string, int> actualCrossProductHeaders =
      crossProductTable.getHeaders();
  std::vector<std::vector<std::string>> actualCrossProductData =
      crossProductTable.getData();

  REQUIRE(actualCrossProductHeaders == expectedCrossProductHeaders);
  REQUIRE(actualCrossProductData == expectedCrossProductData);
}

TEST_CASE("merge", "[Result]") {
  std::unordered_map<std::string, int> expectedMergedHeaders = {
      {"s3", 0}, {"v1", 1}, {"s1", 2}, {"s2", 3}};
  std::vector<std::vector<std::string>> expectedMergedData = {
      {{"5", "y", "8", "11"},
       {"7", "x", "6", "20"},
       {"5", "y", "6", "20"},
       {"5", "z", "8", "11"}}};

  Result mergedTable1 = Result();
  Result mergedTable2 = Result();
  Result mergedTable3 = Result();
  Result mergedTable4 = Result();
  Result mergedTable5 = Result();

  Result::merge(*Uses1, *Modifies1, mergedTable1);
  Result::merge(mergedTable1, *Follows1, mergedTable2);
  Result::merge(mergedTable2, *Parent1, mergedTable3);
  Result::merge(mergedTable3, *Parent1, mergedTable4);
  Result::merge(mergedTable4, *Uses2, mergedTable5);

  std::unordered_map<std::string, int> actualMergedHeaders =
      mergedTable5.getHeaders();
  std::vector<std::vector<std::string>> actualMergedData =
      mergedTable5.getData();

  REQUIRE(actualMergedHeaders == expectedMergedHeaders);
  REQUIRE(actualMergedData == expectedMergedData);
}