#pragma once

namespace QPS {
enum class EntRefType {
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
  IDENT,
  INVALID
};
}  // namespace QPS
