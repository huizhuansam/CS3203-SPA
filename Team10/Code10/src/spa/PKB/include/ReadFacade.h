#pragma once

#include <PKB.h>

#include <iostream>
#include <string>
#include <vector>

class ReadFacade {
 private:
  PKB& pkb = PKB::getPKB();
  std::unordered_map<int, std::unordered_set<int>> nextStarMemoize;
  std::unordered_map<int, std::unordered_set<int>> prevStarMemoize;
  std::unordered_map<int, std::unordered_set<int>> affectsMemoize;

 public:
  // Entity Manager

  /// @brief Returns all variables from PKB
  ///
  /// @return set containing all the variables in PKB
  virtual std::unordered_set<std::string> getAllVariables();

  /// @brief Returns all constants from PKB
  ///
  /// @return set containing all the constants in PKB
  virtual std::unordered_set<std::string> getAllConstants();

  /// @brief Returns all procedures from PKB
  ///
  /// @return set containing all the procedures in PKB
  virtual std::unordered_set<std::string> getAllProcedures();

  /// @brief Returns all statement numbers from PKB
  ///
  /// @return set containing all the statement numbers in PKB
  virtual std::unordered_set<int> getStatements();

  /// @brief Returns all assignment statement numbers from PKB
  ///
  /// @return set containing all the statement numbers of assignments in PKB
  virtual std::unordered_set<int> getAssigns();

  /// @brief Returns all read statement numbers from PKB
  ///
  /// @return set containing all the statement numbers of reads in PKB
  virtual std::unordered_set<int> getReads();

  /// @brief Returns all print statement numbers from PKB
  ///
  /// @return set containing all the statement numbers of prints in PKB
  virtual std::unordered_set<int> getPrints();

  /// @brief Returns all call statement numbers from PKB
  ///
  /// @return set containing all the statement numbers of calls in PKB
  virtual std::unordered_set<int> getCalls();

  /// @brief Returns all while statement numbers from PKB
  ///
  /// @return set containing all the statement numbers of whiles in PKB
  virtual std::unordered_set<int> getWhiles();

  /// @brief Returns all if statement numbers from PKB
  ///
  /// @return set containing all the statement numbers of ifs in PKB
  virtual std::unordered_set<int> getIfs();

  /// @brief Returns the proc called by the given stmt number
  /// @param stmtNo Call statement number
  ///
  /// @return procedure name that is called at the given statement number
  virtual std::string getProcCalledByStmt(int stmtNo);

  /// @brief Returns all call statement numbers that call the given procName
  /// @param procName Procedure name
  ///
  /// @return all call statement numbers that call the given procName
  virtual std::unordered_set<int> getAllStmtsThatCallProc(
      std::string& procName);

  /// @brief Returns all <stmtNo, procName> pairs of the Call entity
  ///
  /// @return all <stmtNo, procName> pairs of the Call entity
  virtual std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllCallsProcPairs();

  /// @brief Returns all procedures that are called by a call statement
  ///
  /// @return all procedures that are called by a call statement
  virtual std::unordered_set<std::string> getAllProceduresCalledByStmts();

  /// @brief Returns the var printed at the given stmt number
  /// @param stmtNo Print statement number
  ///
  /// @return var name that is printed at the given statement number
  virtual std::string getVarPrintedByStmt(int stmtNo);

  /// @brief Returns all print statements that print the given var
  /// @param var Variable that is being printed
  ///
  /// @return all print statements that print the given var
  virtual std::unordered_set<int> getAllStmtsThatPrintVar(std::string& var);

  /// @brief Returns all <stmtNo, var> pairs of the Print entity
  ///
  /// @return all <stmtNo, var> pairs of the Print entity
  virtual std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllPrintVarPairs();

  /// @brief Returns all variables that are printed by a Print statement
  ///
  /// @return all variables that are printed by a Print statement
  virtual std::unordered_set<std::string> getAllVarsPrintByStmts();

  /// @brief Returns the var read at the given stmt number
  /// @param stmtNo Read statement number
  ///
  /// @return var name that is read at the given statement number
  virtual std::string getVarReadByStmt(int stmtNo);

  /// @brief Returns all read statements that read the given var
  /// @param var Variable that is being read
  ///
  /// @return all read statements that read the given var
  virtual std::unordered_set<int> getAllStmtsThatReadVar(std::string& var);

