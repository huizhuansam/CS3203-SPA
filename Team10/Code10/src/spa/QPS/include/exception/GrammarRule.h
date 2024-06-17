#pragma once

#include <string>

namespace QPS {
class GrammarRule {
 public:
  static const std::string NAME;
  static const std::string INTEGER;
  static const std::string ATTR_NAME;
  static const std::string SELECT_CL;
  static const std::string DECLARATION;
  static const std::string RESULT_CL;
  static const std::string TUPLE;
  static const std::string DESIGN_ENTITY;
  static const std::string SUCHTHAT_CL;
  static const std::string WITH_CL;
  static const std::string ATTR_COND;
  static const std::string ATTR_COMPARE;
  static const std::string REF;
  static const std::string REL_COND;
  static const std::string REL_REF;
  static const std::string FOLLOWS;
  static const std::string FOLLOWS_T;
  static const std::string PARENT;
  static const std::string PARENT_T;
  static const std::string USES_S;
  static const std::string USES_P;
  static const std::string MODIFIES_S;
  static const std::string MODIFIES_P;
  static const std::string PATTERN_CL;
  static const std::string PATTERN_COND;
  static const std::string PATTERN;
  static const std::string EXPRESSION_SPEC;
  static const std::string EXPR;
  static const std::string TERM;
  static const std::string FACTOR;
  static const std::string SYN_ASSIGN;
  static const std::string VAR_NAME;
  static const std::string CONSTANT_VALUE;
  static const std::string ASSIGN;
  static const std::string WHILE;
  static const std::string IF;
  static const std::string ENT_REF;
};
}  // namespace QPS
