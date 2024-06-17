#include "result/Result.h"

#include "../parser/Parser.h"

namespace QPS {
Result::Result() = default;

Result::Result(const std::unordered_map<std::string, int>& headers,
               const std::vector<std::vector<std::string>>& data)
    : headers(headers), data(data) {}

std::unordered_map<std::string, int>& Result::getHeaders() {
  return this->headers;
}

std::vector<std::string> Result::getSortedHeaderNames() {
  std::vector<std::string> sortedHeaders;
  sortedHeaders.resize(this->headers.size());
  for (const auto& header : this->headers) {
    auto index = static_cast<size_t>(header.second);
    sortedHeaders[index] = header.first;
  }
  return sortedHeaders;
}

std::vector<std::string> Result::getHeaderNamesWithoutAttrNames() {
  std::vector<std::string> headerNames;
  for (const auto& header : headers) {
    std::string headerStr = header.first;
    if (headerStr.find('.') == std::string::npos) {
      headerNames.push_back(headerStr);
    } else {
      headerNames.push_back(headerStr.substr(0, headerStr.find('.')));
    }
  }
  std::sort(headerNames.begin(), headerNames.end());
  auto extraStart = std::unique(headerNames.begin(), headerNames.end());
  headerNames.erase(extraStart, headerNames.end());
  return headerNames;
}

std::vector<SynonymType> Result::getHeaderSynonymTypes(
    const std::vector<std::string>& headerNames) {
  std::vector<SynonymType> headerTypes;
  for (const auto& header : headerNames) {
    if (header.find('.') != std::string::npos) {
      headerTypes.push_back(
          Parser::getDeclarationType(header.substr(0, header.find('.'))));
    } else {
      headerTypes.push_back(Parser::getDeclarationType(header));
    }
  }
  return headerTypes;
}

int Result::getHeaderIndex(const std::string& header) {
  return this->headers.at(header);
}

void Result::addHeader(const std::string& headerName, int index) {
  this->headers.insert({headerName, index});
}

bool Result::isDataEmpty() {
  return this->data.empty() || this->data.front().empty();
}

std::vector<std::vector<std::string>>& Result::getData() { return this->data; }

void Result::setData(const std::vector<std::vector<std::string>>& newData) {
  this->data = newData;
}

void Result::getDataByHeaderNames(
    std::vector<std::string>& headerNames,
    std::list<std::list<std::string>>& resultData) {
  // Precompute header indices
  std::vector<size_t> headerIndices;
  headerIndices.reserve(headerNames.size());
  for (const auto& headerName : headerNames) {
    // Directly use at() assuming the header will be found
    headerIndices.push_back(static_cast<size_t>(this->headers.at(headerName)));
  }

  // Iterate through each row of data
  for (const auto& row : this->data) {
    std::list<std::string> newRow;
    for (auto index : headerIndices) {
      newRow.push_back(row[index]);  // Directly access the element
    }
    resultData.push_back(
        std::move(newRow));  // Use move semantics to avoid copying
  }
}

void Result::getDataByHeaderNames(
    std::vector<std::string>& headerNames,
    std::vector<std::vector<std::string>>& resultData) {
  for (auto& row : this->data) {
    std::vector<std::string> newRow;
    for (auto& headerName : headerNames) {
      auto index = static_cast<size_t>(this->headers.at(headerName));
      newRow.push_back(row[index]);
    }
    resultData.push_back(newRow);
  }
}

void Result::getTupleByHeaderIndices(std::vector<std::string> row,
                                     std::vector<int>& desiredHeaderIndices,
                                     std::vector<std::string>& tuple) {
  for (auto& desiredHeaderIndex : desiredHeaderIndices) {
    auto index = static_cast<size_t>(desiredHeaderIndex);
    tuple.push_back(row[index]);
  }
}

void Result::getCommonHeaders(Result& r1, Result& r2,
                              std::vector<std::string>& commonHeaders) {
  for (auto& header : r1.headers) {
    if (r2.headers.find(header.first) != r2.headers.end()) {
      commonHeaders.push_back(header.first);
    }
  }
}

void Result::getUncommonHeaders(Result& r1, Result& r2,
                                std::vector<std::string>& uncommonHeaders) {
  for (auto& r2header : r2.headers) {
    std::string r2headerName = r2header.first;
    bool isUncommon = true;
    for (auto& r1header : r1.headers) {
      std::string r1headerName = r1header.first;
      if (r1headerName == r2headerName) {
        isUncommon = false;
        break;
      }
    }

    if (isUncommon) {
      uncommonHeaders.push_back(r2headerName);
    }
  }
}

void Result::flattenData(std::list<std::list<std::string>>& dataToFlatten,
                         std::list<std::string>& flattenedData) {
  for (auto& row : dataToFlatten) {
    for (auto& cell : row) {
      flattenedData.push_back(cell);
    }
  }
}

std::list<std::string> Result::getFlattenListByHeaderNames(
    std::vector<std::string>& headerNames) {
  // Precompute header indices
  std::vector<size_t> headerIndices;
  headerIndices.reserve(headerNames.size());
  for (const auto& headerName : headerNames) {
    // Directly use at() assuming the header will be found
    headerIndices.push_back(static_cast<size_t>(this->headers.at(headerName)));
  }

  std::list<std::string> flattenedData;
  for (auto& row : this->data) {
    std::string rowString;
    bool isFirst = true;
    for (auto index : headerIndices) {
      // add space before if not first element
      if (!isFirst) {
        rowString += " ";
      }
      rowString += row[index];
      isFirst = false;
    }
    flattenedData.push_back(rowString);
  }
  return flattenedData;
}

void Result::appendRow(std::vector<std::string>& row) {
  this->data.push_back(row);
}

void Result::merge(Result& r1, Result& r2, Result& resultTable) {
  std::vector<std::string> commonHeaders;
  getCommonHeaders(r1, r2, commonHeaders);
  if (commonHeaders.empty()) {
    return Result::crossProduct(r1, r2, resultTable);
  } else {
    return Result::innerJoin(r1, r2, commonHeaders, resultTable);
  }
}

void Result::innerJoin(Result& r1, Result& r2,
                       std::vector<std::string>& commonHeaders,
                       Result& resultTable) {
  // get uncommon headers
  std::vector<std::string> extraR2Headers;
  getUncommonHeaders(r1, r2, extraR2Headers);

  // populate resultTable with combined header set
  populateAllHeaders(r1, resultTable, extraR2Headers);

  // find common header indices for r1 and r2
  std::vector<int> commonR1HeaderIndices;
  std::vector<int> commonR2HeaderIndices;
  findCommonHeaderIndices(r1, r2, commonHeaders, commonR1HeaderIndices,
                          commonR2HeaderIndices);

  // find extra r2 header indices
  std::vector<int> extraR2HeaderIndices;
  findExtraHeaderIndices(r2, extraR2Headers, extraR2HeaderIndices);

  // do inner join by hash join
  std::unordered_map<std::string, std::vector<std::vector<std::string>>>
      hashMap;

  // Build hash map for r1: key = tuple of common headers, value = row in r1
  for (auto& row1 : r1.data) {
    std::string key =
        getTupleByHeaderIndicesAsString(row1, commonR1HeaderIndices);
    hashMap[key].push_back(row1);
  }

  std::vector<std::string> newRow(resultTable.headers.size());
  std::vector<std::string> extraTuple2(extraR2Headers.size());

  for (auto& row2 : r2.data) {
    std::string key =
        getTupleByHeaderIndicesAsString(row2, commonR2HeaderIndices);
    if (hashMap.find(key) != hashMap.end()) {
      auto& matchingRowsFromR1 = hashMap[key];
      extraTuple2.clear();
      getTupleByHeaderIndices(row2, extraR2HeaderIndices, extraTuple2);
      for (auto& row1 : matchingRowsFromR1) {
        newRow.clear();
        newRow.insert(newRow.end(), row1.begin(), row1.end());
        newRow.insert(newRow.end(), extraTuple2.begin(), extraTuple2.end());
        resultTable.appendRow(newRow);
      }
    }
  }
}

void Result::innerJoinByHeaders(Result& r1, Result& r2,
                                const std::string& leftHeader,
                                const std::string& rightHeader,
                                Result& resultTable) {
  // result headers = r1 headers + r2 headers
  std::vector<std::string> r2Headers;
  r2Headers.resize(r2.headers.size());
  for (const auto& pair : r2.headers) {
    auto index = static_cast<size_t>(pair.second);
    r2Headers[index] = pair.first;
  }
  populateAllHeaders(r1, resultTable, r2Headers);

  std::vector<int> r1MatchHeaderIndex = {r1.getHeaderIndex(leftHeader)};
  std::vector<int> r2MatchHeaderIndex = {r2.getHeaderIndex(rightHeader)};

  // do inner join by hash join
  std::unordered_map<std::string, std::vector<std::vector<std::string>>>
      hashMap;

  // Build hash map for r1: key = tuple of common headers, value = row in r1
  for (auto& row1 : r1.data) {
    std::string key = getTupleByHeaderIndicesAsString(row1, r1MatchHeaderIndex);
    hashMap[key].push_back(row1);
  }
  std::vector<std::string> newRow(resultTable.headers.size());

  for (auto& row2 : r2.data) {
    std::string key = getTupleByHeaderIndicesAsString(row2, r2MatchHeaderIndex);
    if (hashMap.find(key) != hashMap.end()) {
      auto& matchingRowsFromR1 = hashMap[key];
      for (auto& row1 : matchingRowsFromR1) {
        newRow.clear();
        newRow.insert(newRow.end(), row1.begin(), row1.end());
        newRow.insert(newRow.end(), row2.begin(), row2.end());
        resultTable.appendRow(newRow);
      }
    }
  }
}

void Result::crossProduct(Result& r1, Result& r2, Result& resultTable) {
  // result headers = r1 headers + r2 headers
  std::vector<std::string> r2Headers;
  r2Headers.resize(r2.headers.size());
  for (const auto& pair : r2.headers) {
    auto index = static_cast<size_t>(pair.second);
    r2Headers[index] = pair.first;
  }
  populateAllHeaders(r1, resultTable, r2Headers);

  // Perform cross product on data
  std::vector<std::string> crossRow(resultTable.headers.size());
  for (const auto& row2 : r2.data) {
    for (const auto& row1 : r1.data) {
      crossRow.clear();
      crossRow.insert(crossRow.end(), row1.begin(), row1.end());
      crossRow.insert(crossRow.end(), row2.begin(), row2.end());
      resultTable.appendRow(crossRow);
    }
  }
}

void Result::subtract(Result& r1, Result& r2, Result& resultSubtracted) {
  // header of resultSubtracted = header of r2
  for (auto& header : r2.headers) {
    resultSubtracted.addHeader(header.first, header.second);
  }

  std::vector<int> commonR1HeaderIndices;
  std::vector<int> commonR2HeaderIndices;
  std::vector<std::string> commonHeaders = r2.getSortedHeaderNames();
  findCommonHeaderIndices(r1, r2, commonHeaders, commonR1HeaderIndices,
                          commonR2HeaderIndices);

  // do subtract by hash "subtract"
  std::unordered_set<std::string> hashSet;

  // Build hash map for r1: key = tuple of common headers, value = row in r2
  for (auto& row2 : r2.data) {
    hashSet.insert(
        getTupleByHeaderIndicesAsString(row2, commonR2HeaderIndices));
  }

  std::vector<std::string> newRow(resultSubtracted.headers.size());
  std::vector<std::string> tupleRemained;
  for (auto& row1 : r1.data) {
    std::string key =
        getTupleByHeaderIndicesAsString(row1, commonR1HeaderIndices);
    if (hashSet.find(key) == hashSet.end()) {
      // adds the row where common data are not in r2
      tupleRemained.clear();
      getTupleByHeaderIndices(row1, commonR1HeaderIndices, tupleRemained);

      newRow.clear();
      newRow.insert(newRow.end(), tupleRemained.begin(), tupleRemained.end());

      resultSubtracted.appendRow(newRow);
    }
  }
}

void Result::populateAllHeaders(const Result& r1, Result& resultTable,
                                const std::vector<std::string>& addedHeaders) {
  for (auto& r1Header : r1.headers) {
    resultTable.addHeader(r1Header.first, r1Header.second);
  }
  for (auto& addedHeader : addedHeaders) {
    int index = static_cast<int>(resultTable.headers.size());
    resultTable.addHeader(addedHeader, index);
  }
}

void Result::findCommonHeaderIndices(Result r1, Result& r2,
                                     std::vector<std::string>& commonHeaders,
                                     std::vector<int>& commonR1HeaderIndices,
                                     std::vector<int>& commonR2HeaderIndices) {
  for (auto& commonHeader : commonHeaders) {
    commonR1HeaderIndices.push_back(r1.getHeaderIndex(commonHeader));
    commonR2HeaderIndices.push_back(r2.getHeaderIndex(commonHeader));
  }
}

void Result::findExtraHeaderIndices(
    Result& r2, const std::vector<std::string>& extraR2Headers,
    std::vector<int>& extraR2HeaderIndices) {
  extraR2HeaderIndices.reserve(extraR2Headers.size());
  for (auto& extraR2Header : extraR2Headers) {
    extraR2HeaderIndices.push_back(r2.getHeaderIndex(extraR2Header));
  }
}

std::string Result::getTupleByHeaderIndicesAsString(
    std::vector<std::string> row, std::vector<int>& desiredHeaderIndices) {
  std::string tuple;
  for (auto& desiredHeaderIndex : desiredHeaderIndices) {
    auto index = static_cast<size_t>(desiredHeaderIndex);
    tuple += row[index];
    tuple += " ";
  }
  return tuple;
}

bool Result::operator==(const Result& other) const {
  return this->headers == other.headers && this->data == other.data;
}
}  // namespace QPS
