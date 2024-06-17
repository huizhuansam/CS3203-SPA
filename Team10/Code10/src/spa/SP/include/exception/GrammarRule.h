#pragma once

#include <string>

namespace SP {
class GrammarRule {
 public:
  static const std::string NAME;
  static const std::string INTEGER;
  static const std::string SYNONYM;
  static const std::string STMT_REF;
  static const std::string ENT_REF;
  static const std::string PROGRAM;
  static const std::string PROCEDURE;
  static const std::string STMT_LIST;
  static const std::string STMT;
  static const std::string READ;
  static const std::string PRINT;
  static const std::string CALL;
  static const std::string WHILE;
  static const std::string IF;
  static const std::string ASSIGN;
  static const std::string COND_EXPR;
  static const std::string REL_EXPR;
  static const std::string REL_FACTOR;
  static const std::string EXPR;
  static const std::string TERM;
  static const std::string FACTOR;
  static const std::string VAR_NAME;
  static const std::string PROC_NAME;
  static const std::string CONST_VALUE;
  static const std::string STMT_NO;
};
}  // namespace SP
