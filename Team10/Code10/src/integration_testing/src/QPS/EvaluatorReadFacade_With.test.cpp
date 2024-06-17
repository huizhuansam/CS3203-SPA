#include "ReadFacade.h"
#include "WriteFacade.h"
#include "catch.hpp"
#include "evaluator/Evaluator.h"
#include "fixtures/Strategies.h"

using namespace QPS;

TEST_CASE("QPS::Evaluator integration with ReadFacade for With clause",
          "[With]") {
  // Setup
  WriteFacade writer{};
  writer.clearPKB();
  ReadFacade reader{};

  // Write data to PKB
  // procedure main {
  //    two = 0;
  //    three = 3;
  //    while (two < 4) {
  //       if (two > 2) then {
  //          two = two + 1;
  //       } else {
  //          two = two + 3;
  //          call two;
  //       }
  //    }
  //    read three;
  // }
  // procedure two {
  //    print three;
  // }
  writer.addProcedure("main");
  writer.addProcedure("two");
  writer.addStatement(StatementType::ASSIGN, 1);
  writer.addStatement(StatementType::ASSIGN, 2);
  writer.addStatement(StatementType::WHILE, 3);
  writer.addStatement(StatementType::IF, 4);
  writer.addStatement(StatementType::ASSIGN, 5);
  writer.addStatement(StatementType::ASSIGN, 6);
  writer.addStatement(StatementType::CALL, 7);
  writer.addStatement(StatementType::READ, 8);
  writer.addStatement(StatementType::PRINT, 9);
  writer.addVariable("two");
  writer.addVariable("three");
  writer.addConstant("0");
  writer.addConstant("1");
  writer.addConstant("2");
  writer.addConstant("3");
  writer.addConstant("4");

  writer.addAssignExpPattern(1, "two", {"0"});
  writer.addAssignExpPattern(2, "three", {"3"});
  writer.addWhileControlVariable(3, "two");
  writer.addIfControlVariable(4, "two");
  writer.addAssignExpPattern(5, "two", {"two", "+", "1"});
  writer.addAssignExpPattern(6, "two", {"two", "+", "3"});
  writer.insertStmtCallsProc(7, "two");
  writer.insertStmtReadsVar(8, "three");
  writer.insertStmtPrintsVar(9, "three");

  SECTION("with int = int, evaluates to true") {
    // Select s with 3 = 3
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "3", RefType::INTEGER, "3", RefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{withStrategy}});
    std::list<std::string> expected = {"1", "2", "3", "4", "5",
                                       "6", "7", "8", "9"};
    REQUIRE(result == expected);
  }

  SECTION("with int = int, evaluates to false") {
    // Select s with 3 = 4
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "3", RefType::INTEGER, "4", RefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{withStrategy}});
    std::list<std::string> expected = {};
    REQUIRE(result == expected);
  }

  SECTION("with ident = ident, evaluates to true") {
    // Select s with "hello" = "hello"
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "hello", RefType::IDENT, "hello", RefType::IDENT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{withStrategy}});
    std::list<std::string> expected = {"1", "2", "3", "4", "5",
                                       "6", "7", "8", "9"};
    REQUIRE(result == expected);
  }

  SECTION("with ident = ident, evaluates to false") {
    // Select s with "hello" = "bye"
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "hello", RefType::IDENT, "bye", RefType::IDENT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{withStrategy}});
    std::list<std::string> expected = {};
    REQUIRE(result == expected);
  }

  // attRef = int, int = attrRef

  SECTION("with s.stmt# = int") {
    // Select s with s.stmt# = 4
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "s", RefType::STMT_STMTNO, "4", RefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_s, {{withStrategy}});
    std::list<std::string> expected = {"4"};
    REQUIRE(result == expected);
  }

  SECTION("with a.stmt# = int") {
    // Select a with a.stmt# = 6
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "a", RefType::ASSIGN_STMTNO, "6", RefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{withStrategy}});
    std::list<std::string> expected = {"6"};
    REQUIRE(result == expected);
  }

  SECTION("with r.stmt# = int") {
    // Select r with r.stmt# = 6
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "r", RefType::READ_STMTNO, "8", RefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_r, {{withStrategy}});
    std::list<std::string> expected = {"8"};
    REQUIRE(result == expected);
  }

  SECTION("with pn.stmt# = int") {
    // Select pn with pn.stmt# = 9
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "pn", RefType::PRINT_STMTNO, "9", RefType::INTEGER);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_pn, {{withStrategy}});
    std::list<std::string> expected = {"9"};
    REQUIRE(result == expected);
  }

  SECTION("with int = c.stmt#") {
    // Select c with 7 = c.stmt#
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "7", RefType::INTEGER, "c", RefType::CALL_STMTNO);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_c, {{withStrategy}});
    std::list<std::string> expected = {"7"};
    REQUIRE(result == expected);
  }

  SECTION("with int = w.stmt#") {
    // Select w with 3 = w.stmt#
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "3", RefType::INTEGER, "w", RefType::WHILE_STMTNO);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_w, {{withStrategy}});
    std::list<std::string> expected = {"3"};
    REQUIRE(result == expected);
  }

  SECTION("with int = i.stmt#") {
    // Select w with 4 = i.stmt#
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "4", RefType::INTEGER, "i", RefType::IF_STMTNO);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_i, {{withStrategy}});
    std::list<std::string> expected = {"4"};
    REQUIRE(result == expected);
  }

  SECTION("with int = const.value") {
    // Select const with 1 = const.value
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "1", RefType::INTEGER, "const", RefType::CONSTANT_VALUE);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_const, {{withStrategy}});
    std::list<std::string> expected = {"1"};
    REQUIRE(result == expected);
  }

  // attrRef = ident, ident = attrRef

  SECTION("with p.procName = ident") {
    // Select p with p.procName = main
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "p", RefType::PROCEDURE_PROCNAME, "main", RefType::IDENT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_p, {{withStrategy}});
    std::list<std::string> expected = {"main"};
    REQUIRE(result == expected);
  }

  SECTION("with v.varName = ident") {
    // Select v with v.varName = three
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "v", RefType::VARIABLE_VARNAME, "three", RefType::IDENT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_v, {{withStrategy}});
    std::list<std::string> expected = {"three"};
    REQUIRE(result == expected);
  }

  SECTION("with r.varName = ident") {
    // Select r with r.varName = three
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "r", RefType::READ_VARNAME, "three", RefType::IDENT);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_r, {{withStrategy}});
    std::list<std::string> expected = {"8"};
    REQUIRE(result == expected);
  }

  SECTION("with ident = c.procName") {
    // Select c with two = c.procName
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "two", RefType::IDENT, "c", RefType::CALL_PROCNAME);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_c, {{withStrategy}});
    std::list<std::string> expected = {"7"};
    REQUIRE(result == expected);
  }

  SECTION("with ident = c.procName") {
    // Select c with two = c.procName
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "two", RefType::IDENT, "c", RefType::CALL_PROCNAME);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_c, {{withStrategy}});
    std::list<std::string> expected = {"7"};
    REQUIRE(result == expected);
  }

  SECTION("with ident = pn.varName") {
    // Select pn with three = pn.varName
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "three", RefType::IDENT, "pn", RefType::PRINT_VARNAME);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_pn, {{withStrategy}});
    std::list<std::string> expected = {"9"};
    REQUIRE(result == expected);
  }

  // attrRef == attrRef

  SECTION("with v.varName = p.procName") {
    // Select p with v.varName = p.procName
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "v", RefType::VARIABLE_VARNAME, "p", RefType::PROCEDURE_PROCNAME);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_p, {{withStrategy}});
    std::list<std::string> expected = {"two"};
    REQUIRE(result == expected);
  }

  SECTION("with pn.varName = r.varName") {
    // Select pn with pn.varName = r.varName
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "pn", RefType::PRINT_VARNAME, "r", RefType::READ_VARNAME);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_pn, {{withStrategy}});
    std::list<std::string> expected = {"9"};
    REQUIRE(result == expected);
  }

  SECTION("with a.stmt# = const.value") {
    // Select a with a.stmt# = const.value
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "a", RefType::ASSIGN_STMTNO, "const", RefType::CONSTANT_VALUE);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_a, {{withStrategy}});
    std::list<std::string> expected = {"1", "2"};
    REQUIRE(result == expected);
  }

  SECTION("with w.stmt# = s.stmt#") {
    // Select w with w.stmt# = s.stmt#
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "w", RefType::WHILE_STMTNO, "s", RefType::STMT_STMTNO);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_w, {{withStrategy}});
    std::list<std::string> expected = {"3"};
    REQUIRE(result == expected);
  }

  SECTION("with i.stmt# = w.stmt#, evaluates to false") {
    // Select i with i.stmt# = w.stmt#
    std::shared_ptr<Strategy> withStrategy = std::make_shared<WithStrategy>(
        "i", RefType::IF_STMTNO, "w", RefType::WHILE_STMTNO);
    std::list<std::string> result = Evaluator::getResultList(
        reader, Strategies::select_i, {{withStrategy}});
    std::list<std::string> expected = {};
    REQUIRE(result == expected);
  }

  // Cleanup
  writer.clearPKB();
}
