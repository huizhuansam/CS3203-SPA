#pragma once

#include <string>

namespace QPS {
class NonGrammarRule {
 public:
  static const std::string NO_DUP_SYNONYM;
  static const std::string ALL_SYNONYM_DECLARED;
  static const std::string SYN_ASSIGN_IS_ASSIGN;
  static const std::string FIRST_ARG_NOT_WILDCARD;
  static const std::string ARG_ENTITY_MATCH_RELATION;
  static const std::string ARG_ENTITY_MATCH_PATTERN;
  static const std::string SYNONYM_MATCH_ATTR_NAME;
  static const std::string ATTR_NAME_MATCH_COMPARE_VALUE;
  static const std::string SYN_WHILE_IS_WHILE;
  static const std::string SYN_IF_IS_IF;
  static const std::string VALID_PATTERN_SYN;
  static const std::string BOOLEAN_WITH_ATTR;
};
}  // namespace QPS
