#include "ReadFacade.h"

#include <iostream>
#include <string>
#include <vector>

// Entity Manager methods
std::unordered_set<std::string> ReadFacade::getAllVariables() {
  return pkb.getAllVariables();
};
std::unordered_set<std::string> ReadFacade::getAllConstants() {
  return pkb.getAllConstants();
};
std::unordered_set<std::string> ReadFacade::getAllProcedures() {
  return pkb.getAllProcedures();
};

std::unordered_set<int> ReadFacade::getStatements() {
  return pkb.getStatements();
};

std::unordered_set<int> ReadFacade::getAssigns() { return pkb.getAssigns(); };

std::unordered_set<int> ReadFacade::getReads() { return pkb.getReads(); };

std::unordered_set<int> ReadFacade::getPrints() { return pkb.getPrints(); };

std::unordered_set<int> ReadFacade::getCalls() { return pkb.getCalls(); };

std::unordered_set<int> ReadFacade::getWhiles() { return pkb.getWhiles(); };

std::unordered_set<int> ReadFacade::getIfs() { return pkb.getIfs(); };

std::string ReadFacade::getProcCalledByStmt(int callStmt) {
  return pkb.getProcCalledByStmt(callStmt);
}

std::unordered_set<int> ReadFacade::getAllStmtsThatCallProc(
    std::string& procName) {
  return pkb.getAllStmtsThatCallProc(procName);
}

std::unordered_set<std::pair<int, std::string>, PairHash>
ReadFacade::getAllCallsProcPairs() {
  return pkb.getAllCallsProcPairs();
}

std::unordered_set<std::string> ReadFacade::getAllProceduresCalledByStmts() {
  return pkb.getAllProceduresCalledByStmts();
}

std::string ReadFacade::getVarPrintedByStmt(int printStmt) {
  return pkb.getVarPrintedByStmt(printStmt);
}

std::unordered_set<int> ReadFacade::getAllStmtsThatPrintVar(std::string& var) {
  return pkb.getAllStmtsThatPrintVar(var);
}

std::unordered_set<std::pair<int, std::string>, PairHash>
ReadFacade::getAllPrintVarPairs() {
  return pkb.getAllPrintVarPairs();
}

std::unordered_set<std::string> ReadFacade::getAllVarsPrintByStmts() {
  return pkb.getAllVarsPrintByStmts();
}

std::string ReadFacade::getVarReadByStmt(int readStmt) {
  return pkb.getVarReadByStmt(readStmt);
}

std::unordered_set<int> ReadFacade::getAllStmtsThatReadVar(std::string& var) {
  return pkb.getAllStmtsThatReadVar(var);
}
std::unordered_set<std::pair<int, std::string>, PairHash>
ReadFacade::getAllReadVarPairs() {
  return pkb.getAllReadVarPairs();
}
std::unordered_set<std::string> ReadFacade::getAllVarsReadByStmts() {
  return pkb.getAllVarsReadByStmts();
}

// Pattern Manager Methods
std::unordered_set<std::pair<std::string, std::string>, PairHash>
ReadFacade::getAllAssignExpPairs() {
  return pkb.getAllAssignExpPairs();
};

std::unordered_set<std::pair<std::string, std::string>, PairHash>
ReadFacade::getAssignExpPairsPartialMatch(
    const std::string& var, const std::vector<std::string>& infixTokens) {
  return pkb.getAssignExpPairsPartialMatch(var, infixTokens);
};

std::unordered_set<std::pair<std::string, std::string>, PairHash>
ReadFacade::getAssignExpPairsSynonymPartialMatch(
    const std::vector<std::string>& infixTokens) {
  return pkb.getAssignExpPairsSynonymPartialMatch(infixTokens);
};

std::unordered_set<std::pair<std::string, std::string>, PairHash>
ReadFacade::getAssignExpPairsExactMatch(
    const std::string& var, const std::vector<std::string>& infixTokens) {
  return pkb.getAssignExpPairsExactMatch(var, infixTokens);
};

std::unordered_set<std::pair<std::string, std::string>, PairHash>
ReadFacade::getAssignExpPairsSynonymExactMatch(
    const std::vector<std::string>& infixTokens) {
  return pkb.getAssignExpPairsSynonymExactMatch(infixTokens);
};

std::unordered_set<std::string> ReadFacade::getControlVariableOfWhileStmt(
    int stmtNo) {
  return pkb.getControlVariableOfWhileStmt(stmtNo);
}

std::unordered_set<int> ReadFacade::getWhileStmtsThatUseControlVariable(
    const std::string& var) {
  return pkb.getWhileStmtsThatUseControlVariable(var);
}

