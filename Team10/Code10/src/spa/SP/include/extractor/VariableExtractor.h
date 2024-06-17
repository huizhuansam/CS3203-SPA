#pragma once

#include <memory>
#include <vector>

#include "IExtractor.h"
#include "WriteFacade.h"
#include "tokenizer/Token.h"

namespace SP {
/// @brief Extractor for variables
class VariableExtractor : public IExtractor {
 private:
  WriteFacade& writer;

 public:
  /// @brief Construct a new Variable Extractor object
  /// @param writer A write facade providing write access to the PKB
  VariableExtractor(WriteFacade& writer);

  /// @brief Extract variables from a token vector
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  void extract(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end) override;
};
}  // namespace SP
