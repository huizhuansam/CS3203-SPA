#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ReadFacade.h"
#include "WriteFacade.h"
#include "catch.hpp"
#include "extractor/DesignExtractor.h"
#include "tokenizer/Token.h"
#include "tokenizer/TokenType.h"

using namespace SP;

// SP::DesignExtractor integration with WriteFacade

TEST_CASE("SP::DesignExtractor integration with WriteFacade") {
  // Setup
  WriteFacade writer{};
  writer.clearPKB();
  ReadFacade reader{};
  DesignExtractor::resetStmtNumber();

  SECTION("Valid SIMPLE source program") {
    std::string procName = "computeCentroid";
    std::string var_count = "count";
    std::string var_cenX = "cenX";
    std::string var_cenY = "cenY";
    std::string var_x = "x";
    std::string var_y = "y";
    std::string var_flag = "flag";
    std::string var_normSq = "normSq";
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, procName));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_count));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenX));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenY));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_count));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenX));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenY));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenX));
    tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::AND, "&&"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenY));
    tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_count));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_count));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenX));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenX));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_x));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenY));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenY));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_y));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_count));
    tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "0"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_flag));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenX));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenX));
    tokens.push_back(std::make_unique<Token>(TokenType::DIVIDE, "/"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_count));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenY));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenY));
    tokens.push_back(std::make_unique<Token>(TokenType::DIVIDE, "/"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_count));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_normSq));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenX));
    tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenX));
    tokens.push_back(std::make_unique<Token>(TokenType::PLUS, "+"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenY));
    tokens.push_back(std::make_unique<Token>(TokenType::MULTIPLY, "*"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenY));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenX));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_cenY));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, var_normSq));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    DesignExtractor::extract(tokens);

    auto variables = reader.getAllVariables();
    REQUIRE(variables.size() == 7);
    REQUIRE(variables.count(var_count) == 1);
    REQUIRE(variables.count(var_cenX) == 1);
    REQUIRE(variables.count(var_cenY) == 1);
    REQUIRE(variables.count(var_x) == 1);
    REQUIRE(variables.count(var_y) == 1);
    REQUIRE(variables.count(var_flag) == 1);
    REQUIRE(variables.count(var_normSq) == 1);

    auto constants = reader.getAllConstants();
    REQUIRE(constants.size() == 2);
    REQUIRE(constants.count("0") == 1);
    REQUIRE(constants.count("1") == 1);

    auto procedures = reader.getAllProcedures();
    REQUIRE(procedures.size() == 1);
    REQUIRE(procedures.count(procName) == 1);

    auto statements = reader.getStatements();
    REQUIRE(statements.size() == 18);

    auto assigns = reader.getAssigns();
    REQUIRE(assigns.size() == 10);

    auto reads = reader.getReads();
    REQUIRE(reads.size() == 3);
    REQUIRE(reads.count(1) == 1);
    REQUIRE(reads.count(2) == 1);
    REQUIRE(reads.count(3) == 1);

    auto prints = reader.getPrints();
    REQUIRE(prints.size() == 3);
    REQUIRE(prints.count(16) == 1);
    REQUIRE(prints.count(17) == 1);
    REQUIRE(prints.count(18) == 1);

    auto calls = reader.getCalls();
    REQUIRE(calls.size() == 0);

    auto whiles = reader.getWhiles();
    REQUIRE(whiles.size() == 1);
    REQUIRE(whiles.count(7) == 1);

    auto ifs = reader.getIfs();
    REQUIRE(ifs.size() == 1);
    REQUIRE(ifs.count(11) == 1);

    auto assignExpPairs = reader.getAllAssignExpPairs();
    REQUIRE(assignExpPairs.size() == 10);

    // TODO: getAssignExpPairsPartialMatch
    // TODO : getAssignExpPairsSynonymPartialMatch

    auto getWhileChildren = reader.getChildren(7);
    REQUIRE(getWhileChildren.size() == 3);

    auto getIfChildren = reader.getChildren(11);
    REQUIRE(getIfChildren.size() == 3);

    auto get8Parent = reader.getParent(8);
    REQUIRE(get8Parent == 7);

    auto get9Parent = reader.getParent(9);
    REQUIRE(get9Parent == 7);

    auto get10Parent = reader.getParent(10);
    REQUIRE(get10Parent == 7);

    auto get12Parent = reader.getParent(12);
    REQUIRE(get12Parent == 11);

    auto get13Parent = reader.getParent(13);
    REQUIRE(get13Parent == 11);

    auto get14Parent = reader.getParent(14);
    REQUIRE(get14Parent == 11);

    auto getWhileChildrenStar = reader.getChildrenStar(7);
    REQUIRE(getWhileChildrenStar.size() == 3);

    auto getIfChildrenStar = reader.getChildrenStar(11);
    REQUIRE(getIfChildrenStar.size() == 3);

    auto get8ParentStar = reader.getParentStar(8);
    REQUIRE(get8ParentStar.size() == 1);

    auto get9ParentStar = reader.getParentStar(9);
    REQUIRE(get9ParentStar.size() == 1);

    auto get10ParentStar = reader.getParentStar(10);
    REQUIRE(get10ParentStar.size() == 1);

    auto get12ParentStar = reader.getParentStar(12);
    REQUIRE(get12ParentStar.size() == 1);

    auto get13ParentStar = reader.getParentStar(13);
    REQUIRE(get13ParentStar.size() == 1);

    auto get14ParentStar = reader.getParentStar(14);
    REQUIRE(get14ParentStar.size() == 1);

    auto allParentPairs = reader.getAllParentPairs();
    REQUIRE(allParentPairs.size() == 6);

    auto getParentStarPairs = reader.getAllParentStarPairs();
    REQUIRE(getParentStarPairs.size() == 6);

    auto parents = reader.getAllParents();
    REQUIRE(parents.size() == 2);

    auto children = reader.getAllChildren();
    REQUIRE(children.size() == 6);

    auto statementFollows1 = reader.getStmtThatFollowsAfter(1);
    REQUIRE(statementFollows1 == 2);

    auto statementFollows2 = reader.getStmtThatFollowsAfter(2);
    REQUIRE(statementFollows2 == 3);

    auto statementFollows3 = reader.getStmtThatFollowsAfter(3);
    REQUIRE(statementFollows3 == 4);

    auto statementFollows4 = reader.getStmtThatFollowsAfter(4);
    REQUIRE(statementFollows4 == 5);

    auto statementFollows5 = reader.getStmtThatFollowsAfter(5);
    REQUIRE(statementFollows5 == 6);

    auto statementFollows6 = reader.getStmtThatFollowsAfter(6);
    REQUIRE(statementFollows6 == 7);

    auto statementFollows7 = reader.getStmtThatFollowsAfter(7);
    REQUIRE(statementFollows7 == 11);

    auto statementFollows8 = reader.getStmtThatFollowsAfter(8);
    REQUIRE(statementFollows8 == 9);

    auto statementFollows9 = reader.getStmtThatFollowsAfter(9);
    REQUIRE(statementFollows9 == 10);

    auto statementFollows11 = reader.getStmtThatFollowsAfter(11);
    REQUIRE(statementFollows11 == 15);

    auto statementFollows13 = reader.getStmtThatFollowsAfter(13);
    REQUIRE(statementFollows13 == 14);

    auto statementFollows15 = reader.getStmtThatFollowsAfter(15);
    REQUIRE(statementFollows15 == 16);

    auto statementFollows16 = reader.getStmtThatFollowsAfter(16);
    REQUIRE(statementFollows16 == 17);

    auto statementFollows17 = reader.getStmtThatFollowsAfter(17);
    REQUIRE(statementFollows17 == 18);

    auto statementFollowedBy18 = reader.getStmtThatFollowsBefore(18);
    REQUIRE(statementFollowedBy18 == 17);

    auto statementFollowedBy17 = reader.getStmtThatFollowsBefore(17);
    REQUIRE(statementFollowedBy17 == 16);

    auto statementFollowedBy16 = reader.getStmtThatFollowsBefore(16);
    REQUIRE(statementFollowedBy16 == 15);

    auto statementFollowedBy15 = reader.getStmtThatFollowsBefore(15);
    REQUIRE(statementFollowedBy15 == 11);

    auto statementFollowedBy14 = reader.getStmtThatFollowsBefore(14);
    REQUIRE(statementFollowedBy14 == 13);

    auto statementFollowedBy11 = reader.getStmtThatFollowsBefore(11);
    REQUIRE(statementFollowedBy11 == 7);

    auto statementFollowedBy10 = reader.getStmtThatFollowsBefore(10);
    REQUIRE(statementFollowedBy10 == 9);

    auto statementFollowedBy9 = reader.getStmtThatFollowsBefore(9);
    REQUIRE(statementFollowedBy9 == 8);

    auto statementFollowedBy7 = reader.getStmtThatFollowsBefore(7);
    REQUIRE(statementFollowedBy7 == 6);

    auto statementFollowedBy6 = reader.getStmtThatFollowsBefore(6);
    REQUIRE(statementFollowedBy6 == 5);

    auto statementFollowedBy5 = reader.getStmtThatFollowsBefore(5);
    REQUIRE(statementFollowedBy5 == 4);

    auto statementFollowedBy4 = reader.getStmtThatFollowsBefore(4);
    REQUIRE(statementFollowedBy4 == 3);

    auto statementFollowedBy3 = reader.getStmtThatFollowsBefore(3);
    REQUIRE(statementFollowedBy3 == 2);

    auto statementFollowedBy2 = reader.getStmtThatFollowsBefore(2);
    REQUIRE(statementFollowedBy2 == 1);

    auto statementsFollows1 = reader.getAllStmtsThatFollowAfter(1);
    REQUIRE(statementsFollows1.size() == 11);

    auto statementsFollows2 = reader.getAllStmtsThatFollowAfter(2);
    REQUIRE(statementsFollows2.size() == 10);

    auto statementsFollows3 = reader.getAllStmtsThatFollowAfter(3);
    REQUIRE(statementsFollows3.size() == 9);

    auto statementsFollows4 = reader.getAllStmtsThatFollowAfter(4);
    REQUIRE(statementsFollows4.size() == 8);

    auto statementsFollows5 = reader.getAllStmtsThatFollowAfter(5);
    REQUIRE(statementsFollows5.size() == 7);

    auto statementsFollows6 = reader.getAllStmtsThatFollowAfter(6);
    REQUIRE(statementsFollows6.size() == 6);

    auto statementsFollows7 = reader.getAllStmtsThatFollowAfter(7);
    REQUIRE(statementsFollows7.size() == 5);

    auto statementsFollows8 = reader.getAllStmtsThatFollowAfter(8);
    REQUIRE(statementsFollows8.size() == 2);

    auto statementsFollows9 = reader.getAllStmtsThatFollowAfter(9);
    REQUIRE(statementsFollows9.size() == 1);

    auto statementsFollows11 = reader.getAllStmtsThatFollowAfter(11);
    REQUIRE(statementsFollows11.size() == 4);

    auto statementsFollows13 = reader.getAllStmtsThatFollowAfter(13);
    REQUIRE(statementsFollows13.size() == 1);

    auto statementsFollows15 = reader.getAllStmtsThatFollowAfter(15);
    REQUIRE(statementsFollows15.size() == 3);

    auto statementsFollows16 = reader.getAllStmtsThatFollowAfter(16);
    REQUIRE(statementsFollows16.size() == 2);

    auto statementsFollows17 = reader.getAllStmtsThatFollowAfter(17);
    REQUIRE(statementsFollows17.size() == 1);

    auto statementsFollowedBy18 = reader.getAllStmtsThatFollowBefore(18);
    REQUIRE(statementsFollowedBy18.size() == 11);

    auto statementsFollowedBy17 = reader.getAllStmtsThatFollowBefore(17);
    REQUIRE(statementsFollowedBy17.size() == 10);

    auto statementsFollowedBy16 = reader.getAllStmtsThatFollowBefore(16);
    REQUIRE(statementsFollowedBy16.size() == 9);

    auto statementsFollowedBy15 = reader.getAllStmtsThatFollowBefore(15);
    REQUIRE(statementsFollowedBy15.size() == 8);

    auto statementsFollowedBy14 = reader.getAllStmtsThatFollowBefore(14);
    REQUIRE(statementsFollowedBy14.size() == 1);

    auto statementsFollowedBy11 = reader.getAllStmtsThatFollowBefore(11);
    REQUIRE(statementsFollowedBy11.size() == 7);

    auto statementsFollowedBy10 = reader.getAllStmtsThatFollowBefore(10);
    REQUIRE(statementsFollowedBy10.size() == 2);

    auto statementsFollowedBy9 = reader.getAllStmtsThatFollowBefore(9);
    REQUIRE(statementsFollowedBy9.size() == 1);

    auto statementsFollowedBy7 = reader.getAllStmtsThatFollowBefore(7);
    REQUIRE(statementsFollowedBy7.size() == 6);

    auto statementsFollowedBy6 = reader.getAllStmtsThatFollowBefore(6);
    REQUIRE(statementsFollowedBy6.size() == 5);

    auto statementsFollowedBy5 = reader.getAllStmtsThatFollowBefore(5);
    REQUIRE(statementsFollowedBy5.size() == 4);

    auto statementsFollowedBy4 = reader.getAllStmtsThatFollowBefore(4);
    REQUIRE(statementsFollowedBy4.size() == 3);

    auto statementsFollowedBy3 = reader.getAllStmtsThatFollowBefore(3);
    REQUIRE(statementsFollowedBy3.size() == 2);

    auto statementsFollowedBy2 = reader.getAllStmtsThatFollowBefore(2);
    REQUIRE(statementsFollowedBy2.size() == 1);

    auto followPairs = reader.getAllFollowPairs();
    REQUIRE(followPairs.size() == 14);

    auto followsStarPairs = reader.getAllFollowStarPairs();
    unsigned long numFollowsStarPairs =
        (11 + 10 + 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1) + (2 + 1) + 1;
    REQUIRE(followsStarPairs.size() == numFollowsStarPairs);

    auto stmtFollowOtherStmt = reader.getAllStmtsThatFollowAfterOtherStmts();
    REQUIRE(stmtFollowOtherStmt.size() == 14);

    auto stmtFollowBeforeOtherStmt =
        reader.getAllStmtsThatFollowBeforeOtherStmts();
    REQUIRE(stmtFollowBeforeOtherStmt.size() == 14);

    auto varsModifiedBy1 = reader.getVarsModifiedByStmt(1);
    REQUIRE(varsModifiedBy1.size() == 1);
    REQUIRE(varsModifiedBy1.find(var_count) != varsModifiedBy1.end());

    auto varsModifiedBy2 = reader.getVarsModifiedByStmt(2);
    REQUIRE(varsModifiedBy2.size() == 1);
    REQUIRE(varsModifiedBy2.find(var_cenX) != varsModifiedBy2.end());

    auto varsModifiedBy3 = reader.getVarsModifiedByStmt(3);
    REQUIRE(varsModifiedBy3.size() == 1);
    REQUIRE(varsModifiedBy3.find(var_cenY) != varsModifiedBy3.end());

    auto varsModifiedBy4 = reader.getVarsModifiedByStmt(4);
    REQUIRE(varsModifiedBy4.size() == 1);
    REQUIRE(varsModifiedBy4.find(var_count) != varsModifiedBy4.end());

    auto varsModifiedBy5 = reader.getVarsModifiedByStmt(5);
    REQUIRE(varsModifiedBy5.size() == 1);
    REQUIRE(varsModifiedBy5.find(var_cenX) != varsModifiedBy5.end());

    auto varsModifiedBy6 = reader.getVarsModifiedByStmt(6);
    REQUIRE(varsModifiedBy6.size() == 1);
    REQUIRE(varsModifiedBy6.find(var_cenY) != varsModifiedBy6.end());

    auto varsModifiedBy8 = reader.getVarsModifiedByStmt(8);
    REQUIRE(varsModifiedBy8.size() == 1);
    REQUIRE(varsModifiedBy8.find(var_count) != varsModifiedBy8.end());

    auto varsModifiedBy9 = reader.getVarsModifiedByStmt(9);
    REQUIRE(varsModifiedBy9.size() == 1);
    REQUIRE(varsModifiedBy9.find(var_cenX) != varsModifiedBy9.end());

    auto varsModifiedBy10 = reader.getVarsModifiedByStmt(10);
    REQUIRE(varsModifiedBy10.size() == 1);
    REQUIRE(varsModifiedBy10.find(var_cenY) != varsModifiedBy10.end());

    auto varsModifiedBy12 = reader.getVarsModifiedByStmt(12);
    REQUIRE(varsModifiedBy12.size() == 1);
    REQUIRE(varsModifiedBy12.find(var_flag) != varsModifiedBy12.end());

    auto varsModifiedBy13 = reader.getVarsModifiedByStmt(13);
    REQUIRE(varsModifiedBy13.size() == 1);
    REQUIRE(varsModifiedBy13.find(var_cenX) != varsModifiedBy13.end());

    auto varsModifiedBy14 = reader.getVarsModifiedByStmt(14);
    REQUIRE(varsModifiedBy14.size() == 1);
    REQUIRE(varsModifiedBy14.find(var_cenY) != varsModifiedBy14.end());

    auto varsModifiedBy15 = reader.getVarsModifiedByStmt(15);
    REQUIRE(varsModifiedBy15.size() == 1);
    REQUIRE(varsModifiedBy15.find(var_normSq) != varsModifiedBy15.end());

    auto stmtsThatModifyVarCount = reader.getStmtsThatModifyVar(var_count);
    REQUIRE(stmtsThatModifyVarCount.size() == 4);

    auto stmtsThatModifyVarCenX = reader.getStmtsThatModifyVar(var_cenX);
    REQUIRE(stmtsThatModifyVarCenX.size() == 6);

    auto stmtsThatModifyVarCenY = reader.getStmtsThatModifyVar(var_cenY);
    REQUIRE(stmtsThatModifyVarCenY.size() == 6);

    auto stmtsThatModifyVarFlag = reader.getStmtsThatModifyVar(var_flag);
    REQUIRE(stmtsThatModifyVarFlag.size() == 2);

    auto stmtsThatModifyVarNormSq = reader.getStmtsThatModifyVar(var_normSq);
    REQUIRE(stmtsThatModifyVarNormSq.size() == 1);

    auto varModifiedByStmtPairs = reader.getAllVarModifiedByStmtPairs();
    REQUIRE(varModifiedByStmtPairs.size() == 19);

    auto varsModifiedByProc = reader.getVarsModifiedByProcedure(procName);
    REQUIRE(varsModifiedByProc.size() == 5);

    auto procThatModifiesVarCount =
        reader.getProceduresThatModifyVar(var_count);
    REQUIRE(procThatModifiesVarCount.size() == 1);
    REQUIRE(procThatModifiesVarCount.find(procName) !=
            procThatModifiesVarCount.end());

    auto procThatModifiesVarCenX = reader.getProceduresThatModifyVar(var_cenX);
    REQUIRE(procThatModifiesVarCenX.size() == 1);
    REQUIRE(procThatModifiesVarCenX.find(procName) !=
            procThatModifiesVarCenX.end());

    auto procThatModifiesVarCenY = reader.getProceduresThatModifyVar(var_cenY);
    REQUIRE(procThatModifiesVarCenY.size() == 1);
    REQUIRE(procThatModifiesVarCenY.find(procName) !=
            procThatModifiesVarCenY.end());

    auto procThatModifiesVarFlag = reader.getProceduresThatModifyVar(var_flag);
    REQUIRE(procThatModifiesVarFlag.size() == 1);
    REQUIRE(procThatModifiesVarFlag.find(procName) !=
            procThatModifiesVarFlag.end());

    auto procThatModifiesVarNormSq =
        reader.getProceduresThatModifyVar(var_normSq);
    REQUIRE(procThatModifiesVarNormSq.size() == 1);
    REQUIRE(procThatModifiesVarNormSq.find(procName) !=
            procThatModifiesVarNormSq.end());

    auto varsModifiedByProcPairs = reader.getAllVarModifiedByProcedurePairs();
    REQUIRE(varsModifiedByProcPairs.size() == 5);

    auto stmtsModifyVars = reader.getAllStmtsThatModifyVars();
    REQUIRE(stmtsModifyVars.size() == 15);

    auto varsModifiedByStmts = reader.getAllVarsModifiedByStmts();
    REQUIRE(varsModifiedByStmts.size() == 5);

    auto varsModifiedByProcs = reader.getAllVarsModifiedByProcedures();
    REQUIRE(varsModifiedByProcs.size() == 5);

    auto varsUsedBy7 = reader.getVarsUsedByStmt(7);
    REQUIRE(varsUsedBy7.size() == 5);

    auto varsUsedBy8 = reader.getVarsUsedByStmt(8);
    REQUIRE(varsUsedBy8.size() == 1);
    REQUIRE(varsUsedBy8.find(var_count) != varsUsedBy8.end());

    auto varsUsedBy9 = reader.getVarsUsedByStmt(9);
    REQUIRE(varsUsedBy9.size() == 2);

    auto varsUsedBy10 = reader.getVarsUsedByStmt(10);
    REQUIRE(varsUsedBy10.size() == 2);

    auto varsUsedBy11 = reader.getVarsUsedByStmt(11);
    REQUIRE(varsUsedBy11.size() == 3);

    auto varsUsedBy13 = reader.getVarsUsedByStmt(13);
    REQUIRE(varsUsedBy13.size() == 2);

    auto varsUsedBy14 = reader.getVarsUsedByStmt(14);
    REQUIRE(varsUsedBy14.size() == 2);

    auto varsUsedBy15 = reader.getVarsUsedByStmt(15);
    REQUIRE(varsUsedBy15.size() == 2);

    auto varsUsedBy16 = reader.getVarsUsedByStmt(16);
    REQUIRE(varsUsedBy16.size() == 1);

    auto varsUsedBy17 = reader.getVarsUsedByStmt(17);
    REQUIRE(varsUsedBy17.size() == 1);

    auto varsUsedBy18 = reader.getVarsUsedByStmt(18);
    REQUIRE(varsUsedBy18.size() == 1);

    auto stmtsThatUseVarCount = reader.getStmtsThatUseVar(var_count);
    REQUIRE(stmtsThatUseVarCount.size() == 5);

    auto stmtsThatUseVarCenX = reader.getStmtsThatUseVar(var_cenX);
    REQUIRE(stmtsThatUseVarCenX.size() == 6);

    auto stmtsThatUseVarCenY = reader.getStmtsThatUseVar(var_cenY);
    REQUIRE(stmtsThatUseVarCenY.size() == 6);

    auto stmtsThatUseVarX = reader.getStmtsThatUseVar(var_x);
    REQUIRE(stmtsThatUseVarX.size() == 2);

    auto stmtsThatUseVarY = reader.getStmtsThatUseVar(var_y);
    REQUIRE(stmtsThatUseVarY.size() == 2);

    auto stmtsThatUseVarNormSq = reader.getStmtsThatUseVar(var_normSq);
    REQUIRE(stmtsThatUseVarNormSq.size() == 1);

    auto varsUsedByStmtPairs = reader.getAllVarUsedByStmtPairs();
    REQUIRE(varsUsedByStmtPairs.size() == 22);

    auto varsUsedByProc = reader.getVarsUsedByProcedure(procName);
    REQUIRE(varsUsedByProc.size() == 6);

    auto procsThatUsesVarCount = reader.getProceduresThatUseVar(var_count);
    REQUIRE(procsThatUsesVarCount.size() == 1);

    REQUIRE(procsThatUsesVarCount.find(procName) !=
            procsThatUsesVarCount.end());

    auto procsThatUsesVarCenX = reader.getProceduresThatUseVar(var_cenX);
    REQUIRE(procsThatUsesVarCenX.size() == 1);
    REQUIRE(procsThatUsesVarCenX.find(procName) != procsThatUsesVarCenX.end());

    auto procsThatUsesVarCenY = reader.getProceduresThatUseVar(var_cenY);
    REQUIRE(procsThatUsesVarCenY.size() == 1);
    REQUIRE(procsThatUsesVarCenY.find(procName) != procsThatUsesVarCenY.end());

    auto procsThatUsesVarX = reader.getProceduresThatUseVar(var_x);
    REQUIRE(procsThatUsesVarX.size() == 1);
    REQUIRE(procsThatUsesVarX.find(procName) != procsThatUsesVarX.end());

    auto procsThatUsesVarY = reader.getProceduresThatUseVar(var_y);
    REQUIRE(procsThatUsesVarY.size() == 1);
    REQUIRE(procsThatUsesVarY.find(procName) != procsThatUsesVarY.end());

    auto procsThatUsesVarNormSq = reader.getProceduresThatUseVar(var_normSq);
    REQUIRE(procsThatUsesVarNormSq.size() == 1);
    REQUIRE(procsThatUsesVarNormSq.find(procName) !=
            procsThatUsesVarNormSq.end());

    auto varUsedByProcPairs = reader.getAllVarUsedByProcedurePairs();
    REQUIRE(varUsedByProcPairs.size() == 6);

    auto stmtsThatUseVars = reader.getAllStmtsThatUseVars();
    REQUIRE(stmtsThatUseVars.size() == 11);

    auto varsUsedByStmts = reader.getAllVarsUsedByStmts();
    REQUIRE(varsUsedByStmts.size() == 6);

    auto procsThatUseVars = reader.getAllProceduresThatUseVars();
    REQUIRE(procsThatUseVars.size() == 1);

    auto varsUsedByProcs = reader.getAllVarsUsedByProcedures();
    REQUIRE(varsUsedByProcs.size() == 6);
  }

  SECTION("Simple Procedures Call program token") {
    writer.clearPKB();
    // procedure First {
    //   call Second; } // 01
    //
    // procedure Second {
    //   call Third;} // 02
    //
    // procedure Third {
    //      print v; }
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "First"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::CALL, "call"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "Second"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "Second"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::CALL, "call"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "Third"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "Third"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "v"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));

    DesignExtractor::extract(tokens);
    std::string firstProcName = "First";
    std::string secondProcName = "Second";
    std::string thirdProcName = "Third";

    // All call statement = 1, 2
    REQUIRE(reader.getCalls() == std::unordered_set<int>{1, 2});

    // No procedure calls First
    REQUIRE(reader.getProcsThatCalls(firstProcName).empty());

    // First calls Second, Second called by First
    REQUIRE(reader.getProcsThatCalls(secondProcName) ==
            std::unordered_set<std::string>{firstProcName});
    REQUIRE(reader.getProcsThatIsCalledBy(firstProcName) ==
            std::unordered_set<std::string>{secondProcName});

    // Second calls Third, Third called by Second
    REQUIRE(reader.getProcsThatCalls(thirdProcName) ==
            std::unordered_set<std::string>{secondProcName});
    REQUIRE(reader.getProcsThatIsCalledBy(secondProcName) ==
            std::unordered_set<std::string>{thirdProcName});

    // All call pairs = (First, Second), (Second, Third)
    REQUIRE(
        reader.getAllCallPairs() ==
        std::unordered_set<std::pair<std::string, std::string>, PairHash>{
            std::pair<std::string, std::string>(firstProcName, secondProcName),
            std::pair<std::string, std::string>(secondProcName,
                                                thirdProcName)});

    // All procedure calls that call other procedures = (First, Second)
    REQUIRE(reader.getAllProcsThatCallOtherProcs() ==
            std::unordered_set<std::string>{firstProcName, secondProcName});

    // All procedures that get called by other procedures = (Second, Third)
    REQUIRE(reader.getAllProcsThatGetCalledByOtherProcs() ==
            std::unordered_set<std::string>{secondProcName, thirdProcName});

    // No procedure calls* First
    REQUIRE(reader.getProcsThatCallsStar(firstProcName).empty());

    // First calls* Second
    REQUIRE(reader.getProcsThatCallsStar(secondProcName) ==
            std::unordered_set<std::string>{firstProcName});

    // First and Second calls* Third
    REQUIRE(reader.getProcsThatCallsStar(thirdProcName) ==
            std::unordered_set<std::string>{firstProcName, secondProcName});

    // Second and Third is called* by First
    REQUIRE(reader.getProcsThatIsCalledByStar(firstProcName) ==
            std::unordered_set<std::string>{secondProcName, thirdProcName});

    // Third is called* by Second
    REQUIRE(reader.getProcsThatIsCalledByStar(secondProcName) ==
            std::unordered_set<std::string>{thirdProcName});

    // No procedure is called* by Third
    REQUIRE(reader.getProcsThatIsCalledByStar(thirdProcName).empty());

    // All call* pairs = (First, Second), (First, Third), (Second, Third)
    REQUIRE(
        reader.getAllCallStarPairs() ==
        std::unordered_set<std::pair<std::string, std::string>, PairHash>{
            std::pair<std::string, std::string>(firstProcName, secondProcName),
            std::pair<std::string, std::string>(firstProcName, thirdProcName),
            std::pair<std::string, std::string>(secondProcName,
                                                thirdProcName)});
  }

  SECTION("Next Relationship") {
    writer.clearPKB();
    // procedure Second {
    //  x = 1;
    //  x = 2;
    //  while (x == 3) {
    //   x = 4;
    //   x = 5;
    //  }
    //  if (x==6) then {
    //   x = 7;
    //  } else {
    //   x = 8;
    //   if (x != 9) then {
    //    x = 10;
    //   } else {
    //    x = 11;
    //   }
    //  }
    //  x = 12;
    //  x = 13;
    // }
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "Second"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "1"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "2"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "3"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "4"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "5"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "6"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "7"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "8"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "9"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "10"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "11"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "12"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::ASSIGN, "="));
    tokens.push_back(std::make_unique<Token>(TokenType::INTEGER, "13"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    DesignExtractor::extract(tokens);

    // next-direction
    REQUIRE(reader.getStmtsNextOf(1) == std::unordered_set<int>{2});
    REQUIRE(reader.getStmtsNextOf(2) == std::unordered_set<int>{3});
    REQUIRE(reader.getStmtsNextOf(3) == std::unordered_set<int>{4, 6});
    REQUIRE(reader.getStmtsNextOf(4) == std::unordered_set<int>{5});
    REQUIRE(reader.getStmtsNextOf(5) == std::unordered_set<int>{3});
    REQUIRE(reader.getStmtsNextOf(6) == std::unordered_set<int>{7, 8});
    REQUIRE(reader.getStmtsNextOf(7) == std::unordered_set<int>{12});
    REQUIRE(reader.getStmtsNextOf(8) == std::unordered_set<int>{9});
    REQUIRE(reader.getStmtsNextOf(9) == std::unordered_set<int>{10, 11});
    REQUIRE(reader.getStmtsNextOf(10) == std::unordered_set<int>{12});
    REQUIRE(reader.getStmtsNextOf(11) == std::unordered_set<int>{12});
    REQUIRE(reader.getStmtsNextOf(12) == std::unordered_set<int>{13});
    REQUIRE(reader.getStmtsNextOf(13).empty());

    // previous-direction
    REQUIRE(reader.getStmtsPreviousOf(1).empty());
    REQUIRE(reader.getStmtsPreviousOf(2) == std::unordered_set<int>{1});
    REQUIRE(reader.getStmtsPreviousOf(3) == std::unordered_set<int>{2, 5});
    REQUIRE(reader.getStmtsPreviousOf(4) == std::unordered_set<int>{3});
    REQUIRE(reader.getStmtsPreviousOf(5) == std::unordered_set<int>{4});
    REQUIRE(reader.getStmtsPreviousOf(6) == std::unordered_set<int>{3});
    REQUIRE(reader.getStmtsPreviousOf(7) == std::unordered_set<int>{6});
    REQUIRE(reader.getStmtsPreviousOf(8) == std::unordered_set<int>{6});
    REQUIRE(reader.getStmtsPreviousOf(9) == std::unordered_set<int>{8});
    REQUIRE(reader.getStmtsPreviousOf(10) == std::unordered_set<int>{9});
    REQUIRE(reader.getStmtsPreviousOf(11) == std::unordered_set<int>{9});
    REQUIRE(reader.getStmtsPreviousOf(12) ==
            std::unordered_set<int>{7, 10, 11});
    REQUIRE(reader.getStmtsPreviousOf(13) == std::unordered_set<int>{12});

    // all next pair
    REQUIRE(reader.getAllNextPairs() ==
            std::unordered_set<std::pair<int, int>, PairHash>{
                std::pair<int, int>(1, 2), std::pair<int, int>(2, 3),
                std::pair<int, int>(3, 4), std::pair<int, int>(3, 6),
                std::pair<int, int>(4, 5), std::pair<int, int>(5, 3),
                std::pair<int, int>(6, 7), std::pair<int, int>(6, 8),
                std::pair<int, int>(7, 12), std::pair<int, int>(8, 9),
                std::pair<int, int>(9, 10), std::pair<int, int>(9, 11),
                std::pair<int, int>(10, 12), std::pair<int, int>(11, 12),
                std::pair<int, int>(12, 13)});

    // all statement that is next of other statements
    REQUIRE(reader.getAllStmtsThatAreNextOfOtherStmts() ==
            std::unordered_set<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13});

    // all stmts that is previous of another statement
    REQUIRE(reader.getAllStmtsThatArePreviousOfOtherStmts() ==
            std::unordered_set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
  }

  SECTION("If ccontrol variable") {
    writer.clearPKB();

    // procedure First {
    //  if ((a == b) && (c != d)) then { // 1
    //   read x; // 2
    //  } else {
    //   print y; // 3
    //  }
    //  if ((c == d) || (e != f)) then { // 4
    //   read x; // 5
    //  } else {
    //   print y; // 6
    //  }
    // }
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "First"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "a"));
    tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "b"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::AND, "&&"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "c"));
    tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "d"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::IF, "if"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "c"));
    tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "d"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::OR, "||"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "e"));
    tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "f"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::THEN, "then"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::ELSE, "else"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::PRINT, "print"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "y"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    DesignExtractor::extract(tokens);

    REQUIRE(reader.getControlVariableOfIfStmt(1) ==
            std::unordered_set<std::string>{"a", "b", "c", "d"});
    REQUIRE(reader.getControlVariableOfIfStmt(4) ==
            std::unordered_set<std::string>{"c", "d", "e", "f"});

    REQUIRE(reader.getIfStmtsThatUseControlVariable("a") ==
            std::unordered_set<int>{1});
    REQUIRE(reader.getIfStmtsThatUseControlVariable("b") ==
            std::unordered_set<int>{1});
    REQUIRE(reader.getIfStmtsThatUseControlVariable("c") ==
            std::unordered_set<int>{1, 4});
    REQUIRE(reader.getIfStmtsThatUseControlVariable("d") ==
            std::unordered_set<int>{1, 4});
    REQUIRE(reader.getIfStmtsThatUseControlVariable("e") ==
            std::unordered_set<int>{4});
    REQUIRE(reader.getIfStmtsThatUseControlVariable("f") ==
            std::unordered_set<int>{4});

    REQUIRE(reader.getAllIfStmtsThatUseControlVariables() ==
            std::unordered_set<int>{1, 4});
    REQUIRE(reader.getAllIfControlVariablePairs() ==
            std::unordered_set<std::pair<int, std::string>, PairHash>{
                std::pair<int, std::string>(1, "a"),
                std::pair<int, std::string>(1, "b"),
                std::pair<int, std::string>(1, "c"),
                std::pair<int, std::string>(1, "d"),
                std::pair<int, std::string>(4, "c"),
                std::pair<int, std::string>(4, "d"),
                std::pair<int, std::string>(4, "e"),
                std::pair<int, std::string>(4, "f"),
            });
    REQUIRE(reader.getAllIfControlVariables() ==
            std::unordered_set<std::string>{"a", "b", "c", "d", "e", "f"});
  }

  SECTION("While ccontrol variable") {
    writer.clearPKB();

    // procedure First {
    //  while ((a == b) && (c != d)) { // 1
    //   read x; // 2
    //  }
    //  while ((c == d) || (e != f)) { // 3
    //   read x; // 4
    //  }
    // }
    std::vector<std::unique_ptr<Token>> tokens;
    tokens.push_back(
        std::make_unique<Token>(TokenType::PROCEDURE, "procedure"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "First"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "a"));
    tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "b"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::AND, "&&"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "c"));
    tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "d"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(std::make_unique<Token>(TokenType::WHILE, "while"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "c"));
    tokens.push_back(std::make_unique<Token>(TokenType::EQ, "=="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "d"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::OR, "||"));
    tokens.push_back(std::make_unique<Token>(TokenType::OPEN_BRACKET, "("));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "e"));
    tokens.push_back(std::make_unique<Token>(TokenType::NEQ, "!="));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "f"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(std::make_unique<Token>(TokenType::CLOSE_BRACKET, ")"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::OPEN_CURLY_BRACKET, "{"));
    tokens.push_back(std::make_unique<Token>(TokenType::READ, "read"));
    tokens.push_back(std::make_unique<Token>(TokenType::NAME, "x"));
    tokens.push_back(std::make_unique<Token>(TokenType::SEMICOLON, ";"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    tokens.push_back(
        std::make_unique<Token>(TokenType::CLOSE_CURLY_BRACKET, "}"));
    DesignExtractor::extract(tokens);

    REQUIRE(reader.getControlVariableOfWhileStmt(1) ==
            std::unordered_set<std::string>{"a", "b", "c", "d"});
    REQUIRE(reader.getControlVariableOfWhileStmt(3) ==
            std::unordered_set<std::string>{"c", "d", "e", "f"});

    REQUIRE(reader.getWhileStmtsThatUseControlVariable("a") ==
            std::unordered_set<int>{1});
    REQUIRE(reader.getWhileStmtsThatUseControlVariable("b") ==
            std::unordered_set<int>{1});
    REQUIRE(reader.getWhileStmtsThatUseControlVariable("c") ==
            std::unordered_set<int>{1, 3});
    REQUIRE(reader.getWhileStmtsThatUseControlVariable("d") ==
            std::unordered_set<int>{1, 3});
    REQUIRE(reader.getWhileStmtsThatUseControlVariable("e") ==
            std::unordered_set<int>{3});
    REQUIRE(reader.getWhileStmtsThatUseControlVariable("f") ==
            std::unordered_set<int>{3});

    REQUIRE(reader.getAllWhileStmtsThatUseControlVariables() ==
            std::unordered_set<int>{1, 3});
    REQUIRE(reader.getAllWhileControlVariablePairs() ==
            std::unordered_set<std::pair<int, std::string>, PairHash>{
                std::pair<int, std::string>(1, "a"),
                std::pair<int, std::string>(1, "b"),
                std::pair<int, std::string>(1, "c"),
                std::pair<int, std::string>(1, "d"),
                std::pair<int, std::string>(3, "c"),
                std::pair<int, std::string>(3, "d"),
                std::pair<int, std::string>(3, "e"),
                std::pair<int, std::string>(3, "f"),
            });
    REQUIRE(reader.getAllWhileControlVariables() ==
            std::unordered_set<std::string>{"a", "b", "c", "d", "e", "f"});
  }

  // Cleanup
  DesignExtractor::resetStmtNumber();
  writer.clearPKB();
}
