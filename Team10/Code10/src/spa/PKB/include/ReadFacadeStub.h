// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/a56660b9-506a-4919-9450-f4c6e996201e
#pragma once

#include <PKB.h>
#include <ReadFacade.h>

#include <iostream>
#include <string>
#include <vector>

class ReadFacadeStub : public ReadFacade {
 private:
  [[maybe_unused]] PKB* pkb = nullptr;

 public:
  // Entity Manager methods
  std::unordered_set<std::string> getAllVariables() override {
    return {"a", "b", "c"};
  };

  std::unordered_set<std::string> getAllConstants() override {
    return {"0", "7", "8", "9", "20", "1", "2"};
  };

  std::unordered_set<std::string> getAllProcedures() override {
    return {"main", "call", "b"};
  };

  std::unordered_set<int> getStatements() override {
    return {1, 2, 3, 4, 5, 6};
  };

  std::unordered_set<int> getAssigns() override {
    return {1, 2, 5, 6, 7, 9, 10, 13};
  };

  std::unordered_set<int> getReads() override { return {14, 16, 17}; };

  std::unordered_set<int> getPrints() override { return {1, 2, 12, 15}; };

  std::unordered_set<int> getCalls() override { return {7, 8, 9}; };

  std::unordered_set<int> getWhiles() override { return {3, 10, 11}; };

  std::unordered_set<int> getIfs() override { return {4, 8}; };

  // Pattern Manager Methods
  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsPartialMatch(
      [[maybe_unused]] const std::string& var,
      [[maybe_unused]] const std::vector<std::string>& infixTokens) override {
    return {{"1", "a"}, {"2", "b"}};
  };

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsSynonymPartialMatch(
      [[maybe_unused]] const std::vector<std::string>& infixTokens) override {
    return {{"2", "b"}, {"5", "c"}, {"6", "c"}};
  };

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsExactMatch(
      [[maybe_unused]] const std::string& var,
      [[maybe_unused]] const std::vector<std::string>& infixTokens) override {
    return {{"1", "a"}};
  }

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsSynonymExactMatch(
      [[maybe_unused]] const std::vector<std::string>& infixTokens) override {
    return {{"2", "b"}, {"5", "c"}};
  }

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllAssignExpPairs() override {
    return {{"1", "a"}, {"2", "b"}, {"5", "c"}, {"6", "c"}};
  };

  std::unordered_set<std::string> getControlVariableOfWhileStmt(
      [[maybe_unused]] int stmtNo) override {
    return {"a"};
  }

  std::unordered_set<int> getWhileStmtsThatUseControlVariable(
      [[maybe_unused]] const std::string& var) override {
    return {1, 2, 3};
  }

  std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllWhileControlVariablePairs() override {
    return {{1, "a"}, {2, "a"}, {3, "a"}, {4, "A"}, {5, "b"}, {6, "c"}};
  }

  std::unordered_set<int> getAllWhileStmtsThatUseControlVariables() override {
    return {1, 2, 3, 4, 5, 6};
  }

  std::unordered_set<std::string> getAllWhileControlVariables() override {
    return {"a", "A", "b", "c"};
  }

  std::unordered_set<std::string> getControlVariableOfIfStmt(
      [[maybe_unused]] int stmtNo) override {
    return {"a", "b"};
  }

  std::unordered_set<int> getIfStmtsThatUseControlVariable(
      [[maybe_unused]] const std::string& var) override {
    return {1, 2, 3};
  }

  std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllIfControlVariablePairs() override {
    return {{1, "a"}, {2, "a"}, {3, "a"}, {4, "A"}, {5, "b"}, {6, "c"}};
  }

  std::unordered_set<int> getAllIfStmtsThatUseControlVariables() override {
    return {1, 2, 3, 4, 5, 6};
  }

  std::unordered_set<std::string> getAllIfControlVariables() override {
    return {"a", "A", "b", "c"};
  }

  // Relationship Manager Methods
  // parent
  std::unordered_set<int> getChildren(
      [[maybe_unused]] int parentStmtNo) override {
    return {4, 5, 6, 7};
  };

