#pragma once

#include <functional>
#include <vector>

#include "IExtractor.h"
#include "StmtLstExtractor.h"
#include "WriteFacade.h"
#include "tokenizer/Token.h"

namespace SP {
/// @brief Extractor for statements
class IStmtExtractor : public IExtractor {
 public:
  /// @brief Get the last statement numbers executed
  virtual std::unordered_set<int> getLastExecutedStmtNumbers();

  virtual void dumpContentsInto(StmtLstExtractor& stmtListExtractor,
                                int currentStmtNo) = 0;

  virtual ~IStmtExtractor() = default;
};
}  // namespace SP
