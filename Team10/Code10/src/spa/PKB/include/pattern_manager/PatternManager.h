#include <string>

#include "AssignExpPatternStore.h"
#include "TwoWayMapManager.h"

class PatternManager {
 private:
  AssignExpPatternStore assignExpPatternStore;
  TwoWayMapManager<int, std::string> whileExpPatternStore;
  TwoWayMapManager<int, std::string> ifExpPatternStore;

 public:
  void addAssignExpPattern(int stmtNo, const std::string& var,
                           const std::vector<std::string>& exp);

  void addWhileControlVariable(int stmtNo, const std::string& var);
  void addIfControlVariable(int stmtNo, const std::string& var);

  void clear();

  // assign
  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllAssignExpPairs();

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsPartialMatch(const std::string& var,
                                const std::vector<std::string>& infixTokens);

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsSynonymPartialMatch(
      const std::vector<std::string>& infixTokens);

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsExactMatch(const std::string& var,
                              const std::vector<std::string>& infixTokens);

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsSynonymExactMatch(
      const std::vector<std::string>& infixTokens);

  // while
  std::unordered_set<std::string> getControlVariableOfWhileStmt(int stmtNo);
  std::unordered_set<int> getWhileStmtsThatUseControlVariable(
      const std::string& var);
  std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllWhileControlVariablePairs();
  std::unordered_set<int> getAllWhileStmtsThatUseControlVariables();
  std::unordered_set<std::string> getAllWhileControlVariables();

  // if
  std::unordered_set<std::string> getControlVariableOfIfStmt(int stmtNo);
  std::unordered_set<int> getIfStmtsThatUseControlVariable(
      const std::string& var);
  std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllIfControlVariablePairs();
  std::unordered_set<int> getAllIfStmtsThatUseControlVariables();
  std::unordered_set<std::string> getAllIfControlVariables();
};
