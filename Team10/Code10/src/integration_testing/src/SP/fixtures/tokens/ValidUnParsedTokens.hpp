#pragma once

#include <string>

#include "tokenizer/Token.h"

namespace SP {

class ValidUnParsedTokens {
 public:
  static std::vector<std::unique_ptr<Token>> valid_unparsed_tokens;
  static std::vector<std::unique_ptr<Token>> valid_unparsed_tokens_2;
  static std::vector<std::unique_ptr<Token>> valid_unparsed_tokens_3;
  static std::vector<std::unique_ptr<Token>> valid_unparsed_tokens_4;
  static std::vector<std::unique_ptr<Token>> valid_unparsed_tokens_5;
};

std::vector<std::unique_ptr<Token>> ValidUnParsedTokens::valid_unparsed_tokens =
    [] {
      std::vector<std::unique_ptr<Token>> tokens;
      tokens.push_back(
          std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::NAME, "computeCentroid"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "count"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "count"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::AND, "&&"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "count"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "count"));
      tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "count"));
      tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "flag"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::DIVIDE, "/"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "count"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::DIVIDE, "/"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "count"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "normSq"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "normSq"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      return tokens;
    }();

std::vector<std::unique_ptr<Token>>
    ValidUnParsedTokens::valid_unparsed_tokens_2 = [] {
      std::vector<std::unique_ptr<Token>> tokens;
      tokens.push_back(
          std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "main"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "flag"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "readPoint"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::NAME, "printResults"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "flag"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "normSq"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::NAME, "computeCentroid"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "count"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::AND, "&&"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "count"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "count"));
      tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "count"));
      tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "flag"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::DIVIDE, "/"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "count"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::DIVIDE, "/"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "count"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "normSq"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenX"));
      tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "cenY"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      return tokens;
    }();

std::vector<std::unique_ptr<Token>>
    ValidUnParsedTokens::valid_unparsed_tokens_3 = [] {
      std::vector<std::unique_ptr<Token>> tokens;
      tokens.push_back(
          std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
      tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
      tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
      tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
      tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
      tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
      tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
      tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "11"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
      tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
      tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "22"));
      tokens.push_back(std::make_unique<Token>(TokenType::MINUS, "-"));
      tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
      tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "33"));
      tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
      tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      return tokens;
    }();

std::vector<std::unique_ptr<Token>>
    ValidUnParsedTokens::valid_unparsed_tokens_4 = [] {
      std::vector<std::unique_ptr<Token>> tokens;
      tokens.push_back(
          std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "deepIfWhile"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
      tokens.push_back(std::make_unique<Token>(TokenType::LT, "<"));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "3"));
      tokens.push_back(std::make_unique<Token>(TokenType::GT, ">"));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "4"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "5"));
      tokens.push_back(std::make_unique<Token>(TokenType::LTE, "<="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "6"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "7"));
      tokens.push_back(std::make_unique<Token>(TokenType::GTE, ">="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "8"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "9"));
      tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "10"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "11"));
      tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "12"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::OR, "||"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NOT, "!"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "z"));
      tokens.push_back(std::make_unique<Token>(TokenType::MODULO, "%"));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
      tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::OR, "||"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::AND, "&&"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NOT, "!"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
      tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::AND, "&&"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
      tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      return tokens;
    }();

std::vector<std::unique_ptr<Token>>
    ValidUnParsedTokens::valid_unparsed_tokens_5 = [] {
      std::vector<std::unique_ptr<Token>> tokens;
      tokens.push_back(
          std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
      tokens.push_back(std::make_unique<Token>(
          TokenType::NAME, "complexCondExprWithComplexExpr"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NOT, "!"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
      tokens.push_back(std::make_unique<Token>(TokenType::LT, "<"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "5"));
      tokens.push_back(std::make_unique<Token>(TokenType::DIVIDE, "/"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::MINUS, "-"));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "3"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::OR, "||"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "3"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "5"));
      tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::AND, "&&"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "3"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "5"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::AND, "&&"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "3"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
      tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "5"));
      tokens.push_back(std::make_unique<Token>(TokenType::MODULO, "%"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::OR, "||"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::GTE, ">="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::OR, "||"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::LTE, "<="));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::AND, "&&"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NOT, "!"));
      tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::GT, ">"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
      tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
      tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
      tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      tokens.push_back(
          std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
      return tokens;
    }();
}  // namespace SP