  int getParent([[maybe_unused]] int childStmtNo) override { return 3; };

  std::unordered_set<int> getChildrenStar(
      [[maybe_unused]] int parentStmtNo) override {
    return {4, 5, 6, 7};
  };

  std::unordered_set<int> getParentStar(
      [[maybe_unused]] int childStmtNo) override {
    return {1, 2, 3};
  };

  std::unordered_set<std::pair<int, int>, PairHash> getAllParentPairs()
      override {
    return {{1, 2}, {3, 4}, {5, 6}};
  };

  std::unordered_set<std::pair<int, int>, PairHash> getAllParentStarPairs()
      override {
    return {{1, 2}, {1, 3}, {2, 3}};
  }

  std::unordered_set<int> getAllChildren() override { return {2, 3, 4, 5, 6}; };

  std::unordered_set<int> getAllParents() override { return {1, 2, 3}; };

  // follows
  int getStmtThatFollowsAfter([[maybe_unused]] int stmtNo) override {
    return 4;
  };

  int getStmtThatFollowsBefore([[maybe_unused]] int stmtNo) override {
    return 3;
  };

  std::unordered_set<int> getAllStmtsThatFollowAfter(
      [[maybe_unused]] int stmtNo) override {
    return {10, 11, 12, 13};
  };

  std::unordered_set<int> getAllStmtsThatFollowBefore(
      [[maybe_unused]] int stmtNo) override {
    return {4, 5, 6};
  };

  std::unordered_set<std::pair<int, int>, PairHash> getAllFollowPairs()
      override {
    return {{1, 2}, {3, 4}, {5, 6}};
  };

  std::unordered_set<std::pair<int, int>, PairHash> getAllFollowStarPairs()
      override {
    return {{1, 2}, {1, 3}, {2, 3}};
  }

  std::unordered_set<int> getAllStmtsThatFollowAfterOtherStmts() override {
    return {4, 5, 6, 7};
  }

  std::unordered_set<int> getAllStmtsThatFollowBeforeOtherStmts() override {
    return {1, 2, 3};
  }

  // calls
  std::unordered_set<std::string> getProcsThatIsCalledBy(
      [[maybe_unused]] std::string& sourceProcName) override {
    return {"Second"};
  }

  std::unordered_set<std::string> getProcsThatCalls(
      [[maybe_unused]] std::string& targetProcName) override {
    return {"Second"};
  }

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllCallPairs() override {
    return {{"First", "Second"}, {"Second", "Third"}};
  }

  std::unordered_set<std::string> getAllProcsThatCallOtherProcs() override {
    return {"First", "Second"};
  }

  std::unordered_set<std::string> getAllProcsThatGetCalledByOtherProcs()
      override {
    return {"Second", "Third"};
  }

  // calls*
  std::unordered_set<std::string> getProcsThatIsCalledByStar(
      [[maybe_unused]] std::string& sourceProcName) override {
    return {"Second", "Third"};
  }

  std::unordered_set<std::string> getProcsThatCallsStar(
      [[maybe_unused]] std::string& targetProcName) override {
    return {"First", "Second"};
  }

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllCallStarPairs() override {
    return {{"First", "Second"}, {"First", "Third"}, {"Second", "Third"}};
  }

  // modifies
  std::unordered_set<std::string> getVarsModifiedByStmt(
      [[maybe_unused]] int stmtNo) override {
    return {"a", "b"};
  };

  std::unordered_set<int> getStmtsThatModifyVar(
      [[maybe_unused]] std::string str) override {
    return {1, 2, 3, 9};
  };

  std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllVarModifiedByStmtPairs() override {
    return {{1, "a"}, {2, "b"}, {3, "c"}};
  };

  std::unordered_set<std::string> getVarsModifiedByProcedure(
      [[maybe_unused]] std::string& str) override {
    return {"a", "b", "c", "d"};
  };

  std::unordered_set<std::string> getProceduresThatModifyVar(
      [[maybe_unused]] std::string& str) override {
    return {"main", "call"};
  };

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllVarModifiedByProcedurePairs() override {
    return {{"main", "a"}, {"main", "c"}, {"call", "d"}};
  };

