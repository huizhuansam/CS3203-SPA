#pragma once

#include <sstream>
#include <utility>

#include "result/Result.h"
#include "strategy/PriorityScore.h"
#include "strategy/Strategy.h"
#include "strategy/argument_types/RefType.h"
#include "strategy/argument_types/RefTypeController.h"

namespace QPS {
class WithStrategy : public Strategy {
 private:
  std::string arg1;
  RefType argType1;

  std::string arg2;
  RefType argType2;

 public:
  WithStrategy(std::string arg1, RefType refType1, std::string arg2,
               RefType refType2);

  std::string getArg1();
  std::string getArg2();

  RefType getArgType1();
  RefType getArgType2();

  std::unordered_set<std::string> getSynonyms() override;

  bool isBooleanStrategy() override;
  bool isWithStrategy() override;

  Result evaluateValues(ReadFacade& readFacade) override;
  bool evaluateBoolean([[maybe_unused]] ReadFacade& readFacade) override;

  std::tuple<std::string, std::string, bool> getReplaceableSynValues();

  std::pair<std::string, SynonymType> getReplaceableStmtSyn();

 private:
  Result getResultOfOneSide(bool isLHS, ReadFacade& readFacade);

  static std::string getHeaderWithAttrName(const std::string& synonym,
                                           RefType refType);
};
}  // namespace QPS