std::unordered_set<std::pair<int, std::string>, PairHash>
ReadFacade::getAllWhileControlVariablePairs() {
  return pkb.getAllWhileControlVariablePairs();
}

std::unordered_set<int> ReadFacade::getAllWhileStmtsThatUseControlVariables() {
  return pkb.getAllWhileStmtsThatUseControlVariables();
}

std::unordered_set<std::string> ReadFacade::getAllWhileControlVariables() {
  return pkb.getAllWhileControlVariables();
}

std::unordered_set<std::string> ReadFacade::getControlVariableOfIfStmt(
    int stmtNo) {
  return pkb.getControlVariableOfIfStmt(stmtNo);
}

std::unordered_set<int> ReadFacade::getIfStmtsThatUseControlVariable(
    const std::string& var) {
  return pkb.getIfStmtsThatUseControlVariable(var);
}

std::unordered_set<std::pair<int, std::string>, PairHash>
ReadFacade::getAllIfControlVariablePairs() {
  return pkb.getAllIfControlVariablePairs();
}

std::unordered_set<int> ReadFacade::getAllIfStmtsThatUseControlVariables() {
  return pkb.getAllIfStmtsThatUseControlVariables();
}

std::unordered_set<std::string> ReadFacade::getAllIfControlVariables() {
  return pkb.getAllIfControlVariables();
}

// Relationship Manager Methods
// parent
std::unordered_set<int> ReadFacade::getChildren(int parent) {
  return pkb.getChildren(parent);
}
int ReadFacade::getParent(int child) { return pkb.getParent(child); }
std::unordered_set<int> ReadFacade::getChildrenStar(int parent) {
  return pkb.getChildrenStar(parent);
}
std::unordered_set<int> ReadFacade::getParentStar(int child) {
  return pkb.getParentsStar(child);
}
std::unordered_set<std::pair<int, int>, PairHash>
ReadFacade::getAllParentPairs() {
  return pkb.getAllParentPairs();
}
std::unordered_set<std::pair<int, int>, PairHash>
ReadFacade::getAllParentStarPairs() {
  return pkb.getAllParentStarPairs();
}
std::unordered_set<int> ReadFacade::getAllParents() {
  return pkb.getAllParents();
}
std::unordered_set<int> ReadFacade::getAllChildren() {
  return pkb.getAllChildren();
}

// follows
int ReadFacade::getStmtThatFollowsAfter(int stmtNo) {
  return pkb.getStmtThatFollowsAfter(stmtNo);
}
int ReadFacade::getStmtThatFollowsBefore(int stmtNo) {
  return pkb.getStmtThatFollowsBefore(stmtNo);
}
std::unordered_set<int> ReadFacade::getAllStmtsThatFollowAfter(int stmtNo) {
  return pkb.getAllStmtsThatFollowAfter(stmtNo);
}
std::unordered_set<int> ReadFacade::getAllStmtsThatFollowBefore(int stmtNo) {
  return pkb.getAllStmtsThatFollowBefore(stmtNo);
}
std::unordered_set<std::pair<int, int>, PairHash>
ReadFacade::getAllFollowPairs() {
  return pkb.getAllFollowPairs();
}
std::unordered_set<std::pair<int, int>, PairHash>
ReadFacade::getAllFollowStarPairs() {
  return pkb.getAllFollowStarPairs();
}
std::unordered_set<int> ReadFacade::getAllStmtsThatFollowAfterOtherStmts() {
  return pkb.getAllStmtsThatFollowAfterOtherStmts();
}
std::unordered_set<int> ReadFacade::getAllStmtsThatFollowBeforeOtherStmts() {
  return pkb.getAllStmtsThatFollowBeforeOtherStmts();
}

// calls
std::unordered_set<std::string> ReadFacade::getProcsThatIsCalledBy(
    std::string& sourceProcName) {
  return pkb.getProcsThatIsCalledBy(sourceProcName);
}

std::unordered_set<std::string> ReadFacade::getProcsThatCalls(
    std::string& targetProcName) {
  return pkb.getProcsThatCalls(targetProcName);
}

std::unordered_set<std::pair<std::string, std::string>, PairHash>
ReadFacade::getAllCallPairs() {
  return pkb.getAllCallPairs();
}

std::unordered_set<std::string> ReadFacade::getAllProcsThatCallOtherProcs() {
  return pkb.getAllProcsThatCallOtherProcs();
}

std::unordered_set<std::string>
ReadFacade::getAllProcsThatGetCalledByOtherProcs() {
  return pkb.getAllProcsThatGetCalledByOtherProcs();
}

