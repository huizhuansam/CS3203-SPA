#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "StatementType.h"

class StatementStore {
 private:
  std::unordered_map<StatementType, std::unordered_set<int>> statements;

 public:
  void addStatement(StatementType type, int stmtNo);
  std::unordered_set<int> getStatements();
  std::unordered_set<int> getAssigns();
  std::unordered_set<int> getReads();
  std::unordered_set<int> getPrints();
  std::unordered_set<int> getCalls();
  std::unordered_set<int> getWhiles();
  std::unordered_set<int> getIfs();

  void clear();
};
