#pragma once

#include <string>
#include <utility>

#include "strategy/PriorityScore.h"
#include "strategy/Strategy.h"
#include "strategy/argument_types/EntRefType.h"
#include "strategy/argument_types/EntRefTypeController.h"
#include "strategy/strategy_types/StrategyType.h"

namespace QPS {
using ReadFacadeStrMethod =
    std::function<std::unordered_set<std::string>(std::string, ReadFacade)>;

class EntEntArgStrategy : public Strategy {
 private:
  static const std::unordered_map<StrategyType, ReadFacadeStrMethod>
      strategyToReadFacadeMethodMap;

  StrategyType strategyType;
  std::string arg1;
  EntRefType argType1;
  std::string arg2;
  EntRefType argType2;

  // arg flags
  bool isArg1Synonym = false;
  bool isArg1Ident = false;

  bool isArg2Synonym = false;
  bool isArg2Ident = false;
  bool isArg2Wildcard = false;

  bool isBothArgSame = false;

  // arg sets to be evaluated
  std::unordered_set<std::string> argSet1;
  std::unordered_set<std::string> argSet2;
  std::unordered_map<std::string, std::unordered_set<std::string>> relationMap;

  void setArgFlags();

  void setEvaluationSets(ReadFacade &readFacade);

  [[nodiscard]] std::unordered_map<std::string, int> generateHeaders() const;
  std::vector<std::string> generateDataRow(const std::string &arg1Value,
                                           std::string &arg2Value) const;

 public:
  /// Strategy constructor for a clause with (EntRef, EntRef) arguments.
  /// @param arg1 First argument in clause.
  /// @param arg2 Second argument in clause.
  EntEntArgStrategy(StrategyType strategyType, std::string arg1,
                    EntRefType argType1, std::string arg2, EntRefType argType2);

  std::string getArg1();
  EntRefType getArgType1();
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