  /// @brief Returns all <stmtNo, var> pairs of the Read entity
  ///
  /// @return all <stmtNo, var> pairs of the Read entity
  virtual std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllReadVarPairs();

  /// @brief Returns all variables that are read by a Read statement
  ///
  /// @return all variables that are read by a Read statement
  virtual std::unordered_set<std::string> getAllVarsReadByStmts();

  // Pattern Manager

  /// @brief Returns all (assignment stmtNo, variable) pairs in PKB
  ///
  /// @return all (assignment stmtNo, variable) pairs in PKB
  virtual std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllAssignExpPairs();

  /// @brief Returns all (assignment stmtNo, variable) pairs in PKB that match
  /// var and infixTokens partially
  ///
  /// @param var variable on LHS of assign expression
  /// @param infixTokens query string as an array in infix form
  /// @return all (assignment stmtNo, variable) pairs in PKB that match
  /// infixTokens
  virtual std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsPartialMatch(const std::string& var,
                                const std::vector<std::string>& infixTokens);

  /// @brief Returns all (assignment stmtNo, variable) pairs in PKB that match
  /// infixTokens partially
  ///
  /// @param infixTokens query string as an array in infix form
  /// @return all (assignment stmtNo, variable) pairs in PKB that match
  /// infixTokens
  virtual std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsSynonymPartialMatch(
      const std::vector<std::string>& infixTokens);

  /// @brief Returns all (assignment stmtNo, variable) pairs in PKB that match
  /// var and infixTokens exactly
  ///
  /// @param var variable on LHS of assign expression
  /// @param infixTokens query string as an array in infix form
  /// @return all (assignment stmtNo, variable) pairs in PKB that match
  /// infixTokens
  virtual std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsExactMatch(const std::string& var,
                              const std::vector<std::string>& infixTokens);

  /// @brief Returns all (assignment stmtNo, variable) pairs in PKB that match
  /// infixTokens exactly
  ///
  /// @param infixTokens query string as an array in infix form
  /// @return all (assignment stmtNo, variable) pairs in PKB that match
  /// infixTokens
  virtual std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAssignExpPairsSynonymExactMatch(
      const std::vector<std::string>& infixTokens);

  // while
  /// @brief Returns the control variable used by the given While stmt
  ///
  /// @param stmtNo given While stmtNo
  /// @return control variable used by the given While stmt
  virtual std::unordered_set<std::string> getControlVariableOfWhileStmt(
      int stmtNo);

  /// @brief Returns set of all while stmt no that use the given control
  /// variable
  ///
  /// @param var given control variable
  /// @return set of all while stmt no that use the given control variable
  virtual std::unordered_set<int> getWhileStmtsThatUseControlVariable(
      const std::string& var);

  /// @brief Returns all (while stmtNo, variable) pairs in PKB
  ///
  /// @return all (while stmtNo, variable) pairs in PKB
  virtual std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllWhileControlVariablePairs();

  /// @brief Returns all while statements that use control variables
  ///
  /// @return all while statements that use control variables
  virtual std::unordered_set<int> getAllWhileStmtsThatUseControlVariables();

  /// @brief Returns all control variables used in while statements
  ///
  /// @return all control variables used in while statements
  virtual std::unordered_set<std::string> getAllWhileControlVariables();

  // if
  /// @brief Returns the control variable used by the given If stmt
  ///
  /// @param stmtNo given If stmtNo
  /// @return control variable used by the given If stmt
  virtual std::unordered_set<std::string> getControlVariableOfIfStmt(
      int stmtNo);

  /// @brief Returns set of all if stmt no that use the given control
  /// variable
  ///
  /// @param var given control variable
  /// @return set of all if stmt no that use the given control variable
  virtual std::unordered_set<int> getIfStmtsThatUseControlVariable(
      const std::string& var);

  /// @brief Returns all (if stmtNo, variable) pairs in PKB
  ///
  /// @return all (if stmtNo, variable) pairs in PKB
  virtual std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllIfControlVariablePairs();

  /// @brief Returns all if statements that use control variables
  ///
  /// @return all if statements that use control variables
  virtual std::unordered_set<int> getAllIfStmtsThatUseControlVariables();

