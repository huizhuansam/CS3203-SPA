#pragma once

#include <memory>
#include <vector>

#include "../exception/SyntaxError.h"
#include "../tokenizer/Token.h"
#include "../tokenizer/TokenType.h"

namespace QPS {
class IValidator {
 public:
  virtual void validate(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end) = 0;

  virtual void expect(std::vector<std::shared_ptr<Token>>::iterator& it,
                      const std::vector<std::shared_ptr<Token>>::iterator& end,
                      TokenType expectedType, const std::string& rule);

  virtual void expect(std::vector<std::shared_ptr<Token>>::iterator& it,
                      const std::vector<std::shared_ptr<Token>>::iterator& end,
                      const std::string& expectedValue,
                      const std::string& rule);

  virtual void consume(std::vector<std::shared_ptr<Token>>::iterator& it,
                       const std::vector<std::shared_ptr<Token>>::iterator& end,
                       TokenType type, const std::string& rule);

  virtual void consume(std::vector<std::shared_ptr<Token>>::iterator& it,
                       const std::vector<std::shared_ptr<Token>>::iterator& end,
                       const std::string& value, const std::string& rule);

  virtual void consumeOptional(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end, TokenType type);

  virtual void consumeOptional(
      std::vector<std::shared_ptr<Token>>::iterator& it,
      const std::vector<std::shared_ptr<Token>>::iterator& end,
      const std::string& value);

  virtual ~IValidator() = default;
};
}  // namespace QPS
