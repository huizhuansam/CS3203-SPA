#include "SymbolTokenHandler.h"

#include <functional>
#include <memory>
#include <stdexcept>
#include <unordered_map>

#include "StringHandler.h"

namespace SP {
std::unordered_map<char, std::function<std::unique_ptr<Token>()>>
    SymbolTokenHandler::charToTokenHandlerMap = {
        {
            ';',
            []() { return std::make_unique<Token>(TokenType::SEMICOLON, ";"); },
        },
        {
            '{',
            []() {
              return std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET,
                                             "{");
            },
        },
        {
            '}',
            []() {
              return std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET,
                                             "}");
            },
        },
        {
            '(',
            []() {
              return std::make_unique<Token>(TokenType::OPEN_BRACKET, "(");
            },
        },
        {
            ')',
            []() {
              return std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")");
            },
        },
        {
            '+',
            []() { return std::make_unique<Token>(TokenType::PLUS, "+"); },
        },
        {
            '-',
            []() { return std::make_unique<Token>(TokenType::MINUS, "-"); },
        },
        {
            '*',
            []() { return std::make_unique<Token>(TokenType::MULTIPLY, "*"); },
        },
        {
            '/',
            []() { return std::make_unique<Token>(TokenType::DIVIDE, "/"); },
        },
        {
            '%',
            []() { return std::make_unique<Token>(TokenType::MODULO, "%"); },
        },
};

std::unordered_map<
    char, std::function<std::unique_ptr<Token>(std::string::const_iterator&,
                                               std::string::const_iterator&)>>
    SymbolTokenHandler::charToSpecialTokenHandlerMap = {
        {
            '!',
            [](std::string::const_iterator& it,
               std::string::const_iterator& end) {
              return handleExclamationMark(it, end);
            },
        },
        {
            '=',
            [](std::string::const_iterator& it,
               std::string::const_iterator& end) {
              return handleEqual(it, end);
            },
        },
        {
            '<',
            [](std::string::const_iterator& it,
               std::string::const_iterator& end) {
              return handleLessThan(it, end);
            },
        },
        {
            '>',
            [](std::string::const_iterator& it,
               std::string::const_iterator& end) {
              return handleGreaterThan(it, end);
            },
        },
        {
            '&',
            [](std::string::const_iterator& it,
               std::string::const_iterator& end) {
              return handleAmpersand(it, end);
            },
        },
        {
            '|',
            [](std::string::const_iterator& it,
               std::string::const_iterator& end) {
              return handleVerticalBar(it, end);
            },
        },
};

std::unique_ptr<Token> SymbolTokenHandler::handleToken(
    std::string::const_iterator& it, std::string::const_iterator& end) {
  if (it == end) {
    throw std::runtime_error("Symbol not recognized: ");
  }
  char currentChar = *it;
  bool charIsInCharToTokenHandlerMap =
      charToTokenHandlerMap.count(currentChar) > 0;
  bool charIsInCharToSpecialTokenHandlerMap =
      charToSpecialTokenHandlerMap.count(currentChar) > 0;
  if (!charIsInCharToTokenHandlerMap && !charIsInCharToSpecialTokenHandlerMap) {
    throw std::runtime_error("Symbol not recognized: " +
                             std::string(1, currentChar));
  }
  return charIsInCharToTokenHandlerMap
             ? charToTokenHandlerMap[currentChar]()
             : charToSpecialTokenHandlerMap[currentChar](it, end);
}

std::unique_ptr<Token> SymbolTokenHandler::handleExclamationMark(
    std::string::const_iterator& it, std::string::const_iterator& end) {
  if (StringHandler::hasNextChar(it, end) &&
      StringHandler::getNextChar(it) == '=') {
    StringHandler::pointNextChar(it);
    return std::make_unique<Token>(TokenType::NEQ, "!=");
  }
  return std::make_unique<Token>(TokenType::NOT, "!");
}

std::unique_ptr<Token> SymbolTokenHandler::handleEqual(
    std::string::const_iterator& it, std::string::const_iterator& end) {
  if (StringHandler::hasNextChar(it, end) &&
      StringHandler::getNextChar(it) == '=') {
    StringHandler::pointNextChar(it);
    return std::make_unique<Token>(TokenType::EQ, "==");
  }
  return std::make_unique<Token>(TokenType::ASSIGN, "=");
}

std::unique_ptr<Token> SymbolTokenHandler::handleLessThan(
    std::string::const_iterator& it, std::string::const_iterator& end) {
  if (StringHandler::hasNextChar(it, end) &&
      StringHandler::getNextChar(it) == '=') {
    StringHandler::pointNextChar(it);
    return std::make_unique<Token>(TokenType::LTE, "<=");
  }
  return std::make_unique<Token>(TokenType::LT, "<");
}

std::unique_ptr<Token> SymbolTokenHandler::handleGreaterThan(
    std::string::const_iterator& it, std::string::const_iterator& end) {
  if (StringHandler::hasNextChar(it, end) &&
      StringHandler::getNextChar(it) == '=') {
    StringHandler::pointNextChar(it);
    return std::make_unique<Token>(TokenType::GTE, ">=");
  }
  return std::make_unique<Token>(TokenType::GT, ">");
}

std::unique_ptr<Token> SymbolTokenHandler::handleAmpersand(
    std::string::const_iterator& it, std::string::const_iterator& end) {
  if (!(StringHandler::hasNextChar(it, end) &&
        StringHandler::getNextChar(it) == '&')) {
    throw std::runtime_error("Invalid token found: &");
  }
  StringHandler::pointNextChar(it);
  return std::make_unique<Token>(TokenType::AND, "&&");
}

std::unique_ptr<Token> SymbolTokenHandler::handleVerticalBar(
    std::string::const_iterator& it, std::string::const_iterator& end) {
  if (!(StringHandler::hasNextChar(it, end) &&
        StringHandler::getNextChar(it) == '|')) {
    throw std::runtime_error("Invalid token found: |");
  }
  StringHandler::pointNextChar(it);
  return std::make_unique<Token>(TokenType::OR, "||");
}

}  // namespace SP