  /// @brief Returns all control variables used in if statements
  ///
  /// @return all control variables used in if statements
  virtual std::unordered_set<std::string> getAllIfControlVariables();

  // Relationship Manager
  // parent

  /// @brief Returns a vector of all direct children of input parent
  ///
  /// @param parentStmtNo Parent statement number
  /// @return Statement number of direct child
  virtual std::unordered_set<int> getChildren(int parentStmtNo);

  /// @brief Returns direct parent of input child
  ///
  /// @param childStmtNo Child statement number
  /// @return Statement number of direct parent
  virtual int getParent(int childStmtNo);

  /// @brief Returns list of transitive children of input parent
  ///
  /// @param parentStmtNo Parent statement number
  /// @return list containing all transitive children of parentStmtNo
  virtual std::unordered_set<int> getChildrenStar(int parentStmtNo);

  /// @brief Returns list of transitive parents of input child
  ///
  /// @param childStmtNo Child statement number
  /// @return list containing all transitive parents of childStmtNo
  virtual std::unordered_set<int> getParentStar(int childStmtNo);

  /// @brief Returns list of all parent-child pairs
  ///
  /// @return list containing all parent-child pairs
  virtual std::unordered_set<std::pair<int, int>, PairHash> getAllParentPairs();

  /// @brief Returns list of all transitive parent-child pairs
  ///
  /// @return list containing all parent-child pairs
  virtual std::unordered_set<std::pair<int, int>, PairHash>
  getAllParentStarPairs();

  /// @brief Returns list of all stmts that are parents
  ///
  /// @return list containing all stmts that are parents
  virtual std::unordered_set<int> getAllParents();

  /// @brief Returns list of all stmts that are children
  ///
  /// @return list containing all stmts that are children
  virtual std::unordered_set<int> getAllChildren();
  // follows
  /// @brief Returns statement that directly follows stmtNo
  ///
  /// @param stmtNo Statement number of query statement
  /// @return statement that directly follows stmtNo
  /// @details If 1 --> 2 --> 3 --> 4, getStmtThatFollowsAfter(1) returns 2
  virtual int getStmtThatFollowsAfter(int stmtNo);

  /// @brief Returns statement that directly followed by stmtNo
  ///
  /// @param stmtNo Statement number of query statement
  /// @return statement that directly followed by stmtNo
  /// @details If 1 --> 2 --> 3 --> 4, getStmtThatFollowsBefore(4) returns 3
  virtual int getStmtThatFollowsBefore(int stmtNo);

  /// @brief Returns all statements that transitively follows stmtNo
  ///
  /// @param stmtNo Statement number of query statement
  /// @return statements that transitively follows stmtNo
  /// @details If 1 --> 2 --> 3 --> 4, getAllStmtsThatFollowAfter(1) returns
  /// {2, 3, 4}
  virtual std::unordered_set<int> getAllStmtsThatFollowAfter(int stmtNo);

  /// @brief Returns statements that transitively followed by stmtNo
  ///
  /// @param stmtNo Statement number of query statement
  /// @return statements that transitively followed by stmtNo
  /// @details If 1 --> 2 --> 3 --> 4, getAllStmtsThatFollowBefore(3) returns
  /// {1, 2}
  virtual std::unordered_set<int> getAllStmtsThatFollowBefore(int afterStmtNo);

  /// @brief Returns list of all Follow pairs
  ///
  /// @return list containing all Follow pairs
  /// @details If 1 --> 2 --> 3 --> 4, getAllFollowPairs returns {(1, 2), (2,
  /// 3), (3, 4)}
  virtual std::unordered_set<std::pair<int, int>, PairHash> getAllFollowPairs();

  /// @brief Returns list of all Follow pairs
  ///
  /// @return list containing all Follow pairs
  /// @details If 1 --> 2 --> 3 --> 4, getAllFollowStarPairs returns {(1, 2),
  /// (1, 3), (1, 4), (2, 3), (2, 4), (3, 4)}
  virtual std::unordered_set<std::pair<int, int>, PairHash>
  getAllFollowStarPairs();

  /// @brief Returns list of all stmts that follow another statement
  ///
  /// @return list containing all stmts that follow another statement
  /// @details If 1 --> 2 --> 3 --> 4 and 6 --> 7, getAllFollowPairs returns {2,
  /// 3, 4, 7}
  virtual std::unordered_set<int> getAllStmtsThatFollowAfterOtherStmts();

