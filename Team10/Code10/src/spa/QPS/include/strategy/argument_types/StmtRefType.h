#pragma once

namespace QPS {
enum class StmtRefType {
  STMT,
  READ,
  PRINT,
  CALL,
  WHILE,
  IF,
  ASSIGN,
  VARIABLE,
  CONSTANT,
  PROCEDURE,
  WILDCARD,
  INTEGER,
  INVALID
};
}  // namespace QPS
