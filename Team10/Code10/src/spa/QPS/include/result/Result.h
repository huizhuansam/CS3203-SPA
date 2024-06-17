#pragma once

#include <list>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "strategy/argument_types/SynonymType.h"

namespace QPS {
class Result {
 private:
  std::unordered_map<std::string, int> headers;
  std::vector<std::vector<std::string>> data;

 public:
  /// @brief Construct a new Result object
  Result();

  /// @brief Construct a new Result object
  /// @param headers The headers of the result
  /// @param data The data of the result
  Result(const std::unordered_map<std::string, int>& headers,
         const std::vector<std::vector<std::string>>& data);

  /// @brief Returns the headers of the result
  std::unordered_map<std::string, int>& getHeaders();

  /// @brief Returns the headers of the result, sorted by index
  std::vector<std::string> getSortedHeaderNames();

  /// @brief Returns the header names without attribute names
  std::vector<std::string> getHeaderNamesWithoutAttrNames();

  /// @brierf Returns the synonym types of the headers
  static std::vector<SynonymType> getHeaderSynonymTypes(
      const std::vector<std::string>& headerNames);

  /// @brief Returns the column index of the header
  /// @param header The header to get the index of
  int getHeaderIndex(const std::string& header);

  /// @brief Add a header to the result
  /// @param headerName The name of the header
  /// @param index The index of the header
  void addHeader(const std::string& headerName, int index);

  /// @brief Returns true if the result is empty, false otherwise
  bool isDataEmpty();

  /// @brief Returns the data of the result
  std::vector<std::vector<std::string>>& getData();

  /// @brief Set the data of the result
  void setData(const std::vector<std::vector<std::string>>& newData);

  /// @brief Returns the data of the result, filtered by header names
  /// @param headerNames The header names to filter by
  /// @param resultData The filtered data
  void getDataByHeaderNames(std::vector<std::string>& headerNames,
                            std::list<std::list<std::string>>& resultData);

  /// @brief Returns the data of the result, filtered by header names
  /// @param headerNames The header names to filter by
  /// @param resultData The filtered data
  void getDataByHeaderNames(std::vector<std::string>& headerNames,
                            std::vector<std::vector<std::string>>& resultData);

  /// @brief Append a row to the result
  void appendRow(std::vector<std::string>& row);

  /// @brief Get a tuple from a row by header indices
  /// @param row The row to get the tuple from
  /// @param desiredHeaderIndices The indices of the headers to get the tuple
  /// from
  /// @param tuple The tuple to get
  static void getTupleByHeaderIndices(std::vector<std::string> row,
                                      std::vector<int>& desiredHeaderIndices,
                                      std::vector<std::string>& tuple);

  /// @brief Get common header names between two results
  /// @param r1 The first result
  /// @param r2 The second result
  /// @param commonHeaders The common header names
  static void getCommonHeaders(Result& r1, Result& r2,
                               std::vector<std::string>& commonHeaders);

  /// @brief Get uncommon header names between two results
  /// @param r1 The first result
  /// @param r2 The second result
  /// @param uncommonHeaders The uncommon header names
  static void getUncommonHeaders(Result& r1, Result& r2,
                                 std::vector<std::string>& uncommonHeaders);

  /// @brief Flatten a 2D vector of strings to a 1D vector of strings
  /// @param dataToFlatten The 2D vector of strings to flatten
  /// @param flattenedData The 1D vector of strings to store the flattened
  static void flattenData(std::list<std::list<std::string>>& dataToFlatten,
                          std::list<std::string>& flattenedData);

  /// Get flatten list of strings by header names.
  /// @param headerNames Header names to get flatten list of strings by.
  std::list<std::string> getFlattenListByHeaderNames(
      std::vector<std::string>& headerNames);

  /// @brief Merge two results
  /// @param r1 The first result
  /// @param r2 The second result
  /// @param resultMerged The result of the merge
  static void merge(Result& r1, Result& r2, Result& resultMerged);

  /// @brief Inner join two results
  /// @param r1 The first result
  /// @param r2 The second result
  /// @param commonHeaders The common header names
  /// @param resultTable The result of the inner join
  static void innerJoin(Result& r1, Result& r2,
                        std::vector<std::string>& commonHeaders,
                        Result& resultTable);

  /// @brief Inner join two results on selected left and right headers
  /// @param r1 The first result
  /// @param r2 The second result
  /// @param resultTable The result of the inner join
  /// @param leftHeader The header of the left result to match with right header
  /// @param rightHeader The header of the right result to match with left
  /// header
  static void innerJoinByHeaders(Result& r1, Result& r2,
                                 const std::string& leftHeader,
                                 const std::string& rightHeader,
                                 Result& resultTable);

  /// @brief Cross product two results
  /// @param r1 The first result
  /// @param r2 The second result
  /// @param resultTable The result of the cross product
  static void crossProduct(Result& r1, Result& r2, Result& resultTable);

  /// @brief Subtract two results
  /// @param r1 The first result, superset of r2
  /// @param r2 The second result, subset of r1
  /// @param resultSubtracted The result of the subtraction
  static void subtract(Result& r1, Result& r2, Result& resultSubtracted);

  /// Populates resultTable with all headers from r1 and r2.
  /// @param r1 First result to copy headers from.
  /// @param resultTable Result instance to copy headers to.
  /// @param extraR2Headers Headers in r2 but not in r1
  static void populateAllHeaders(const Result& r1, Result& resultTable,
                                 const std::vector<std::string>& addedHeaders);

  /// Finds indices in r1 and r2 of their common headers.
  /// @param r1 First result to get header indices for.
  /// @param r2 Second result to get header indices for.
  /// @param commonHeaders Common headers to find header indices for.
  /// @param commonR1HeaderIndices Vector to write r1 header indices to.
  /// @param commonR2HeaderIndices Vector to write r2 header indices to.
  static void findCommonHeaderIndices(Result r1, Result& r2,
                                      std::vector<std::string>& commonHeaders,
                                      std::vector<int>& commonR1HeaderIndices,
                                      std::vector<int>& commonR2HeaderIndices);

  /// Finds indices of headers in r2 but not in r1.
  /// @param r2 Second result to get uncommon headers with.
  /// @param extraR2Headers Headers in r2 but not in r1.
  /// @param extraR2HeaderIndices Header indices of headers in r2 but not in r1.
  static void findExtraHeaderIndices(
      Result& r2, const std::vector<std::string>& extraR2Headers,
      std::vector<int>& extraR2HeaderIndices);

  /// Get a tuple string from a row by desired header indices.
  /// @param row Row to get tuple from.
  /// @param desiredHeaderIndices Desired header indices to get tuple from.
  static std::string getTupleByHeaderIndicesAsString(
      std::vector<std::string> row, std::vector<int>& desiredHeaderIndices);

  bool operator==(const Result& other) const;
};
}  // namespace QPS