  /// @brief Returns list of all stmts that are followed by another statement
  ///
  /// @return list containing all stmts that are followed by another statement
  /// @details If 1 --> 2 --> 3 --> 4 and 6 --> 7,
  /// getAllStmtsThatFollowAfterOtherStmts returns {1, 2, 3, 6}
  virtual std::unordered_set<int> getAllStmtsThatFollowBeforeOtherStmts();

  // calls
  /// @brief Returns a set of all procedures that call targetProcName
  ///
  /// @param targetProcName Name of procedure being called
  /// @return Set of all procedures that call targetProcName
  virtual std::unordered_set<std::string> getProcsThatCalls(
      std::string& targetProcName);

  /// @brief Returns a set of all procedures that sourceProcName calls
  ///
  /// @param sourceProcName Name of procedure calling other procedures
  /// @return Set of all procedures that sourceProcName calls
  virtual std::unordered_set<std::string> getProcsThatIsCalledBy(
      std::string& sourceProcName);

  /// @brief Returns set of all Call pairs
  ///
  /// @return set containing all Call pairs
  /// @details If "First" --> "Second", "Second" --> "Third", getAllCallPairs
  /// returns {("First", "Second"), ("Second", "Third")}
  virtual std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllCallPairs();

  /// @brief Returns set of all procedures that call other procedures
  ///
  /// @return list containing all stmts that follow another statement
  /// @details If "First" --> "Second", "Third" --> "Fourth", getAllFollowPairs
  /// returns {"First", "Third"}
  virtual std::unordered_set<std::string> getAllProcsThatCallOtherProcs();

  /// @brief Returns set of all procedures that call other procedures
  ///
  /// @return list containing all stmts that follow another statement
  /// @details If "First" --> "Second", "Third" --> "Fourth", getAllFollowPairs
  /// returns {"Second", "Fourth"}
  virtual std::unordered_set<std::string>
  getAllProcsThatGetCalledByOtherProcs();

  // calls*
  /// @brief Returns a set of all procedures that call targetProcName
  /// transitively
  ///
  /// @param targetProcName Name of procedure being called transitively
  /// @return Set of all procedures that call targetProcName transitively
  virtual std::unordered_set<std::string> getProcsThatCallsStar(
      std::string& targetProcName);

  /// @brief Returns a set of all procedures that sourceProcName calls
  /// transitively
  ///
  /// @param sourceProcName Name of procedure calling other procedures
  /// transitively
  /// @return Set of all procedures that sourceProcName calls transitively
  virtual std::unordered_set<std::string> getProcsThatIsCalledByStar(
      std::string& sourceProcName);

  /// @brief Returns set of all CallStar pairs
  ///
  /// @return set containing all CallStar pairs
  /// @details If "First" --> "Second", "Second" --> "Third", getAllCallPairs
  /// returns {("First", "Second"), ("First", "Third"), ("Second", "Third")}
  virtual std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllCallStarPairs();

  // modifies
  /// @brief Returns all variables that stmtNo modifies
  ///
  /// @param stmtNo Statement number of query statement
  /// @return list containing all variables that stmtNo modifies
  /// @details getVarsModifiedByStmt(1) returns {"a", "b", "c"}
  virtual std::unordered_set<std::string> getVarsModifiedByStmt(int stmtNo);

  /// @brief Returns all statement numbers of statements that modifies var
  ///
  /// @param var Variable that is being queried
  /// @return list containing all statement numbers of statements that modifies
  /// var
  /// @details getStmtsThatModifyVar("a") returns {1, 3, 5}
  virtual std::unordered_set<int> getStmtsThatModifyVar(std::string var);

  /// @brief Returns list of all Modifies pairs for statements
  ///
  /// @return list containing all Modifies pairs
  /// @details getAllVarModifiedByStmtPairs() --> {(1, "a"), (1, "b"), (1, "c"),
  /// (3, "b"), (4, "c")}
  virtual std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllVarModifiedByStmtPairs();

  /// @brief Returns all variables that procName modifies
  ///
  /// @param procName Name of procedure that is queried
  /// @return list containing all variables that procName modifies
  /// @details getVarsModifiedByProcedure("main") returns {"a", "b", "c"}
  virtual std::unordered_set<std::string> getVarsModifiedByProcedure(
      std::string& procName);

