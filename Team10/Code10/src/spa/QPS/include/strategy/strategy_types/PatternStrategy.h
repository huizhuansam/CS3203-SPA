#pragma once

#include <utility>

#include "strategy/PriorityScore.h"
#include "strategy/Strategy.h"
#include "strategy/argument_types/EntRefType.h"
#include "strategy/argument_types/EntRefTypeController.h"
#include "strategy/argument_types/ExprSpecType.h"
#include "strategy/strategy_types/StrategyType.h"

namespace QPS {
using ReadFacadeReturnPairMethod =
    std::function<std::unordered_set<std::pair<std::string, std::string>,
                                     PairHash>(ReadFacade)>;

class PatternStrategy : public Strategy {
 private:
  static const std::unordered_map<StrategyType, ReadFacadeReturnPairMethod>
      strategyToReadFacadeMethodMap;

  StrategyType strategyType;
  std::string synonym;
  std::string arg1;
  EntRefType argType1;
  std::vector<std::string> arg2;
  ExprSpecType argType2;

  // strategy type flags
  bool isAssignPattern = false;
  bool isWhilePattern = false;
  bool isIfPattern = false;

  // arg flags
  bool isArg1Synonym = false;
  bool isArg1Variable = false;
  bool isArg1Ident = false;
  bool isArg1Wildcard = false;
  bool isExpr = false;
  bool isPartialExpr = false;

  void setArgFlags();

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getStmtVarPairSet(ReadFacade& readFacade) const;

  [[nodiscard]] std::unordered_map<std::string, int> generateHeaders() const;

  std::vector<std::string> generateDataRow(std::string& stmtNo,
                                           std::string& var) const;

 public:
  /// Strategy constructor for a pattern clause,
  /// i.e. pattern syn (var, _ [,-]*).
  /// @param synonym Assignment synonym in pattern clause.
  /// @param arg1 First argument in clause.
  /// @param argType1 EntRefType of arg1.
  /// @param arg2 Second argument in clause.
  /// @param argType2 ExprSpecType of arg2.
  PatternStrategy(StrategyType strategyType, std::string synonym,
                  std::string arg1, EntRefType argType1,
                  std::vector<std::string> arg2, ExprSpecType argType2);

  std::string getSynonym();
  std::string getArg1();
  std::vector<std::string> getArg2();
  EntRefType getArgType1();
  ExprSpecType getArgType2();
  std::unordered_set<std::string> getSynonyms() override;

  /// Returns the result table of the relation clause.
  /// @param readFacade ReadFacade object to retrieve the PKB data.
  Result evaluateValues(ReadFacade& readFacade) override;

  void replaceSynFromWithClause(
      std::unordered_map<std::string, std::pair<std::string, bool>>&
          replaceableSynValues,
      std::unordered_map<std::string, SynonymType>& replaceableStmtSyn)
      override;
};
}  // namespace QPS
