#include "entity_manager/StatementStore.h"

#include <iostream>
#include <string>

void StatementStore::addStatement(StatementType type, int stmtNo) {
  statements[StatementType::STATEMENT].insert(stmtNo);
  statements[type].insert(stmtNo);
}

std::unordered_set<int> StatementStore::getStatements() {
  return statements[StatementType::STATEMENT];
};
std::unordered_set<int> StatementStore::getAssigns() {
  return statements[StatementType::ASSIGN];
};
std::unordered_set<int> StatementStore::getReads() {
  return statements[StatementType::READ];
};
std::unordered_set<int> StatementStore::getPrints() {
  return statements[StatementType::PRINT];
};
std::unordered_set<int> StatementStore::getCalls() {
  return statements[StatementType::CALL];
};
std::unordered_set<int> StatementStore::getWhiles() {
  return statements[StatementType::WHILE];
};
std::unordered_set<int> StatementStore::getIfs() {
  return statements[StatementType::IF];
};

void StatementStore::clear() { statements.clear(); }
