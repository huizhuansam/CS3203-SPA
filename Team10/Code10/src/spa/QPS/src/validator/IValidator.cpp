#include "validator/IValidator.h"

namespace QPS {
void IValidator::expect(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end,
    TokenType expectedType, const std::string& rule) {
  if (it == end || (*it)->getType() != expectedType) {
    throw SyntaxError(rule);
  }
}

void IValidator::expect(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end,
    const std::string& expectedValue, const std::string& rule) {
  if (it == end || (*it)->getValue() != expectedValue) {
    throw SyntaxError(rule);
  }
}

void IValidator::consume(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end, TokenType type,
    const std::string& rule) {
  expect(it, end, type, rule);
  it++;
}

void IValidator::consume(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end,
    const std::string& value, const std::string& rule) {
  expect(it, end, value, rule);
  it++;
}

void IValidator::consumeOptional(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end, TokenType type) {
  if (it != end && (*it)->getType() == type) {
    it++;
  }
}

void IValidator::consumeOptional(
    std::vector<std::shared_ptr<Token>>::iterator& it,
    const std::vector<std::shared_ptr<Token>>::iterator& end,
    const std::string& value) {
  if (it != end && (*it)->getValue() == value) {
    it++;
  }
}
}  // namespace QPS
