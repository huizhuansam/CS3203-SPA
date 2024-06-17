#pragma once

#include <vector>

#include "IExtractor.h"
#include "WriteFacade.h"
#include "tokenizer/Token.h"

namespace SP {
/// @brief Extractor for conditional expressions
class CondExprExtractor : public IExtractor {
 private:
  WriteFacade& writer;
  std::unordered_set<std::string> varUsed;

 public:
  /// @brief Construct a new Cond Expr Extractor object
  /// @param writer A write facade providing write access to the PKB
  CondExprExtractor(WriteFacade& writer);

  /// @brief Get the variables used in the conditional expression
  /// @return A set of variable names used in the conditional expression
  std::unordered_set<std::string> getVarUsed();

  /// @brief Extract conditional expressions from a token vector
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  void extract(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end) override;

 private:
  bool isOpenBracketOfCondExpr(
      const std::vector<std::unique_ptr<Token>>::iterator& it);
};
}  // namespace SP
