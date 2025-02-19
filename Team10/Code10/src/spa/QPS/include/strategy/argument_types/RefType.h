#pragma once

namespace QPS {
enum class RefType {
  IDENT,
  INTEGER,
  // attrRefs with format SYNONYM_ATTRNAME
  PROCEDURE_PROCNAME,
  CALL_PROCNAME,
  VARIABLE_VARNAME,
  READ_VARNAME,
  PRINT_VARNAME,
  CONSTANT_VALUE,
  STMT_STMTNO,
  READ_STMTNO,
  PRINT_STMTNO,
  CALL_STMTNO,
  WHILE_STMTNO,
  IF_STMTNO,
  ASSIGN_STMTNO,
  NONE
};
}  // namespace QPS
