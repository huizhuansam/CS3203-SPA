#include "validator/semantic_validator/SemanticValidator.h"

namespace QPS {
const std::unordered_map<std::string, std::unordered_set<std::string>>
    SemanticValidator::validAttrNames = {
        {"procedure", {"procName"}},
        {"call", {"procName", "stmt#"}},
        {"variable", {"varName"}},
        {"read", {"varName", "stmt#"}},
        {"print", {"varName", "stmt#"}},
        {"constant", {"value"}},
        {"stmt", {"stmt#"}},
        {"assign", {"stmt#"}},
        {"while", {"stmt#"}},
        {"if", {"stmt#"}},
};

void SemanticValidator::validate(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  // initialize synonym-to-type map
  std::unordered_map<std::string, std::string> synonymTypeMap;

  // validate declaration part
  validateDeclaration(it, synonymTypeMap);

  // validate select clause
  validateSelect(it, end, synonymTypeMap);

  // validate remaining clause
  validateClause(it, end, synonymTypeMap);
}

void SemanticValidator::validateDeclaration(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    std::unordered_map<std::string, std::string>& synonymTypeMap) {
  // validate declaration part
  while ((*it)->getValue() != "Select") {
    std::string synonymType = (*it)->getValue();
    it++;  // consume synonym type
    while ((*it)->getType() != TokenType::SEMICOLON) {
      if ((*it)->getType() == TokenType::COMMA) {
        it++;  // consume comma
        continue;
      }

      throwErrorIfDuplicate(synonymTypeMap, it);

      std::string synonym = (*it)->getValue();
      synonymTypeMap.insert({synonym, synonymType});

      it++;  // consume synonym
    }
    it++;  // consume semicolon
  }
}

void SemanticValidator::validateSelect(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end,
    std::unordered_map<std::string, std::string>& synonymTypeMap) {
  it++;  // consume "Select"

  TokenType currentType = (*it)->getType();
  std::string currentValue = (*it)->getValue();

  if (currentType == TokenType::OPEN_ANGLE_BRACKET) {
    validateTupleSelect(it, end, synonymTypeMap);
    return;
  }

  bool isDeclared = synonymTypeMap.find(currentValue) != synonymTypeMap.end();
  if (currentValue == "BOOLEAN" && !isDeclared) {
    // check for declaration since declaration takes precedence
    validateBooleanSelect(it, end);
    return;
  }

  validateSingleSelect(it, end, synonymTypeMap);
}

void SemanticValidator::validateSingleSelect(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end,
    std::unordered_map<std::string, std::string>& synonymTypeMap) {
  throwErrorIfNotDeclared(synonymTypeMap, it);
  std::string synonym = (*it)->getValue();
  it++;  // consume synonym

  if ((it != end) && (*it)->getType() == TokenType::PERIOD) {
    it++;  // consume period
    std::string attrName = (*it)->getValue();
    throwErrorIfAttrNameInvalid(synonymTypeMap, synonym, attrName);
    it++;  // consume attr name
  }
}

void SemanticValidator::validateTupleSelect(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end,
    std::unordered_map<std::string, std::string>& synonymTypeMap) {
  it++;  // consume open angle bracket

  std::string synonym;
  while ((*it)->getType() != TokenType::CLOSE_ANGLE_BRACKET) {
    bool isComma = (*it)->getType() == TokenType::COMMA;
    if (isComma) {
      it++;  // consume comma
      continue;
    }

    validateSingleSelect(it, end, synonymTypeMap);
  }

  it++;  // consume close angle bracket
}

void SemanticValidator::validateBooleanSelect(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end) {
  it++;  // consume "BOOLEAN"
  if (it != end && (*it)->getType() == TokenType::PERIOD) {
    throw SemanticError(NonGrammarRule::BOOLEAN_WITH_ATTR);
  }
}

void SemanticValidator::validateClause(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end,
    std::unordered_map<std::string, std::string>& synonymTypeMap) {
  // validate remaining clause
  while (it != end) {
    bool isSuchThat = (*it)->getValue() == "such";
    bool isPattern = (*it)->getValue() == "pattern";
    bool isWith = (*it)->getValue() == "with";
    if (isSuchThat) {
      it += 2;  // consume "such", "that"
      do {
        // consume "and", then continue validating relation clause
        if ((*it)->getValue() == "and") {
          it++;  // consume "and"
        }

        validateSuchThat(it, synonymTypeMap);
      } while (it != end && (*it)->getValue() == "and");
    } else if (isPattern) {
      it++;  // consume "pattern"
      do {
        // consume "and", then continue validating pattern
        if ((*it)->getValue() == "and") {
          it++;  // consume "and"
        }

        validatePattern(it, synonymTypeMap);
      } while (it != end && (*it)->getValue() == "and");
    } else if (isWith) {
      it++;  // consume "with"
      do {
        // consume "and", then continue validating with
        if ((*it)->getValue() == "and") {
          it++;  // consume "and"
        }

        validateWith(it, synonymTypeMap);
      } while (it != end && (*it)->getValue() == "and");
    }
  }
}

void SemanticValidator::validateSuchThat(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    std::unordered_map<std::string, std::string>& synonymTypeMap) {
  bool hasNotBeforeRel =
      (*it)->getValue() == "not" && (*(it + 1))->getType() == TokenType::NAME;
  if (hasNotBeforeRel) {
    it++;  // consume "not"
  }

  // validate relation clause
  std::string relation = (*it)->getValue();
  it++;  // consume relation
  it++;  // consume open bracket

  if (relation == "Uses" || relation == "Modifies") {
    // Semantic Rules:
    // 1. arg1 not wildcard
    // 2. arg1 must be procedure or stmt, if it is synonym
    // 3. arg2 must be variable, if it is synonym
    throwErrorIfWildcard(it);
    throwErrorIfNotProcedureOrStmt(synonymTypeMap, it);
    isQuotedEntity(it) ? it += 3 : it++;  // consume arg1

    it++;  // consume comma

    throwErrorIfNotVariable(synonymTypeMap, it);
    isQuotedEntity(it) ? it += 3 : it++;  // consume arg2

  } else if (relation == "Calls" || relation == "Calls*") {
    throwErrorIfNotProcedure(synonymTypeMap, it);
    isQuotedEntity(it) ? it += 3 : it++;  // consume arg1

    it++;  // consume comma

    throwErrorIfNotProcedure(synonymTypeMap, it);
    isQuotedEntity(it) ? it += 3 : it++;  // consume arg2
  } else {
    // relation is one of the following:
    // "Follows", "Follows*", "Parent", "Parent*",
    // "Next", "Next*", "Affects"

    // Semantic Rules:
    // 1. arg1 must be stmt or its subtypes, if it is synonym
    // 2. arg2 must be stmt or its subtypes, if it is synonym
    throwErrorIfNotStmt(synonymTypeMap, it);
    it++;  // consume arg1

    it++;  // consume comma

    throwErrorIfNotStmt(synonymTypeMap, it);
    it++;  // consume arg2
  }

  it++;  // consume close bracket
}

void SemanticValidator::validatePattern(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    std::unordered_map<std::string, std::string>& synonymTypeMap) {
  // validate pattern clause
  bool hasNotBeforeSynonym =
      (*it)->getValue() == "not" && (*(it + 1))->getType() == TokenType::NAME;
  if (hasNotBeforeSynonym) {
    it++;  // consume "not"
  }

  throwErrorIfNotDeclared(synonymTypeMap, it);
  std::string synType = getSynonymType(synonymTypeMap, it);
  it++;  // consume assign synonym

  it++;  // consume open bracket

  throwErrorIfPatternArg1NotVariable(synonymTypeMap, it);
  isQuotedEntity(it) ? it += 3 : it++;  // consume arg1

  it++;  // consume comma

  // can determine validity of synType from second argument onward
  consumeRemainingPatternFromSecondArg(synType, it);
}

void SemanticValidator::validateWith(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    std::unordered_map<std::string, std::string>& synonymTypeMap) {
  // Helper function to check token types
  auto checkTokenType = [&](TokenType t1,
                            std::optional<TokenType> t2 = std::nullopt,
                            std::optional<TokenType> t3 = std::nullopt) {
    if ((*it)->getType() != t1) return false;
    if (t2 && (*(it + 1))->getType() != *t2) return false;
    if (t3 && (*(it + 2))->getType() != *t3) return false;
    return true;
  };

  // Helper function to validate and consume tokens
  auto validateAndConsumeRef = [&](bool isInteger, bool isIdent,
                                   bool isSynonym) {
    if (isInteger) {
      it++;  // consume integer
    } else if (isIdent) {
      it += 3;       // consume quoted entity
      return false;  // ref is not integer
    } else if (isSynonym) {
      throwErrorIfNotDeclared(synonymTypeMap, it);
      std::string synonym = (*it)->getValue();
      std::string attrName = (*(it + 2))->getValue();
      throwErrorIfAttrNameInvalid(synonymTypeMap, synonym, attrName);
      it += 3;  // consume synonym
      if (attrName == "procName" || attrName == "varName") {
        return false;  // ref is not integer
      }
    }
    return true;
  };

  bool hasNot = (*it)->getValue() == "not";
  if (hasNot) {
    it++;  // consume "not"
  }

  // attrCompare : ref '=' ref
  // ref : '"' IDENT '"' | INTEGER | synonym '.' attrName

  // First ref
  bool isInteger = checkTokenType(TokenType::INTEGER);
  bool isIdent = checkTokenType(TokenType::DOUBLE_QUOTE, TokenType::NAME,
                                TokenType::DOUBLE_QUOTE);
  bool isSynonym =
      checkTokenType(TokenType::NAME, TokenType::PERIOD, TokenType::ATTR_NAME);
  bool isRef1Integer = validateAndConsumeRef(isInteger, isIdent, isSynonym);

  it++;  // consume equal sign

  // Second ref
  isInteger = checkTokenType(TokenType::INTEGER);
  isIdent = checkTokenType(TokenType::DOUBLE_QUOTE, TokenType::NAME,
                           TokenType::DOUBLE_QUOTE);
  isSynonym =
      checkTokenType(TokenType::NAME, TokenType::PERIOD, TokenType::ATTR_NAME);
  bool isRef2Integer = validateAndConsumeRef(isInteger, isIdent, isSynonym);

  // advanced SPA semantic rule 4
  if (isRef1Integer != isRef2Integer) {
    throw SemanticError(NonGrammarRule::ATTR_NAME_MATCH_COMPARE_VALUE);
  }
}

bool SemanticValidator::isQuotedEntity(
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  return (*it)->getType() == TokenType::DOUBLE_QUOTE &&
         (*(it + 1))->getType() == TokenType::NAME &&
         (*(it + 2))->getType() == TokenType::DOUBLE_QUOTE;
}

bool SemanticValidator::isSynonym(
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  return (*it)->getType() == TokenType::NAME;
}

// semantic rule 1
void SemanticValidator::throwErrorIfDuplicate(
    std::unordered_map<std::string, std::string>& synonymTypeMap,
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  if (isSynonym(it) &&
      synonymTypeMap.find((*it)->getValue()) != synonymTypeMap.end()) {
    throw SemanticError(NonGrammarRule::NO_DUP_SYNONYM);
  }
}

// semantic rule 2
void SemanticValidator::throwErrorIfNotDeclared(
    std::unordered_map<std::string, std::string>& synonymTypeMap,
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  if (isSynonym(it) &&
      synonymTypeMap.find((*it)->getValue()) == synonymTypeMap.end()) {
    throw SemanticError(NonGrammarRule::ALL_SYNONYM_DECLARED);
  }
}

// semantic rule 4
void SemanticValidator::throwErrorIfWildcard(
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  if ((*it)->getType() == TokenType::WILDCARD) {
    throw SemanticError(NonGrammarRule::FIRST_ARG_NOT_WILDCARD);
  }
}

// semantic rule 5
void SemanticValidator::throwErrorIfNotProcedure(
    std::unordered_map<std::string, std::string>& synonymTypeMap,
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  if (isSynonym(it) && getSynonymType(synonymTypeMap, it) != "procedure") {
    throw SemanticError(NonGrammarRule::ARG_ENTITY_MATCH_RELATION);
  }
}

// semantic rule 5
void SemanticValidator::throwErrorIfNotStmt(
    std::unordered_map<std::string, std::string>& synonymTypeMap,
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  std::unordered_set<std::string> nonStmtTypes = {"variable", "constant",
                                                  "procedure"};
  if (isSynonym(it) && nonStmtTypes.find(getSynonymType(synonymTypeMap, it)) !=
                           nonStmtTypes.end()) {
    throw SemanticError(NonGrammarRule::ARG_ENTITY_MATCH_RELATION);
  }
}

// semantic rule 5
void SemanticValidator::throwErrorIfNotProcedureOrStmt(
    std::unordered_map<std::string, std::string>& synonymTypeMap,
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  std::unordered_set<std::string> unexpectedTypes = {"variable", "constant"};
  if (isSynonym(it) && unexpectedTypes.find(getSynonymType(
                           synonymTypeMap, it)) != unexpectedTypes.end()) {
    throw SemanticError(NonGrammarRule::ARG_ENTITY_MATCH_RELATION);
  }
}

// semantic rule 5
void SemanticValidator::throwErrorIfNotVariable(
    std::unordered_map<std::string, std::string>& synonymTypeMap,
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  if (isSynonym(it) && getSynonymType(synonymTypeMap, it) != "variable") {
    throw SemanticError(NonGrammarRule::ARG_ENTITY_MATCH_RELATION);
  }
}

// semantic rule 3
// advanced semantic rule 2, 3
void SemanticValidator::consumeRemainingPatternFromSecondArg(
    std::string& synType, std::vector<std::shared_ptr<Token>>::iterator& it) {
  // currently pointing at second argument

  if (synType == "if") {
    consumeIfPatternFromSecondArg(it);
    return;
  }

  if (synType == "while") {
    consumeWhilePatternFromSecondArg(it);
    return;
  }

  if (synType == "assign") {
    consumeAssignPatternFromSecondArg(it);
    return;
  }

  // if synType is not "if", "while", or "assign"
  throw SemanticError(NonGrammarRule::VALID_PATTERN_SYN);
}

void SemanticValidator::consumeIfPatternFromSecondArg(
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  // expect "if", then second and third argument are wildcards
  bool isIfPatternArgs = (*it)->getType() == TokenType::WILDCARD &&
                         (*(it + 1))->getType() == TokenType::COMMA &&
                         (*(it + 2))->getType() == TokenType::WILDCARD &&
                         (*(it + 3))->getType() == TokenType::CLOSE_BRACKET;
  if (!isIfPatternArgs) {
    throw SemanticError(NonGrammarRule::SYN_IF_IS_IF);
  }
  it += 4;  // consume second and third argument
}

void SemanticValidator::consumeWhilePatternFromSecondArg(
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  // expect "while", then second argument is wildcard
  bool isWhilePatternArgs = (*(it))->getType() == TokenType::WILDCARD &&
                            (*(it + 1))->getType() == TokenType::CLOSE_BRACKET;
  if (!isWhilePatternArgs) {
    throw SemanticError(NonGrammarRule::SYN_WHILE_IS_WHILE);
  }
  it += 2;  // consume second argument
}

void SemanticValidator::consumeAssignPatternFromSecondArg(
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  // expect "assign",
  // then only one more argument (no more comma) till closing bracket
  int openBracketCount = 1;
  while (openBracketCount > 0) {
    if ((*it)->getType() == TokenType::OPEN_BRACKET) {
      openBracketCount++;
    } else if ((*it)->getType() == TokenType::CLOSE_BRACKET) {
      openBracketCount--;
    } else if ((*it)->getType() == TokenType::COMMA) {
      throw SemanticError(NonGrammarRule::SYN_ASSIGN_IS_ASSIGN);
    }
    it++;
  }
}

// semantic rule 6
void SemanticValidator::throwErrorIfPatternArg1NotVariable(
    std::unordered_map<std::string, std::string>& synonymTypeMap,
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  if (isSynonym(it) && getSynonymType(synonymTypeMap, it) != "variable") {
    throw SemanticError(NonGrammarRule::ARG_ENTITY_MATCH_PATTERN);
  }
}

// advanced SPA semantic rule 5
void SemanticValidator::throwErrorIfAttrNameInvalid(
    std::unordered_map<std::string, std::string>& synonymTypeMap,
    const std::string& synonym, const std::string& attrName) {
  // procedure.procName, call.procName, variable.varName, read.varName,
  // print.varName: NAME constant.value: INTEGER stmt.stmt#, read.stmt#,
  // print.stmt#, call.stmt#, while.stmt#, if.stmt#, assign.stmt#: INTEGER
  std::string synonymType = synonymTypeMap.at(synonym);
  std::unordered_set<std::string> validAttrNamesForCurrentSynonym =
      validAttrNames.at(synonymType);
  if (validAttrNamesForCurrentSynonym.find(attrName) ==
      validAttrNamesForCurrentSynonym.end()) {
    throw SemanticError(NonGrammarRule::SYNONYM_MATCH_ATTR_NAME);
  }
}

std::string SemanticValidator::getSynonymType(
    std::unordered_map<std::string, std::string>& synonymTypeMap,
    std::vector<std::shared_ptr<Token>>::iterator& it) {
  throwErrorIfNotDeclared(synonymTypeMap, it);
  return synonymTypeMap.at((*it)->getValue());
}
}  // namespace QPS
