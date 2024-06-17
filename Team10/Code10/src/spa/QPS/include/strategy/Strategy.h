#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../result/Result.h"
#include "ReadFacade.h"
#include "cache/Cache.h"
#include "strategy/argument_types/AttrNameType.h"
#include "strategy/argument_types/StmtRefType.h"
#include "strategy/argument_types/SynonymType.h"

namespace QPS {
using EvaluateFunctionType =
    std::function<std::vector<std::vector<std::string>>(ReadFacade&)>;

class Strategy {
 private:
  bool isNot = false;
  int priorityScore = 0;

 protected:
  static std::vector<std::string> getAllHeaderNames(const std::string& synonym,
                                                    SynonymType synonymType);

  // Attributes for the data of the different synonym types with attrName
  // e.g. for procedure, it will be 2 column data for "procedure" and
  // "procedure.procName" e.g. for read, it will be 3 column data for "read",
  // "read.stmt#", "read.varName"
  static const EvaluateFunctionType evaluateProcedure;
  static const EvaluateFunctionType evaluateCall;
  static const EvaluateFunctionType evaluateVariable;
  static const EvaluateFunctionType evaluateRead;
  static const EvaluateFunctionType evaluatePrint;
  static const EvaluateFunctionType evaluateConstant;
  static const EvaluateFunctionType evaluateStmt;
  static const EvaluateFunctionType evaluateAssign;
  static const EvaluateFunctionType evaluateWhile;
  static const EvaluateFunctionType evaluateIf;
  static const std::unordered_map<SynonymType, EvaluateFunctionType>
      synonymAttrNameEvaluationMap;

  static std::unordered_set<int> getAllStmtBySynonymType(
      StmtRefType type, ReadFacade& readFacade);

  void setPriorityScore(int score);

  std::shared_ptr<Cache> cache = nullptr;

 public:
  /// Evaluates strategy and fetches information from relevant endpoints in PKB.
  /// @return Result object containing evaluation result.
  virtual Result evaluateValues(ReadFacade& readFacade);
  /// Evaluates strategy and fetches information from relevant endpoints in PKB.
  /// @return Whether boolean result is true or false.
  virtual bool evaluateBoolean(ReadFacade& readFacade);

  virtual bool isSelectStrategy();
  virtual bool isSelectTupleStrategy();
  virtual bool isSelectBooleanStrategy();
  virtual bool isBooleanStrategy();
  virtual bool isWithStrategy();
  [[nodiscard]] bool isNotStrategy() const;

  virtual int getSynonymCount();
  virtual std::unordered_set<std::string> getSynonyms();
  [[nodiscard]] int getPriorityScore() const;

  void setIsNotStrategy();

  void injectCache(const std::shared_ptr<Cache>& cacheObject);

  virtual void replaceSynFromWithClause(
      std::unordered_map<std::string, std::pair<std::string, bool>>&
          replaceableSynValues,
      std::unordered_map<std::string, SynonymType>& replaceableStmtSyn);

  virtual ~Strategy() = default;
};
}  // namespace QPS
