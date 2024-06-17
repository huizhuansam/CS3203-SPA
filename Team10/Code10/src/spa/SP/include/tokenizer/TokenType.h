#pragma once

namespace SP {
enum class TokenType {
  // Dynamic tokens
  NAME,
  INTEGER,

  // Static tokens
  // Keywords
  PROCEDURE,
  READ,
  PRINT,
  CALL,
  WHILE,
  IF,
  THEN,
  ELSE,

  // Separators
  SEMICOLON,
  OPEN_CURLY_BRACKET,
  CLOSE_CURLY_BRACKET,
  OPEN_BRACKET,
  CLOSE_BRACKET,

  // Relational operators
  GT,
  GTE,
  LT,
  LTE,
  EQ,
  NEQ,

  // Logical operators
  NOT,
  AND,
  OR,

  // Assignment operator
  ASSIGN,

  // Arithmetic operators
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  MODULO,

  // White space
  WHITESPACE,
};
}  // namespace SP
