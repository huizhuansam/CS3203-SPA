#pragma once

#include <PKB.h>

#include <iostream>
#include <string>
#include <vector>

class WriteFacade {
 private:
  PKB& pkb = PKB::getPKB();

 public:
  /// @brief Clears the all data in PKB instance
  ///
  /// @return void
  virtual void clearPKB();

  // Entity Manager

  /// @brief Stores variable in the PKB
  ///
  /// @param var The variable to be stored
  /// @return void
  virtual void addVariable(const std::string& var);

  /// @brief Stores constant in the PKB
  ///
  /// @param constant The constant to be stored
  /// @return void
  virtual void addConstant(const std::string& constant);

  /// @brief Stores procedure in the PKB
  ///
  /// @param proc The procedure to be stored
  /// @return void
  virtual void addProcedure(const std::string& proc);

  /// @brief Stores statement in the PKB
  ///
  /// @param var The statement to be stored
  /// @return void
  /// @details When adding statement, just add the specific StatementType once.
  /// You don't have to do addStatement(StamentType::Statement, 1)  because we
  /// do it for you automatically when you add (StatementType:ASSIGN, 1).
  virtual void addStatement(StatementType type, int stmtNo);

  /// @brief Stores a stmt number and procName pair, where at the given stmt
  /// number, the procName is called
  ///
  /// @param stmtNo stmtNo
  /// @param procName The procedure called at the given stmtNo
  /// @return void
  virtual void insertStmtCallsProc(int stmtNo, const std::string& procName);

  /// @brief Stores a stmt number and var pair, where at the given stmt number,
  /// the var is printed
  ///
  /// @param stmtNo stmtNo
  /// @param var The var printed at the given stmtNo
  /// @return void
  virtual void insertStmtPrintsVar(int stmtNo, const std::string& var);

  /// @brief Stores a stmt number and var pair, where at the given stmt number,
  /// the var is read
  ///
  /// @param stmtNo stmtNo
  /// @param var The var read at the given stmtNo
  /// @return void
  virtual void insertStmtReadsVar(int stmtNo, const std::string& var);

  // Pattern Manager

  /// @brief Stores assignment expression pattern in the PKB
  ///
  /// @param stmtNo Statement number of assignment
  /// @param var Variable on the LHS of assignment
  /// @param exp Expression on the RHS of assignment
  /// @return void
  virtual void addAssignExpPattern(int stmtNo, const std::string& var,
                                   const std::vector<std::string>& exp);

  /// @brief Stores assignment expression pattern in the PKB
  ///
  /// @param stmtNo Statement number of While statement
  /// @param var Control Variable of While statement
  /// @return void
  virtual void addWhileControlVariable(int stmtNo, const std::string& var);

  /// @brief Stores assignment expression pattern in the PKB
  ///
  /// @param stmtNo Statement number of If statement
  /// @param var Control Variable of If statementt
  /// @return void
  virtual void addIfControlVariable(int stmtNo, const std::string& var);

  // Relationship Manager
  // parent

  /// @brief Stores the direct Parent-Child relationship in PKB
  ///
  /// @param parentStmtNo Statement number of direct parent
  /// @param childStmtNo Statement number of direct child
  /// @return void
  virtual void insertDirectParentChildRelationship(int parentStmtNo,
                                                   int childStmtNo);

  /// @brief Stores the transitive Parent-Child relationship in PKB
  ///
  /// @param parentStmtNo Statement number of indirect parent
  /// @param childStmtNo Statement number of indirect child
  /// @return void
  virtual void insertParentStarRelationship(int parentStmtNo, int childStmtNo);

  // follows
  /// @brief Stores the direct Follows relationship in PKB
  ///
  /// @param beforeStmtNo Statement number of the before Statement in Follows
  /// Relationship
  /// @param afterStmtNo Statement number of the after Statement in Follows
  /// Relationship
  /// @return void
  /// @ details For example, 1 --> 2. 1 is beforeStmtNo. 2 is afterStmtNo
  virtual void insertDirectFollowsRelationship(int beforeStmtNo,
                                               int afterStmtNo);

  /// @brief Stores the transitive Follows relationship in PKB
  ///
  /// @param beforeStmtNo Statement number of the before Statement in transitive
  /// Follows Relationship
  /// @param afterStmtNo Statement number of the after Statement in transitive
  /// Follows Relationship
  /// @return void
  /// @ details For example, 1 --> 2. 1 is beforeStmtNo. 2 is afterStmtNo
  virtual void insertFollowsStarRelationship(int beforeStmtNo, int afterStmtNo);

  //  calls
  /// @brief Stores the Calls and Calls* relationship in PKB
  ///
  /// @param sourceProcName Name of the caller procedure
  /// @param targetProcName Name of the procedure being called
  /// @return void
  /// @ details For example, "First" calls "Second". "First" is sourceProcName.
  /// "Second" is targetProcName
  virtual void insertCallsRelationship(const std::string& sourceProcName,
                                       const std::string& targetProcName);

  // modifies
  /// @brief Stores modifies relationship in PKB
  ///
  /// This is for Statements
  ///
  /// @param stmtNo Statement number of statement that modifies var
  /// @param var Variable that is being modified
  /// @return void
  virtual void insertModifies(int stmtNo, const std::string& var);

  /// @brief Stores modifies relationship in PKB
  ///
  /// This is for Procedures
  ///
  /// @param procName Name of the procedure that modifies var
  /// @param var Variable that is being modified
  /// @return void
  virtual void insertModifiesProcedure(const std::string& procName,
                                       const std::string& var);

  // Uses
  /// @brief Stores uses relationship in PKB
  ///
  /// This is for Statements
  ///
  /// @param stmtNo Statement number of statement that modifies var
  /// @param var Variable that is being modified
  /// @return void
  virtual void insertUses(int stmtNo, const std::string& var);

  /// @brief Stores uses relationship in PKB
  ///
  /// This is for Procedures
  ///
  /// @param stmtNo Statement number of statement that modifies var
  /// @param var Variable that is being modified
  /// @return void
  virtual void insertUsesProcedure(const std::string& str1,
                                   const std::string& str2);

  /// @brief Stores the direct next relationship in PKB
  ///
  /// @param previousStmtNo stmtNo of the previous stmt
  /// @param nextStmtNo stmtNo of the next stmt
  /// @return void
  /// @ details For example, stmts run in the order 1, 2, 3
  /// then 1 is the previousStmtNo and 2 is the nextStmtNo
  virtual void insertNextRelationship(int previousStmtNo, int nextStmtNo);

  virtual ~WriteFacade() = default;
};