  /// @brief Returns all procedures that modifies var
  ///
  /// @param var Variable that is being queried
  /// @return list containing all procedures that modifies var
  /// @details getProceduresThatModifyVar("a") returns {"main", "fun1",
  /// "fun2"}
  virtual std::unordered_set<std::string> getProceduresThatModifyVar(
      std::string& var);

  /// @brief Returns list of all Modifies pairs for procedures
  ///
  /// @return list containing all Modifies pairs
  /// @details getAllVarModifiedByProcedurePairs() returns {("main", "a"),
  /// ("main", "b"), ("main", "c"), ("fun1", "b), ("fun2", "c")}
  virtual std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllVarModifiedByProcedurePairs();

  /// @brief Returns list of all stmts that modify var
  ///
  /// @return list containing all stmts that modify var
  /// @details if 1 modifies "b", and 2 modifies "c",
  /// getAllStmtsThatModifyVars() returns {1, 2}
  virtual std::unordered_set<int> getAllStmtsThatModifyVars();

  /// @brief Returns list of all var that are modified in stmt
  ///
  /// @return list containing all var that are modified in stmt
  /// @details if 1 modifies "b", and 2 modifies "c",
  /// getAllVarsModifiedByStmts() returns {"b", "c"}
  virtual std::unordered_set<std::string> getAllVarsModifiedByStmts();

  /// @brief Returns list of all procedures that modify var
  ///
  /// @return list containing all procedures that modify var
  /// @details if "main" modifies "b", and "call" modifies "c",
  /// getAllProceduresThatModifyVars() returns {"main", "call"}
  virtual std::unordered_set<std::string> getAllProceduresThatModifyVars();

  /// @brief Returns list of all var that are modified by procedures
  ///
  /// @return list containing all var that are modified by procedures
  /// @details if "main" modifies "b", and "call" modifies "c",
  /// getAllVarsModifiedByProcedures() returns {"b", "c"}
  virtual std::unordered_set<std::string> getAllVarsModifiedByProcedures();

  // uses
  /// @brief Returns all variables that stmtNo uses
  ///
  /// @param stmtNo Statement number of query statement
  /// @return list containing all variables that stmtNo uses
  /// @details getVarsUsedByStmt(1) returns {"a", "b", "c"}
  virtual std::unordered_set<std::string> getVarsUsedByStmt(int stmtNo);

  /// @brief Returns all statement numbers of statements that uses var
  ///
  /// @param var Variable that is being queried
  /// @return list containing all statement numbers of statements that uses
  /// var
  /// @details getStmtsThatUseVar("a") returns {1, 3, 5}
  virtual std::unordered_set<int> getStmtsThatUseVar(std::string var);

  /// @brief Returns list of all Uses pairs for statements
  ///
  /// @return list containing all Uses pairs
  /// @details getAllVarsUsedByStmtPairs() --> {(1, "a"), (1, "b"), (1, "c"),
  /// (3, "b"), (4, "c")}
  virtual std::unordered_set<std::pair<int, std::string>, PairHash>
  getAllVarUsedByStmtPairs();

  /// @brief Returns all variables that procName uses
  ///
  /// @param procName Name of procName that is queried
  /// @return list containing all variables that procName uses
  /// @details getVarsUsedByProcedure("main") returns {"a", "b", "c"}
  virtual std::unordered_set<std::string> getVarsUsedByProcedure(
      std::string procName);

  /// @brief Returns all procedures that uses var
  ///
  /// @param var Variable that is being queried
  /// @return list containing all procedures that uses var
  /// @details getProceduresThatUseVar("a") returns {"main", "fun1", "fun2"}
  virtual std::unordered_set<std::string> getProceduresThatUseVar(
      std::string var);

  /// @brief Returns list of all Uses pairs for procedures
  ///
  /// @return list containing all Uses pairs
  /// @details getAllVarUsedByProcedurePairs() returns {("main", "a"), ("main",
  /// "b"), ("main", "c"), ("fun1", "b), ("fun2", "c")}
  virtual std::unordered_set<std::pair<std::string, std::string>, PairHash>
  getAllVarUsedByProcedurePairs();