// calls*
std::unordered_set<std::string> ReadFacade::getProcsThatIsCalledByStar(
    std::string& sourceProcName) {
  return pkb.getProcsThatIsCalledByStar(sourceProcName);
}

std::unordered_set<std::string> ReadFacade::getProcsThatCallsStar(
    std::string& targetProcName) {
  return pkb.getProcsThatCallsStar(targetProcName);
}

std::unordered_set<std::pair<std::string, std::string>, PairHash>
ReadFacade::getAllCallStarPairs() {
  return pkb.getAllCallStarPairs();
}

// modifies
std::unordered_set<std::string> ReadFacade::getVarsModifiedByStmt(int stmtNo) {
  return pkb.getVarsModifiedByStmt(stmtNo);
}
std::unordered_set<int> ReadFacade::getStmtsThatModifyVar(std::string var) {
  return pkb.getStmtsThatModifyVar(var);
}
std::unordered_set<std::pair<int, std::string>, PairHash>
ReadFacade::getAllVarModifiedByStmtPairs() {
  return pkb.getAllVarModifiedByStmtPairs();
}
std::unordered_set<int> ReadFacade::getAllStmtsThatModifyVars() {
  return pkb.getAllStmtsThatModifyVars();
}
std::unordered_set<std::string> ReadFacade::getAllVarsModifiedByStmts() {
  return pkb.getAllVarsModifiedByStmts();
}
std::unordered_set<std::string> ReadFacade::getVarsModifiedByProcedure(
    std::string& procName) {
  return pkb.getVarsModifiedByProcedure(procName);
}
std::unordered_set<std::string> ReadFacade::getProceduresThatModifyVar(
    std::string& var) {
  return pkb.getProceduresThatModifyVar(var);
}
std::unordered_set<std::pair<std::string, std::string>, PairHash>
ReadFacade::getAllVarModifiedByProcedurePairs() {
  return pkb.getAllVarModifiedByProcedurePairs();
}
std::unordered_set<std::string> ReadFacade::getAllProceduresThatModifyVars() {
  return pkb.getAllProceduresThatModifyVars();
}
std::unordered_set<std::string> ReadFacade::getAllVarsModifiedByProcedures() {
  return pkb.getAllVarsModifiedByProcedures();
}
// uses
std::unordered_set<std::string> ReadFacade::getVarsUsedByStmt(int stmtNo) {
  return pkb.getVarsUsedByStmt(stmtNo);
}
std::unordered_set<int> ReadFacade::getStmtsThatUseVar(std::string var) {
  return pkb.getStmtsThatUseVar(var);
}
std::unordered_set<std::pair<int, std::string>, PairHash>
ReadFacade::getAllVarUsedByStmtPairs() {
  return pkb.getAllVarUsedByStmtPairs();
}
std::unordered_set<int> ReadFacade::getAllStmtsThatUseVars() {
  return pkb.getAllStmtsThatUseVars();
}
std::unordered_set<std::string> ReadFacade::getAllVarsUsedByStmts() {
  return pkb.getAllVarsUsedByStmts();
}
std::unordered_set<std::string> ReadFacade::getVarsUsedByProcedure(
    std::string procName) {
  return pkb.getVarsUsedByProcedure(procName);
}
std::unordered_set<std::string> ReadFacade::getProceduresThatUseVar(
    std::string var) {
  return pkb.getProceduresThatUseVar(var);
}
std::unordered_set<std::pair<std::string, std::string>, PairHash>
ReadFacade::getAllVarUsedByProcedurePairs() {
  return pkb.getAllVarUsedByProcedurePairs();
}
std::unordered_set<std::string> ReadFacade::getAllProceduresThatUseVars() {
  return pkb.getAllProceduresThatUseVars();
}
std::unordered_set<std::string> ReadFacade::getAllVarsUsedByProcedures() {
  return pkb.getAllVarsUsedByProcedures();
}

