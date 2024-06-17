#pragma once

#include <string>

#include "strategy/PriorityScore.h"
#include "strategy/Strategy.h"
#include "strategy/argument_types/EntRefType.h"
#include "strategy/argument_types/EntRefTypeController.h"
#include "strategy/argument_types/StmtRefType.h"
#include "strategy/argument_types/StmtRefTypeController.h"
#include "strategy/strategy_types/StrategyType.h"

namespace QPS {

using ReadFacadeIntReturnStrMethod =
    std::function<std::unordered_set<std::string>(int stmtNo, ReadFacade)>;

class StmtEntArgStrategy : public Strategy {
 private:
  static const std::unordered_map<StrategyType, ReadFacadeIntReturnStrMethod>
      strategyToReadFacadeMethodMap;

  StrategyType strategyType;
  std::string arg1;
  StmtRefType argType1;
  std::string arg2;
  EntRefType argType2;

  // arg flags
  bool isArg1Synonym = false;
  bool isArg1Integer = false;

  bool isArg2Synonym = false;
  bool isArg2Ident = false;
  bool isArg2Wildcard = false;

  // arg sets to be evaluated
  std::unordered_set<int> argSet1;
  std::unordered_set<std::string> argSet2;
  std::unordered_map<int, std::unordered_set<std::string>> relationMap;
  void setArgFlags();

  void setEvaluationSets(ReadFacade &readFacade);

  [[nodiscard]] std::unordered_map<std::string, int> generateHeaders() const;

  std::vector<std::string> generateDataRow(int stmtNo, std::string &var) const;

 public:
  /// Strategy constructor for a clause with (StmtRef, EntRef) arguments.
  /// @param arg1 First argument in clause.
  /// @param arg2 Second argument in clause.
  StmtEntArgStrategy(StrategyType strategyType, std::string arg1,
                     StmtRefType argType1, std::string arg2,
                     EntRefType argType2);
  std::string getArg1();
  StmtRefType getArgType1();
  std::string getArg2();
  EntRefType getArgType2();
  std::unordered_set<std::string> getSynonyms() override;

  bool isBooleanStrategy() override;

  /// Returns the result table of the relation clause.
  /// @param readFacade ReadFacade object to retrieve the PKB data.
  Result evaluateValues(ReadFacade &readFacade) override;

  /// Returns the boolean result of the relation clause.
  /// @param readFacade ReadFacade object to retrieve the PKB data.
  bool evaluateBoolean(ReadFacade &readFacade) override;

  void replaceSynFromWithClause(
      std::unordered_map<std::string, std::pair<std::string, bool>>
          &replaceableSynValues,
      std::unordered_map<std::string, SynonymType> &replaceableStmtSyn)
      override;
};
}  // namespace QPS
