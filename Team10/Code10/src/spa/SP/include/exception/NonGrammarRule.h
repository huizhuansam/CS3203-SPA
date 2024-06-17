#pragma once

#include <string>

namespace SP {
class NonGrammarRule {
 public:
  static const std::string NO_DUP_PROC;
  static const std::string NO_CALL_TO_UNDEF_PROC;
  static const std::string NO_RECURSIVE_OR_CYCLIC_CALL;
};
}  // namespace SP
