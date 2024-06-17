#pragma once

#include "IExtractor.h"
#include "WriteFacade.h"

namespace SP {
/// @brief Extractor for the program
class ProgramExtractor : public IExtractor {
 private:
  WriteFacade& writer;
  // key: procedure name, value: set of procedure names called by the procedure
  std::unordered_map<std::string, std::unordered_set<std::string>> procCallMap;
  // key: procedure name, value: set of variable names used by the procedure
  std::unordered_map<std::string, std::unordered_set<std::string>>
      procVarUsedMap;
  // key: procedure name, value: set of variable names modified by the procedure
  std::unordered_map<std::string, std::unordered_set<std::string>>
      procVarModifiedMap;

  // key: statement number, value: set of procedure names called by the
  // statement
  std::unordered_map<int, std::unordered_set<std::string>> stmtCallMap;

  std::unordered_map<std::string, std::unordered_set<std::string>> procUsesMemo;
  std::unordered_map<std::string, std::unordered_set<std::string>>
      procModifiesMemo;

 public:
  /// @brief Construct a new Program Extractor object
  /// @param writer A write facade providing write access to the PKB
  ProgramExtractor(WriteFacade& writer);

  /// @brief Extract the program from a token vector
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  void extract(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end) override;

 private:
  std::unordered_set<std::string> getAllVarModifiedByProc(
      const std::string& procName);

  std::unordered_set<std::string> getAllVarUsedByProc(
      const std::string& procName);
};
}  // namespace SP
