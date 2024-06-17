#pragma once
#include <PKBUtil.h>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class AssignExpPatternStore {
 private:
  std::unordered_map<std::pair<std::string, std::string>,
                     std::vector<std::string>, PairHash>
      assignExps;
  bool isExactMatch(const std::vector<std::string>& arr1,
                    const std::vector<std::string>& arr2);

 public:
  void addExp(int stmtNo, const std::string& var,
              const std::vector<std::string>& infixTokens);

  void clear();

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllExpPairs();

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getExpPairsPartialMatch(const std::string& var,
                          const std::vector<std::string>& infixTokens);

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getExpPairsSynonymPartialMatch(const std::vector<std::string>& infixTokens);

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getExpPairsExactMatch(const std::string& var,
                        const std::vector<std::string>& infixTokens);

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getExpPairsSynonymExactMatch(const std::vector<std::string>& infixTokens);

  bool isSubVector(const std::vector<std::string>& largerVector,
                   const std::vector<std::string>& smallerVector);
  std::vector<std::string> infixToPostfix(
      const std::vector<std::string>& infixTokens);
  bool isAlphanumeric(const std::string& str);
  bool isArithmeticOperator(const std::string& str);
  int precedence(const std::string& str);
};
