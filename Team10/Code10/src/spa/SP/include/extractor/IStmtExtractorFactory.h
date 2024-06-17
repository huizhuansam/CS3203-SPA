#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "DesignExtractor.h"
#include "IExtractor.h"
#include "IStmtExtractor.h"
#include "WriteFacade.h"
#include "tokenizer/Token.h"

namespace SP {
class IStmtExtractorFactory {
 private:
  static const std::unordered_map<
      TokenType, std::function<std::unique_ptr<IStmtExtractor>(WriteFacade&)>>
      tokenTypeToExtractorMap;

  static const std::unordered_map<TokenType, StatementType>
      tokenTypeToStatementTypeMap;

 public:
  static std::unique_ptr<IStmtExtractor> of(
      std::vector<std::unique_ptr<Token>>::iterator& it, WriteFacade& writer);
};
}  // namespace SP
