#pragma once

#include <list>
#include <string>

#include "./evaluator/Evaluator.h"
#include "./exception/SemanticError.h"
#include "./exception/SyntaxError.h"
#include "./optimizer/Optimizer.h"
#include "./parser/Parser.h"
#include "./tokenizer/Token.h"
#include "./tokenizer/Tokenizer.h"
#include "./validator/Validator.h"
#include "ReadFacade.h"

namespace QPS {
class QPS {
 public:
  static std::list<std::string> evaluate(
      [[maybe_unused]] const std::string& query);

  QPS() = delete;  // Disallow instantiation
};
}  // namespace QPS
