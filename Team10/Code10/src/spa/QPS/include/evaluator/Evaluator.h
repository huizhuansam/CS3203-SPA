#pragma once

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "result/Result.h"
#include "strategy/BooleanSelectStrategy.h"
#include "strategy/Strategy.h"
#include "strategy/TupleSelectStrategy.h"

namespace QPS {
class Evaluator {
 private:
  static const std::list<std::string> TRUE_LIST;
  static const std::list<std::string> FALSE_LIST;
  static const std::list<std::string> EMPTY_LIST;

 public:
  /// Evaluate Strategy groups and SelectStrategy into result list.
  /// @param readFacade ReadFacade instance to evaluate strategies with.
  /// @param selectStrategy SelectStrategy instance to select results with.
  /// @param groups Strategy groups to be evaluated.
  static std::list<std::string> getResultList(
      ReadFacade& readFacade, const std::shared_ptr<Strategy>& selectStrategy,
      const std::vector<std::vector<std::shared_ptr<Strategy>>>& groups);

 private:
  /// Evaluates result of boolean select.
  /// @param readFacade ReadFacade instance to evaluate strategies with.
  /// @param groups Strategy groups to be evaluated and merged.
  /// @return Result of boolean select evaluation.
  static std::list<std::string> evaluateBoolean(
      ReadFacade& readFacade,
      const std::vector<std::vector<std::shared_ptr<Strategy>>>& groups);

  /// Evaluates result of value select.
  /// @param readFacade ReadFacade instance to evaluate strategies with.
  /// @param selectStrategy SelectStrategy to be evaluated.
  /// @param groups Strategy groups to be evaluated and merged.
  /// @return Result of value select evaluation.
  static std::list<std::string> evaluateValues(
      ReadFacade& readFacade, const std::shared_ptr<Strategy>& selectStrategy,
      const std::vector<std::vector<std::shared_ptr<Strategy>>>& groups);

  /// Evaluates and merged strategies within each strategy group.
  /// @param readFacade ReadFacade instance to evaluate strategies with.
  /// @param groups Strategy groups to be evaluated and merged.
  /// @return Vector of Result instances from merging individual groups.
  static std::vector<Result> evaluateEachGroup(
      ReadFacade& readFacade,
      const std::vector<std::vector<std::shared_ptr<Strategy>>>& groups);

  /// Evalutes a strategy for values result.
  /// @param readFacade ReadFacade instance to evaluate strategy with.
  /// @param strategy Strategy to be evaluated.
  /// @param isFirst Whether strategy instance is first in strategy group.
  /// @param groupResult Current merged group result.
  /// @return Result of merging strategy instance evaluation into groupResult.
  static Result evaluateValueStrategy(ReadFacade& readFacade,
                                      const std::shared_ptr<Strategy>& strategy,
                                      bool isFirst, Result groupResult);

  /// Evaluates a not strategy.
  /// @param readFacade ReadFacade instance to evaluate not strategy with.
  /// @param strategy Not strategy to be evaluated.
  /// @return Result of evaluating not strategy instance.
  static Result evaluateNotValueStrategy(
      ReadFacade& readFacade, const std::shared_ptr<Strategy>& strategy);

  /// Gets targets of value select strategy as vector of string.
  /// @param selectStrategy Value select strategy instance to get targets from.
  /// @return Targets of value select strategy as vector of string.
  static std::vector<std::string> getSelectTargets(
      const std::shared_ptr<Strategy>& selectStrategy);

  /// Filter group results to only contain columns that are selected.
  /// @param groupResults Group results vector to filter.
  /// @param targetSynonyms Target synonyms of select strategy.
  /// @return Results with header(s) and data in common with select strategy.
  static std::vector<Result> filterGroupResultsByTargetSynonyms(
      std::vector<Result>& groupResults,
      std::vector<std::string>& targetSynonyms);

  /// Filter group result to only contain columns that are selected.
  /// @param groupResult Group result to filter.
  /// @param targetSynonyms Target synonyms of select strategy.
  /// @param filteredGroupResult Result with header(s) and data in common with
  /// select strategy.
  static void filterGroupResultByTargetSynonyms(
      Result& groupResult, std::vector<std::string>& targetSynonyms,
      Result& filteredGroupResult);

  /// Merge results into a single constraint result.
  /// @param filteredGroupResults Filtered group results to be merged.
  /// @return Result of merging filtered group results.
  static Result mergeResults(std::vector<Result>& filteredGroupResults);

  /// Gets synonyms selected by select strategy.
  /// @param selectStrategy Select strategy to get selected synonyms from.
  /// @return Synonyms selected by select strategy.
  static std::vector<std::string> getSelectSynonyms(
      const std::shared_ptr<Strategy>& selectStrategy);

  /// Gets synonym types selected by select strategy.
  /// @param selectStrategy Select strategy to get synonym types from.
  /// @return Synonym types selected by select strategy.
  static std::vector<SynonymType> getSynonymTypes(
      const std::shared_ptr<Strategy>& selectStrategy);

  /// Gets attrName types selected by select strategy.
  /// @param selectStrategy Select strategy to get attrName types from.
  /// @return AttrName types selected by select strategy.
  static std::vector<AttrNameType> getAttrNameTypes(
      const std::shared_ptr<Strategy>& selectStrategy);

  /// Select result by combining constraint result with missing data.
  /// @param selectTargets Targets selected by select strategy.
  /// @param selectSynonyms Synonyms selected by select strategy.
  /// @param selectSynonymTypes Synonym types selected by select strategy.
  /// @param selectAttrNameTypes AttrName types selected by select strategy.
  /// @param constraintResult Results found in constraint clauses.
  /// @param readFacade ReadFacade instance to get missing data with.
  /// @return Result instance containing complete data for select strategy.
  static Result selectResultWithConstraint(
      const std::vector<std::string>& selectTargets,
      const std::vector<std::string>& selectSynonyms,
      const std::vector<SynonymType>& selectSynonymTypes,
      const std::vector<AttrNameType>& selectAttrNameTypes,
      Result& constraintResult, ReadFacade& readFacade);
};
}  // namespace QPS