#include "StringHandler.h"

#include <regex>

bool StringHandler::isWhitespace(char ch) { return std::isspace(ch); }

bool StringHandler::isValidSourceSymbol(char ch) {
  std::regex symbolRegex("[;{}()\\+\\-\\*/%!\\=<>\\&\\|]");
  return std::regex_match(std::string(1, ch), symbolRegex);
}

bool StringHandler::isValidQuerySymbol(char ch) {
  std::regex symbolRegex("[;()\\+\\-\\*/%,_<>.=\"]");
  return std::regex_match(std::string(1, ch), symbolRegex);
}

bool StringHandler::isLetter(char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool StringHandler::isDigit(char ch) { return ch >= '0' && ch <= '9'; }

bool StringHandler::hasNextChar(std::string::const_iterator& it,
                                std::string::const_iterator& end) {
  return (it + 1) != end;
}

char StringHandler::getNextChar(std::string::const_iterator& it) {
  return *(it + 1);
}

void StringHandler::pointNextChar(std::string::const_iterator& it) { it++; }

bool StringHandler::hasPreviousChar(std::string::const_iterator& it,
                                    std::string::const_iterator& end) {
  return it != end;
}

void StringHandler::pointPreviousChar(std::string::const_iterator& it) { it--; }

std::string StringHandler::formWordString(std::string::const_iterator& it,
                                          std::string::const_iterator& end) {
  std::string word;
  while (it != end && (isLetter(*it) || isDigit(*it))) {
    word += *it;
    pointNextChar(it);
  }
  // go back to the last character of the word
  pointPreviousChar(it);
  return word;
}

std::string StringHandler::formNumberString(std::string::const_iterator& it,
                                            std::string::const_iterator& end) {
  std::string number;
  while (it != end && isDigit(*it)) {
    number += *it;
    pointNextChar(it);
  }
  // go back to the last character of the number
  pointPreviousChar(it);
  return number;
}
