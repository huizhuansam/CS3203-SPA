#include "WithOptimizer.h"

#include "WithStrategy.h"

namespace QPS {
void WithOptimizer::optimizeWith(
    std::vector<std::shared_ptr<Strategy>>& strategies) {
  // use map for O(1) access
  // 1. get all the value a synonym type can be replaced with from "with" clause
  // 2. get all stmt type that can be replaced with a stricter stmt type
  std::unordered_map<std::string, std::pair<std::string, bool>>
      replaceableSynValues = getReplaceableSynValues(strategies);
  std::unordered_map<std::string, SynonymType> replaceableStmtSyn =
      getReplaceableStmtSyn(strategies);

  // nothing to replace, do nothing
  if (replaceableSynValues.empty() && replaceableStmtSyn.empty()) {
    return;
  }

  // for each strategy, if the strategy contains the synonym,
  // then replace the argument with setter
  for (const auto& strategy : strategies) {
    strategy->replaceSynFromWithClause(replaceableSynValues,
                                       replaceableStmtSyn);
  }
}

std::unordered_map<std::string, std::pair<std::string, bool>>
WithOptimizer::getReplaceableSynValues(
    std::vector<std::shared_ptr<Strategy>>& strategies) {
  std::unordered_map<std::string, std::pair<std::string, bool>>
      replaceableSynValues;
  for (const auto& strategy : strategies) {
    bool isWithStrategy = strategy->isWithStrategy();
    if (isWithStrategy && !strategy->isNotStrategy()) {
      // convert to WithStrategy
      std::shared_ptr<WithStrategy> withStrategy =
          std::dynamic_pointer_cast<WithStrategy>(strategy);

      // get the replaceable values
      std::tuple<std::string, std::string, bool> synValuePair =
          withStrategy->getReplaceableSynValues();
      bool canReplaceSynValue = !std::get<0>(synValuePair).empty() &&
                                !std::get<1>(synValuePair).empty();
      if (canReplaceSynValue) {
        std::string synToReplace = std::get<0>(synValuePair);
        std::string valueToReplace = std::get<1>(synValuePair);
        bool isSynValueBool = std::get<2>(synValuePair);
        replaceableSynValues[synToReplace] =
            std::make_pair(valueToReplace, isSynValueBool);
      }
    }
  }
  return replaceableSynValues;
}

std::unordered_map<std::string, SynonymType>
WithOptimizer::getReplaceableStmtSyn(
    std::vector<std::shared_ptr<Strategy>>& strategies) {
  std::unordered_map<std::string, SynonymType> replaceableStmtSyn;
  for (const auto& strategy : strategies) {
    bool isWithStrategy = strategy->isWithStrategy();
    if (isWithStrategy && !strategy->isNotStrategy()) {
      // convert to WithStrategy
      std::shared_ptr<WithStrategy> withStrategy =
          std::dynamic_pointer_cast<WithStrategy>(strategy);

      // get the replaceable stmt synonyms
      std::pair<std::string, SynonymType> stmtSynPair =
          withStrategy->getReplaceableStmtSyn();
      bool canReplaceStmtSyn = !stmtSynPair.first.empty() &&
                               stmtSynPair.second != SynonymType::INVALID;
      if (canReplaceStmtSyn) {
        replaceableStmtSyn[stmtSynPair.first] = stmtSynPair.second;
      }
    }
  }
  return replaceableStmtSyn;
}
}  // namespace QPS