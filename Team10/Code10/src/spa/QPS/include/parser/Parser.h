#pragma once

#include <memory>
#include <vector>

#include "../parser/DeclarationParser.h"
#include "../parser/EntEntParser.h"
#include "../parser/ParserUtil.h"
#include "../parser/PatternParser.h"
#include "../parser/SelectParser.h"
#include "../parser/StmtEntParser.h"
#include "../parser/StmtStmtParser.h"
#include "../parser/WithParser.h"
#include "../tokenizer/Token.h"
#include "strategy/Strategy.h"
#include "strategy/argument_types/SynonymType.h"

namespace QPS {
class Parser {
 public:
  static std::vector<std::shared_ptr<Strategy>> parse(
      std::vector<std::shared_ptr<Token>>& query);
  static SynonymType getDeclarationType(const std::string& synonym);

 private:
  static std::unordered_map<std::string, SynonymType> declarationTypeMap;
  static std::unordered_map<
      std::string,
      std::function<void(std::vector<std::shared_ptr<Token>>::iterator&,
                         std::vector<std::shared_ptr<Strategy>>&)>>
      parserMap;

  static void parseSelect(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end,
      std::vector<std::shared_ptr<Strategy>>& strategies);

  static void parseClauses(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end,
      std::vector<std::shared_ptr<Strategy>>& strategies);

  static void parseSuchThat(std::vector<std::shared_ptr<Token>>::iterator& it,
                            std::vector<std::shared_ptr<Strategy>>& strategies);

  static void parseModifies(std::vector<std::shared_ptr<Token>>::iterator& it,
                            std::vector<std::shared_ptr<Strategy>>& strategies);

  static void parseUses(std::vector<std::shared_ptr<Token>>::iterator& it,
                        std::vector<std::shared_ptr<Strategy>>& strategies);

  static bool isProcedure(std::vector<std::shared_ptr<Token>>::iterator& it);

  static void parsePattern(std::vector<std::shared_ptr<Token>>::iterator& it,
                           std::vector<std::shared_ptr<Strategy>>& strategies);

  static void parseWith(std::vector<std::shared_ptr<Token>>::iterator& it,
                        std::vector<std::shared_ptr<Strategy>>& strategies);

  static bool isSameClauseType(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end);

  static bool isNot(std::vector<std::shared_ptr<Token>>::iterator& it);
};
}  // namespace QPS
