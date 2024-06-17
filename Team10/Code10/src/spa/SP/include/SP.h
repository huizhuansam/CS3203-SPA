#pragma once

#include <string>

#include "PKB.h"

namespace SP {
/// @brief The SP class is the main class of the SP module
class SP {
 public:
  /// @brief Processes the source code
  /// @param input The source code to be processed
  static void processSimple(const std::string& input);

  SP() = delete;  // Disallow instantiation
};
}  // namespace SP