  std::unordered_set<int> getAllStmtsThatModifyVars() override {
    return {1, 2, 3};
  }

  std::unordered_set<std::string> getAllVarsModifiedByStmts() override {
    return {"a", "b"};
  }

  std::unordered_set<std::string> getAllProceduresThatModifyVars() override {
    return {"main", "call", "fun"};
  }

  std::unordered_set<std::string> getAllVarsModifiedByProcedures() override {
    return {"a", "b", "c"};
  }

  // uses
  std::unordered_set<std::string> getVarsUsedByStmt(
      [[maybe_unused]] int stmtNo) override {
    return {"a", "c"};
  };

  std::unordered_set<int> getStmtsThatUseVar(
      [[maybe_unused]] std::string str) override {
    return {1, 2, 3};
  };

  std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllVarUsedByStmtPairs() override {
    return {{1, "a"}, {2, "c"}, {3, "b"}};
  };

  std::unordered_set<std::string> getVarsUsedByProcedure(
      [[maybe_unused]] std::string str) override {
    return {"a", "b"};
  };

  std::unordered_set<std::string> getProceduresThatUseVar(
      [[maybe_unused]] std::string str) override {
    return {"main", "call"};
  };

  std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllVarUsedByProcedurePairs() override {
    return {{"main", "d"}, {"call", "a"}, {"main", "ef"}};
  };

  std::unordered_set<int> getAllStmtsThatUseVars() override {
    return {1, 2, 3};
  }
  std::unordered_set<std::string> getAllVarsUsedByStmts() override {
    return {"a", "b", "c"};
  }
  std::unordered_set<std::string> getAllProceduresThatUseVars() override {
    return {"main", "call"};
  }
  std::unordered_set<std::string> getAllVarsUsedByProcedures() override {
    return {"a", "b", "c", "d"};
  }

  std::unordered_set<int> getStmtsNextOf([[maybe_unused]] int stmtNo) override {
    return {2, 3};
  }

  std::unordered_set<int> getStmtsPreviousOf(
      [[maybe_unused]] int stmtNo) override {
    return {5, 8};
  }

  std::unordered_set<std::pair<int, int>, PairHash> getAllNextPairs() override {
    return {{1, 2}, {2, 3}};
  }

  std::unordered_set<int> getAllStmtsThatAreNextOfOtherStmts() override {
    return {2, 3, 4};
  }

  std::unordered_set<int> getAllStmtsThatArePreviousOfOtherStmts() override {
    return {1, 2, 3};
  }

  std::unordered_set<int> getAllStmtsThatCallProc(
      [[maybe_unused]] std::string& procName) override {
    return {1, 2};
  }

  std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllCallsProcPairs() override {
    return {{1, "first"}, {2, "first"}, {3, "second"}};
  }

  std::unordered_set<std::string> getAllProceduresCalledByStmts() override {
    return {"first", "second"};
  }

  std::string getVarPrintedByStmt([[maybe_unused]] int stmtNo) override {
    return "cat";
  }

  std::unordered_set<int> getAllStmtsThatPrintVar(
      [[maybe_unused]] std::string& var) override {
    return {1, 2};
  }

  std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllPrintVarPairs() override {
    return {{1, "cat"}, {2, "cat"}, {3, "dog"}};
  }

  std::unordered_set<std::string> getAllVarsPrintByStmts() override {
    return {"d", "a", "b"};
  }

  std::string getVarReadByStmt([[maybe_unused]] int stmtNo) override {
    return "cat";
  }

  std::unordered_set<int> getAllStmtsThatReadVar(
      [[maybe_unused]] std::string& var) override {
    return {1, 2};
  }

  std::unordered_set<std::pair<int, std::string>, PairHash> getAllReadVarPairs()
      override {
    return {{1, "cat"}, {2, "cat"}, {3, "dog"}};
  }

  std::unordered_set<std::string> getAllVarsReadByStmts() override {
    return {"c", "b"};
  }
};
// ai-gen end