  /// @brief Returns list of all stmts that use var
  ///
  /// @return list containing all stmts that use var
  /// @details if 1 uses "b", and 2 uses "c",
  /// getAllStmtsThatUseVars() returns {1, 2}
  virtual std::unordered_set<int> getAllStmtsThatUseVars();

  /// @brief Returns list of all var that are used in a stmt
  ///
  /// @return list containing all var that are used in a stmt
  /// @details if 1 uses "b", and 2 uses "c",
  /// getAllVarsUsedByStmts() returns {"b", "c"}
  virtual std::unordered_set<std::string> getAllVarsUsedByStmts();

  /// @brief Returns list of all procedures that use var
  ///
  /// @return list containing all procedures that use var
  /// @details if "main" uses "b", and "call" uses "c",
  /// getAllProceduresThatUseVars() returns {"main", "call"}
  virtual std::unordered_set<std::string> getAllProceduresThatUseVars();

  /// @brief Returns list of all var that are used in a procedure
  ///
  /// @return list containing all var that are used in a procedure
  /// @details if "main" uses "b", and "call" uses "c",
  /// getAllVarsUsedByProcedures() returns {"b", "c"}
  virtual std::unordered_set<std::string> getAllVarsUsedByProcedures();

  // next
  /// @brief Returns statement that runs after stmtNo
  ///
  /// @param stmtNo Statement number of query statement
  /// @return statement that runs after stmtNo
  /// @details If 1 --> 2 --> 3 --> 4, getStmtsNextOf(1) returns 2
  virtual std::unordered_set<int> getStmtsNextOf(int stmtNo);

  /// @brief Returns all statements that run after stmtNo.
  /// @param stmtNo Statement number of query statement.
  /// @return All statements that run after stmtNo.
  virtual std::unordered_set<int> getStmtsNextStarOf(int stmtNo);

  /// @brief Returns statement that runs before stmtNo
  ///
  /// @param stmtNo Statement number of query statement
  /// @return statement that runs before stmtNo
  /// @details If 1 --> 2 --> 3 --> 4, getStmtsPreviousOf(2) returns 1
  virtual std::unordered_set<int> getStmtsPreviousOf(int stmtNo);

  /// @brief Returns all statements that run before stmtNo.
  /// @param stmtNo Statement number of query statement.
  /// @return All statements that run before stmtNo.
  virtual std::unordered_set<int> getStmtsPreviousStarOf(int stmtNo);

  /// Runs DFS to get all statements that run before or after stmtNo.
  /// @param stmtNo Statement number of query statement.
  /// @param isNext Whether to get statements that run after or run before.
  /// @return All statements that run before or after stmtNo.
  std::unordered_set<int> getStmtByDFS(int stmtNo, bool isNext = true);

  /// @brief Returns list of all Next pairs
  ///
  /// @return list containing all Next pairs
  /// @details If 1 --> 2 --> 3 --> 4, getAllNextPairs returns {(1, 2), (2,
  /// 3), (3, 4)}
  virtual std::unordered_set<std::pair<int, int>, PairHash> getAllNextPairs();

  /// @brief Returns list of all stmts that is next of another statement
  ///
  /// @return list containing all stmts that is next of another statement
  /// @details If 1 --> 2 --> 3 --> 4 and 6 --> 7,
  /// getAllStmtsThatAreNextOfOtherStmts returns {2, 3, 4, 7}
  virtual std::unordered_set<int> getAllStmtsThatAreNextOfOtherStmts();

  /// @brief Returns list of all stmts that is previous of another statement
  ///
  /// @return list containing all stmts that is previous of another statement
  /// @details If 1 --> 2 --> 3 --> 4 and 6 --> 7,
  /// getAllStmtsThatArePreviousOfOtherStmts returns {1, 2, 3, 6}
  virtual std::unordered_set<int> getAllStmtsThatArePreviousOfOtherStmts();

  // affects
  /// @brief Returns statements that is affected by stmtNo
  ///
  /// @param stmtNo Statement number of query statement
  /// @return statement that is affected by stmtNo
  /// @details If 1 --> 2 --> 3 --> 4, getStmtsNextOf(1) returns {2, 3, 4}
  virtual std::unordered_set<int> getStmtsAffectedBy(int stmtNo);

  virtual ~ReadFacade() = default;
};
