#include "strategy/Strategy.h"

namespace QPS {
const EvaluateFunctionType Strategy::evaluateProcedure =
    [](ReadFacade& readFacade) -> std::vector<std::vector<std::string>> {
  std::vector<std::vector<std::string>> data;
  std::unordered_set<std::string> allProcedure = readFacade.getAllProcedures();

  // header: procedure
  data.reserve(allProcedure.size());
  for (const std::string& procName : allProcedure) {
    data.push_back({procName});
  }

  return data;
};

const EvaluateFunctionType Strategy::evaluateCall =
    [](ReadFacade& readFacade) -> std::vector<std::vector<std::string>> {
  std::vector<std::vector<std::string>> data;
  std::unordered_set<int> allCallStmt = readFacade.getCalls();

  // header: call, call.procName
  for (const int callStmt : allCallStmt) {
    std::string procName = readFacade.getProcCalledByStmt(callStmt);
    std::string callStmtStr = std::to_string(callStmt);
    data.push_back({callStmtStr, procName});
  }

  return data;
};

const EvaluateFunctionType Strategy::evaluateVariable =
    [](ReadFacade& readFacade) -> std::vector<std::vector<std::string>> {
  std::vector<std::vector<std::string>> data;
  std::unordered_set<std::string> allVarNames = readFacade.getAllVariables();

  // header: variable
  data.reserve(allVarNames.size());
  for (const std::string& varName : allVarNames) {
    data.push_back({varName});
  }

  return data;
};

const EvaluateFunctionType Strategy::evaluateRead =
    [](ReadFacade& readFacade) -> std::vector<std::vector<std::string>> {
  std::vector<std::vector<std::string>> data;
  std::unordered_set<int> allReadStmt = readFacade.getReads();

  // header: read, read.varName
  for (const int readStmt : allReadStmt) {
    std::string varName = readFacade.getVarReadByStmt(readStmt);
    std::string readStmtStr = std::to_string(readStmt);
    data.push_back({readStmtStr, varName});
  }

  return data;
};

const EvaluateFunctionType Strategy::evaluatePrint =
    [](ReadFacade& readFacade) -> std::vector<std::vector<std::string>> {
  std::vector<std::vector<std::string>> data;
  std::unordered_set<int> allPrintStmt = readFacade.getPrints();

  // header: print, print.varName
  for (const int printStmt : allPrintStmt) {
    std::string varName = readFacade.getVarPrintedByStmt(printStmt);
    std::string printStmtStr = std::to_string(printStmt);
    data.push_back({printStmtStr, varName});
  }

  return data;
};

const EvaluateFunctionType Strategy::evaluateConstant =
    [](ReadFacade& readFacade) -> std::vector<std::vector<std::string>> {
  std::vector<std::vector<std::string>> data;
  std::unordered_set<std::string> allConstantValues =
      readFacade.getAllConstants();

  // header: constant
  data.reserve(allConstantValues.size());
  for (const std::string& constantValue : allConstantValues) {
    data.push_back({constantValue});
  }

  return data;
};

const EvaluateFunctionType Strategy::evaluateStmt =
    [](ReadFacade& readFacade) -> std::vector<std::vector<std::string>> {
  std::vector<std::vector<std::string>> data;
  std::unordered_set<int> allStmtNo = readFacade.getStatements();

  // header: stmt
  for (const int stmtNo : allStmtNo) {
    std::string stmtNoStr = std::to_string(stmtNo);
    data.push_back({stmtNoStr});
  }

  return data;
};

const EvaluateFunctionType Strategy::evaluateAssign =
    [](ReadFacade& readFacade) -> std::vector<std::vector<std::string>> {
  std::vector<std::vector<std::string>> data;
  std::unordered_set<int> allAssignStmtNo = readFacade.getAssigns();

  // header: assign
  for (const int assignStmtNo : allAssignStmtNo) {
    std::string assignStmtNoStr = std::to_string(assignStmtNo);
    data.push_back({assignStmtNoStr});
  }

  return data;
};

const EvaluateFunctionType Strategy::evaluateWhile =
    [](ReadFacade& readFacade) -> std::vector<std::vector<std::string>> {
  std::vector<std::vector<std::string>> data;
  std::unordered_set<int> allWhileStmtNo = readFacade.getWhiles();

  // header: while
  for (const int whileStmtNo : allWhileStmtNo) {
    std::string whileStmtNoStr = std::to_string(whileStmtNo);
    data.push_back({whileStmtNoStr});
  }

  return data;
};

const EvaluateFunctionType Strategy::evaluateIf =
    [](ReadFacade& readFacade) -> std::vector<std::vector<std::string>> {
  std::vector<std::vector<std::string>> data;
  std::unordered_set<int> allIfStmtNo = readFacade.getIfs();

  // header: if
  for (const int ifStmtNo : allIfStmtNo) {
    std::string ifStmtNoStr = std::to_string(ifStmtNo);
    data.push_back({ifStmtNoStr});
  }

  return data;
};

const std::unordered_map<SynonymType, EvaluateFunctionType>
    Strategy::synonymAttrNameEvaluationMap = {
        {SynonymType::PROCEDURE, evaluateProcedure},
        {SynonymType::CALL, evaluateCall},
        {SynonymType::VARIABLE, evaluateVariable},
        {SynonymType::READ, evaluateRead},
        {SynonymType::PRINT, evaluatePrint},
        {SynonymType::CONSTANT, evaluateConstant},
        {SynonymType::STMT, evaluateStmt},
        {SynonymType::ASSIGN, evaluateAssign},
        {SynonymType::WHILE, evaluateWhile},
        {SynonymType::IF, evaluateIf},
};

Result Strategy::evaluateValues([[maybe_unused]] ReadFacade& readFacade) {
  return {};
}

bool Strategy::evaluateBoolean([[maybe_unused]] ReadFacade& readFacade) {
  return true;
}

bool Strategy::isSelectStrategy() {
  return isSelectTupleStrategy() || isSelectBooleanStrategy();
}

bool Strategy::isSelectTupleStrategy() { return false; }

bool Strategy::isSelectBooleanStrategy() { return false; }

bool Strategy::isBooleanStrategy() { return false; }

bool Strategy::isWithStrategy() { return false; }

[[maybe_unused]] void Strategy::setIsNotStrategy() { isNot = true; }

bool Strategy::isNotStrategy() const { return isNot; }

std::unordered_set<int> Strategy::getAllStmtBySynonymType(
    StmtRefType type, ReadFacade& readFacade) {
  std::unordered_map<StmtRefType, std::function<std::unordered_set<int>()>>
      stmtRefMap = {
          {StmtRefType::ASSIGN,
           [&readFacade]() { return readFacade.getAssigns(); }},
          {StmtRefType::CALL,
           [&readFacade]() { return readFacade.getCalls(); }},
          {StmtRefType::PRINT,
           [&readFacade]() { return readFacade.getPrints(); }},
          {StmtRefType::READ,
           [&readFacade]() { return readFacade.getReads(); }},
          {StmtRefType::WHILE,
           [&readFacade]() { return readFacade.getWhiles(); }},
          {StmtRefType::IF, [&readFacade]() { return readFacade.getIfs(); }},
          {StmtRefType::STMT,
           [&readFacade]() { return readFacade.getStatements(); }},
          {StmtRefType::WILDCARD,
           [&readFacade]() { return readFacade.getStatements(); }},
      };

  return stmtRefMap[type]();
}

std::vector<std::string> Strategy::getAllHeaderNames(const std::string& synonym,
                                                     SynonymType synonymType) {
  std::vector<std::string> headers;
  headers.push_back(synonym);
  if (synonymType == SynonymType::CALL) {
    headers.push_back(synonym + ".procName");
  }
  if (synonymType == SynonymType::READ || synonymType == SynonymType::PRINT) {
    headers.push_back(synonym + ".varName");
  }

  return headers;
}

int Strategy::getSynonymCount() {
  return static_cast<int>(getSynonyms().size());
}

std::unordered_set<std::string> Strategy::getSynonyms() { return {}; }

void Strategy::setPriorityScore(int score) { priorityScore = score; }

int Strategy::getPriorityScore() const { return priorityScore; }

void Strategy::injectCache(const std::shared_ptr<Cache>& cacheObject) {
  this->cache = cacheObject;
}

void Strategy::replaceSynFromWithClause(
    [[maybe_unused]] std::unordered_map<
        std::string, std::pair<std::string, bool>>& replaceableSynValues,
    [[maybe_unused]] std::unordered_map<std::string, SynonymType>&
        replaceableStmtSyn) {
  // Do nothing
}
}  // namespace QPS
