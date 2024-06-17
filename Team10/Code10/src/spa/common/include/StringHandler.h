#pragma once

#include <string>

class StringHandler {
 public:
  static bool isWhitespace(char ch);

  static bool isValidSourceSymbol(char ch);

  static bool isValidQuerySymbol(char ch);

  static bool isLetter(char ch);

  static bool isDigit(char ch);

  static bool hasNextChar(std::string::const_iterator& it,
                          std::string::const_iterator& end);

  static char getNextChar(std::string::const_iterator& it);

  static void pointNextChar(std::string::const_iterator& it);

  static bool hasPreviousChar(std::string::const_iterator& it,
                              std::string::const_iterator& end);

  static void pointPreviousChar(std::string::const_iterator& it);

  static std::string formWordString(std::string::const_iterator& it,
                                    std::string::const_iterator& end);

  static std::string formNumberString(std::string::const_iterator& it,
                                      std::string::const_iterator& end);
};
