#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../../exception/NonGrammarRule.h"
#include "../../exception/SemanticError.h"
#include "../../tokenizer/Token.h"
#include "../../validator/IValidator.h"

namespace QPS {
class SemanticValidator : public IValidator {
 private:
  static const std::unordered_map<std::string, std::unordered_set<std::string>>
      validAttrNames;

 public:
  SemanticValidator() = default;

  void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) override;

 private:
  static void validateDeclaration(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      std::unordered_map<std::string, std::string>& synonymTypeMap);

  static void validateSelect(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end,
      std::unordered_map<std::string, std::string>& synonymTypeMap);

  static void validateSingleSelect(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end,
      std::unordered_map<std::string, std::string>& synonymTypeMap);

  static void validateTupleSelect(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end,
      std::unordered_map<std::string, std::string>& synonymTypeMap);

  static void validateBooleanSelect(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end);

  static void validateClause(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end,
      std::unordered_map<std::string, std::string>& synonymTypeMap);

  static void validateSuchThat(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      std::unordered_map<std::string, std::string>& synonymTypeMap);

  static void validatePattern(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      std::unordered_map<std::string, std::string>& synonymTypeMap);

  static void consumeRemainingPatternFromSecondArg(
      std::string& synType, std::vector<std::shared_ptr<Token>>::iterator& it);

  static void consumeIfPatternFromSecondArg(
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static void consumeWhilePatternFromSecondArg(
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static void consumeAssignPatternFromSecondArg(
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static void validateWith(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      std::unordered_map<std::string, std::string>& synonymTypeMap);

  static bool isQuotedEntity(std::vector<std::shared_ptr<Token>>::iterator& it);

  static bool isSynonym(std::vector<std::shared_ptr<Token>>::iterator& it);

  static void throwErrorIfDuplicate(
      std::unordered_map<std::string, std::string>& synonymTypeMap,
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static void throwErrorIfNotDeclared(
      std::unordered_map<std::string, std::string>& synonymTypeMap,
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static void throwErrorIfWildcard(
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static void throwErrorIfNotProcedure(
      std::unordered_map<std::string, std::string>& synonymTypeMap,
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static void throwErrorIfNotStmt(
      std::unordered_map<std::string, std::string>& synonymTypeMap,
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static void throwErrorIfNotProcedureOrStmt(
      std::unordered_map<std::string, std::string>& synonymTypeMap,
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static void throwErrorIfNotVariable(
      std::unordered_map<std::string, std::string>& synonymTypeMap,
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static void throwErrorIfPatternArg1NotVariable(
      std::unordered_map<std::string, std::string>& synonymTypeMap,
      std::vector<std::shared_ptr<Token>>::iterator& it);

  static void throwErrorIfAttrNameInvalid(
      std::unordered_map<std::string, std::string>& synonymTypeMap,
      const std::string& synonym, const std::string& attrName);

  static std::string getSynonymType(
      std::unordered_map<std::string, std::string>& synonymTypeMap,
      std::vector<std::shared_ptr<Token>>::iterator& it);
};
}  // namespace QPS
