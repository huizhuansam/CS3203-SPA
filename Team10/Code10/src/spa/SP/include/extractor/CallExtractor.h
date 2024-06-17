#pragma once

#include <vector>

#include "IStmtExtractor.h"
#include "WriteFacade.h"
#include "tokenizer/Token.h"

namespace SP {
/// @brief Extractor for call statements
class CallExtractor : public IStmtExtractor {
 private:
  WriteFacade& writer;

  std::unordered_set<std::string> procCalled;

 public:
  /// @brief Construct a new Call Extractor object
  /// @param writer A write facade providing write access to the PKB
  CallExtractor(WriteFacade& writer);

  /// @brief Extracts call statements from a token vector
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  void extract(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end) override;

  void dumpContentsInto(StmtLstExtractor& stmtListExtractor,
                        int currentStmtNo) override;
};
}  // namespace SP
