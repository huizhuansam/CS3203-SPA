#pragma once

#include "IExtractor.h"
#include "WriteFacade.h"

namespace SP {
/// @brief Extractor for procedures
class ProcedureExtractor : public IExtractor {
 private:
  WriteFacade& writer;
  std::string nameOfProcedureExtracted;
  std::unordered_set<std::string> varUsed;
  std::unordered_set<std::string> varModified;
  std::unordered_set<std::string> procCalled;
  std::unordered_map<int, std::unordered_set<std::string>> stmtCallMap;

 public:
  /// @brief Construct a new Procedure Extractor object
  /// @param writer A write facade providing write access to the PKB
  ProcedureExtractor(WriteFacade& writer);

  /// @brief Extract procedures from a token vector
  /// @param it The iterator to the current token
  /// @param end The iterator to the end of the token vector
  void extract(
      std::vector<std::unique_ptr<Token>>::iterator& it,
      const std::vector<std::unique_ptr<Token>>::iterator& end) override;

  /// @brief Get the procedure name this extractor extracted
  std::string getNameOfProcedureExtracted();

  /// @brief Get variables used in this procedure
  /// @return A set of variable names used in this procedure
  std::unordered_set<std::string>& getVarUsed();

  /// @brief Get variables modified in this procedure
  /// @return A set of variable names modified in this procedure
  std::unordered_set<std::string>& getVarModified();

  /// @brief Get procedures called in this procedure
  /// @return A set of procedure names called in this procedure
  std::unordered_set<std::string>& getProcCalled();

  /// @brief Get the statement call map
  /// @return A map of statement number to set of procedure names
  /// called
  std::unordered_map<int, std::unordered_set<std::string>>& getStmtCallMap();
};
}  // namespace SP
