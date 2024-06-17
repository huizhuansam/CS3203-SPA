#pragma once

#include <PKB.h>
#include <WriteFacade.h>

#include <iostream>
#include <string>
#include <vector>

class WriteFacadeStub : public WriteFacade {
 private:
  [[maybe_unused]] PKB* pkb = nullptr;

 public:
  // Entity Manager

  /// @brief Stores variable in the PKB
  ///
  /// @param var The variable to be stored
  /// @return void
  void addVariable([[maybe_unused]] const std::string& var) override{};

  /// @brief Stores constant in the PKB
  ///
  /// @param constant The constant to be stored
  /// @return void
  void addConstant([[maybe_unused]] const std::string& constant) override{};

  /// @brief Stores procedure in the PKB
  ///
  /// @param proc The procedure to be stored
  /// @return void
  void addProcedure([[maybe_unused]] const std::string& proc) override{};

  /// @brief Stores statement in the PKB
  ///
  /// @param var The statement to be stored
  /// @return void
  /// @details When adding statement, just add the specific StatementType once.
  /// You don't have to do addStatement(StamentType::Statement, 1)  because we
  /// do it for you automatically when you add (StatementType:ASSIGN, 1).
  void addStatement([[maybe_unused]] StatementType type,
                    [[maybe_unused]] int stmtNo) override{};

  /// @brief Stores a stmt number and procName pair, where at the given stmt
  /// number, the procName is called
  ///
  /// @param stmtNo stmtNo
  /// @param procName The procedure called at the given stmtNo
  /// @return void
  void insertStmtCallsProc(
      [[maybe_unused]] int stmtNo,
      [[maybe_unused]] const std::string& procName) override{};

  /// @brief Stores a stmt number and var pair, where at the given stmt number,
  /// the var is printed
  ///
  /// @param stmtNo stmtNo
  /// @param var The var printed at the given stmtNo
  /// @return void
  void insertStmtPrintsVar([[maybe_unused]] int stmtNo,
                           [[maybe_unused]] const std::string& var) override{};

  /// @brief Stores a stmt number and var pair, where at the given stmt number,
  /// the var is read
  ///
  /// @param stmtNo stmtNo
  /// @param var The var read at the given stmtNo
  /// @return void
  void insertStmtReadsVar([[maybe_unused]] int stmtNo,
                          [[maybe_unused]] const std::string& var) override{};

  // Pattern Manager

  /// @brief Stores assignment expression pattern in the PKB
  ///
  /// @param stmtNo Statement number of assignment
  /// @param var Variable on the LHS of assignment
  /// @param exp Expression on the RHS of assignment
  /// @return void
  void addAssignExpPattern(
      [[maybe_unused]] int stmtNo, [[maybe_unused]] const std::string& var,
      [[maybe_unused]] const std::vector<std::string>& exp) override{};

  /// @brief Stores assignment expression pattern in the PKB
  ///
  /// @param stmtNo Statement number of While statement
  /// @param var Control Variable of While statement
  /// @return void
  void addWhileControlVariable(
      [[maybe_unused]] int stmtNo,
      [[maybe_unused]] const std::string& var) override{};

  /// @brief Stores assignment expression pattern in the PKB
  ///
  /// @param stmtNo Statement number of If statement
  /// @param var Control Variable of If statementt
  /// @return void
  void addIfControlVariable([[maybe_unused]] int stmtNo,
                            [[maybe_unused]] const std::string& var) override{};

  // Relationship Manager
  // parent

  /// @brief Stores the direct Parent-Child relationship in PKB
  ///
  /// @param parentStmtNo Statement number of direct parent
  /// @param childStmtNo Statement number of direct child
  /// @return void
  void insertDirectParentChildRelationship(
      [[maybe_unused]] int parentStmtNo,
      [[maybe_unused]] int childStmtNo) override{};

  /// @brief Stores the transitive Parent-Child relationship in PKB
  ///
  /// @param parentStmtNo Statement number of indirect parent
  /// @param childStmtNo Statement number of indirect child
  /// @return void
  void insertParentStarRelationship(
      [[maybe_unused]] int parentStmtNo,
      [[maybe_unused]] int childStmtNo) override{};

  // follows
  /// @brief Stores the direct Follows relationship in PKB
  ///
  /// @param beforeStmtNo Statement number of the before Statement in Follows
  /// Relationship
  /// @param afterStmtNo Statement number of the after Statement in Follows
  /// Relationship
  /// @return void
  /// @ details For example, 1 --> 2. 1 is beforeStmtNo. 2 is afterStmtNo
  void insertDirectFollowsRelationship(
      [[maybe_unused]] int beforeStmtNo,
      [[maybe_unused]] int afterStmtNo) override{};

  /// @brief Stores the direct Follows relationship in PKB
  ///
  /// @param beforeStmtNo Statement number of the before Statement in transitive
  /// Follows Relationship
  /// @param afterStmtNo Statement number of the after Statement in transitive
  /// Follows Relationship
  /// @return void
  /// @ details For example, 1 --> 2. 1 is beforeStmtNo. 2 is afterStmtNo
  void insertFollowsStarRelationship(
      [[maybe_unused]] int beforeStmtNo,
      [[maybe_unused]] int afterStmtNo) override{};

  // calls
  /// @brief Stores the Calls and Calls* relationship in PKB
  ///
  /// @param sourceProcName Name of the caller procedure
  /// @param targetProcName Name of the procedure being called
  /// @return void
  /// @ details For example, "First" calls "Second". "First" is sourceProcName.
  /// "Second" is targetProcName
  virtual void insertCallsRelationship(
      [[maybe_unused]] const std::string& sourceProcName,
      [[maybe_unused]] const std::string& targetProcName) override{};

  // modifies
  /// @brief Stores modifies relationship in PKB
  ///
  /// This is for Statements
  ///
  /// @param stmtNo Statement number of statement that modifies var
  /// @param var Variable that is being modified
  /// @return void
  void insertModifies([[maybe_unused]] int stmtNo,
                      [[maybe_unused]] const std::string& var) override{};

  /// @brief Stores modifies relationship in PKB
  ///
  /// This is for Procedures
  ///
  /// @param procName Name of the procedure that modifies var
  /// @param var Variable that is being modified
  /// @return void
  void insertModifiesProcedure(
      [[maybe_unused]] const std::string& procName,
      [[maybe_unused]] const std::string& var) override{};

  // Uses
  /// @brief Stores uses relationship in PKB
  ///
  /// This is for Statements
  ///
  /// @param stmtNo Statement number of statement that modifies var
  /// @param var Variable that is being modified
  /// @return void
  void insertUses([[maybe_unused]] int stmtNo,
                  [[maybe_unused]] const std::string& var) override{};

  /// @brief Stores uses relationship in PKB
  ///
  /// This is for Procedures
  ///
  /// @param stmtNo Statement number of statement that modifies var
  /// @param var Variable that is being modified
  /// @return void
  void insertUsesProcedure([[maybe_unused]] const std::string& str1,
                           [[maybe_unused]] const std::string& str2) override{};

  /// @brief Stores the direct next relationship in PKB
  ///
  /// @param previousStmtNo stmtNo of the previous stmt
  /// @param nextStmtNo stmtNo of the next stmt
  /// @return void
  /// @ details For example, stmts run in the order 1, 2, 3
  /// then 1 is the previousStmtNo and 2 is the nextStmtNo
  void insertNextRelationship([[maybe_unused]] int previousStmtNo,
                              [[maybe_unused]] int nextStmtNo) override {}
};