// next
std::unordered_set<int> ReadFacade::getStmtsNextOf(int stmtNo) {
  return pkb.getStmtsNextOf(stmtNo);
}
std::unordered_set<int> ReadFacade::getStmtsNextStarOf(int stmtNo) {
  std::unordered_set<int> nexts;
  if (nextStarMemoize.find(stmtNo) != nextStarMemoize.end()) {
    nexts = nextStarMemoize.at(stmtNo);
  } else {
    nexts = getStmtByDFS(stmtNo);
    nextStarMemoize[stmtNo] = nexts;
  }

  return nexts;
}
std::unordered_set<int> ReadFacade::getStmtsPreviousOf(int stmtNo) {
  return pkb.getStmtsPreviousOf(stmtNo);
}
std::unordered_set<int> ReadFacade::getStmtsPreviousStarOf(int stmtNo) {
  std::unordered_set<int> prevs;
  if (prevStarMemoize.find(stmtNo) != prevStarMemoize.end()) {
    prevs = prevStarMemoize.at(stmtNo);
  } else {
    prevs = getStmtByDFS(stmtNo, false);
    prevStarMemoize[stmtNo] = prevs;
  }

  return prevs;
}
std::unordered_set<int> ReadFacade::getStmtByDFS(int stmtNo, bool isNext) {
  std::unordered_set<int> visited;
  std::stack<int> stack;
  stack.push(stmtNo);

  bool isFirstAddingStartStmt = true;
  while (!stack.empty()) {
    int currentStmt = stack.top();
    stack.pop();

    if (visited.find(currentStmt) == visited.end()) {
      // add to visited if it is not the first time adding start stmt
      if (!isFirstAddingStartStmt) {
        visited.insert(currentStmt);
      }

      // do not add to visited if it is the first time adding start stmt
      if (isFirstAddingStartStmt && currentStmt == stmtNo) {
        isFirstAddingStartStmt = false;
      }

      // Get neighbors of current statement using readFacade.getStmtsNextOf
      std::unordered_set<int> neighbours =
          isNext ? getStmtsNextOf(currentStmt)
                 : getStmtsPreviousOf(currentStmt);

      // Add unvisited neighbors to the stack
      for (int neighbour : neighbours) {
        if (visited.find(neighbour) == visited.end()) {
          stack.push(neighbour);
        }
      }
    }
  }

  return visited;
}

std::unordered_set<std::pair<int, int>, PairHash>
ReadFacade::getAllNextPairs() {
  return pkb.getAllNextPairs();
}

std::unordered_set<int> ReadFacade::getAllStmtsThatAreNextOfOtherStmts() {
  return pkb.getAllStmtsThatAreNextOfOtherStmts();
}

std::unordered_set<int> ReadFacade::getAllStmtsThatArePreviousOfOtherStmts() {
  return pkb.getAllStmtsThatArePreviousOfOtherStmts();
}

std::unordered_set<int> ReadFacade::getStmtsAffectedBy(int stmtNo) {
  std::unordered_set<int> stmtsAffected;
  if (affectsMemoize.find(stmtNo) != affectsMemoize.end()) {
    stmtsAffected = affectsMemoize.at(stmtNo);
    return stmtsAffected;
  }

  // container statements for checking later
  std::unordered_set<int> allAssignStmts = pkb.getAssigns();
  if (allAssignStmts.find(stmtNo) == allAssignStmts.end()) {
    return {};
  }

  std::unordered_set<int> allWhileStmts = pkb.getWhiles();
  std::unordered_set<int> allIfStmts = pkb.getIfs();

  std::stack<int> stack;
  std::unordered_set<int> visited;
  std::string targetVar = *(pkb.getVarsModifiedByStmt(stmtNo).begin());

  // initialize stack with the next statements of the given statement
  std::unordered_set<int> nextStmts = pkb.getStmtsNextOf(stmtNo);
  for (int nextStmt : nextStmts) {
    stack.push(nextStmt);
  }

  while (!stack.empty()) {
    int current = stack.top();
    stack.pop();

    bool isVisited = visited.find(current) != visited.end();
    if (isVisited) {
      continue;
    }

    // check if the current statement is an assignment statement
    // and uses the target variable
    bool isCurrentAssignStmt =
        allAssignStmts.find(current) != allAssignStmts.end();
    if (isCurrentAssignStmt) {
      std::unordered_set<std::string> varsUsed = pkb.getVarsUsedByStmt(current);
      if (varsUsed.find(targetVar) != varsUsed.end()) {
        stmtsAffected.insert(current);
      }
    }

    // check if the current statement is a container statement
    // and modifies the target variable
    bool isNotContainerStmt =
        allWhileStmts.find(current) == allWhileStmts.end() &&
        allIfStmts.find(current) == allIfStmts.end();
    if (isNotContainerStmt) {
      std::unordered_set<std::string> varsModified =
          pkb.getVarsModifiedByStmt(current);
      if (varsModified.find(targetVar) != varsModified.end()) {
        continue;
      }
    }

    visited.insert(current);

    nextStmts = pkb.getStmtsNextOf(current);
    for (int nextStmt : nextStmts) {
      if (visited.find(nextStmt) == visited.end()) {
        stack.push(nextStmt);
      }
    }
  }

  affectsMemoize[stmtNo] = stmtsAffected;
  return stmtsAffected;
}