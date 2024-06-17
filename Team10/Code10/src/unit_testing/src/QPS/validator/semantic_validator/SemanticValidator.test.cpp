#include "validator/semantic_validator/SemanticValidator.h"

#include "../src/spa/QPS/include/exception/NonGrammarRule.h"
#include "catch.hpp"

using namespace QPS;

SemanticValidator validator;

TEST_CASE("No duplicate synonym", "[SemanticValidator]") {
  SECTION("Same synonym same type") {
    // procedure p, p;
    // Select p
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "procedure"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "p"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();

    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::NO_DUP_SYNONYM);
  }

  SECTION("Same synonym different types") {
    // variable v; assign v;
    // Select v
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "v"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();

    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::NO_DUP_SYNONYM);
  }
}

TEST_CASE("All synonym is declared exactly once", "[SemanticValidator]") {
  SECTION("Undeclared synonym in select clause") {
    // if ifs;
    // Select v
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "if"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "v"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();

    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ALL_SYNONYM_DECLARED);
  }

  SECTION("Undeclared synonym in relation clause") {
    // while w;
    // Select w such that Follows(w, a)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "while"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Follows"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();

    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ALL_SYNONYM_DECLARED);
  }

  SECTION("Undeclared synonym in pattern clause") {
    // read re;
    // Select re pattern w(v, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "read"),
        std::make_shared<Token>(TokenType::NAME, "re"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "re"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();

    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ALL_SYNONYM_DECLARED);
  }
}

TEST_CASE("syn-assign is declared as a synonym of an assignment",
          "[SemanticValidator]") {
  SECTION("Expect assign but synonym type not matches") {
    // stmt s; stmt a;
    // Select s pattern a(_, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();

    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::VALID_PATTERN_SYN);
  }

  SECTION("Assign pattern exact matching but wrong synonym type") {
    // variable v;
    // Select v pattern v(v, "v")
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::VALID_PATTERN_SYN);
  }

  SECTION("Assign pattern partial matching but wrong synonym type") {
    // variable v;
    // Select v pattern v(v, _"v"_)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::VALID_PATTERN_SYN);
  }

  SECTION("Assign pattern but has three arguments") {
    // assign a;
    // Select a pattern a(_, _, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::SYN_ASSIGN_IS_ASSIGN);
  }
}

TEST_CASE("syn-while is declared as a synonym of while statement",
          "[SemanticValidator]") {
  SECTION("While pattern but wrong synonym type") {
    // procedure p;
    // Select p pattern p(_, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "procedure"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::VALID_PATTERN_SYN);
  }

  SECTION("While pattern but has three arguments") {
    // while w;
    // Select w pattern w(_, _, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "while"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::SYN_WHILE_IS_WHILE);
  }

  SECTION("While pattern but second argument is not wildcard") {
    // while w;
    // Select w pattern w(_, "v")
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "while"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::SYN_WHILE_IS_WHILE);
  }
}

TEST_CASE("syn-if is declared as a synonym of if statement",
          "[SemanticValidator]") {
  SECTION("If pattern but wrong synonym type") {
    // read r;
    // Select r pattern r(_, _, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "read"),
        std::make_shared<Token>(TokenType::NAME, "r"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "r"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "r"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::VALID_PATTERN_SYN);
  }

  SECTION("If pattern but has two arguments only") {
    // if ifs;
    // Select ifs pattern ifs(_, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "if"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::SYN_IF_IS_IF);
  }

  SECTION("If pattern but second argument is not wildcard") {
    // if ifs;
    // Select ifs pattern ifs(_, "v", _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "if"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::SYN_IF_IS_IF);
  }

  SECTION("If pattern but third argument is not wildcard") {
    // if ifs; variable v;
    // Select ifs pattern ifs(_, _, "v")
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "if"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::SYN_IF_IS_IF);
  }
}

TEST_CASE("The first argument for Modifies and Uses cannot be _",
          "[SemanticValidator]") {
  SECTION("Modifies first argument is _") {
    // stmt s; assign a;
    // Select s such that Modifies(_, "a")
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Modifies"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();

    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::FIRST_ARG_NOT_WILDCARD);
  }

  SECTION("Uses first argument is _") {
    // stmt s; assign a;
    // Select s such that Uses(_, "a")
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Uses"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();

    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::FIRST_ARG_NOT_WILDCARD);
  }
}

TEST_CASE("Synonym match design entity for relationship argument",
          "[SemanticValidator]") {
  SECTION("Parent first argument is not statement or its subtypes") {
    // variable v;
    // Select v such that Parent(v, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Parent"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ARG_ENTITY_MATCH_RELATION);
  }

  SECTION("Follows* first argument is not statement or its subtypes") {
    // variable v;
    // Select v such that Follows*(v, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Follows*"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ARG_ENTITY_MATCH_RELATION);
  }

  SECTION("Modifies second argument is not variable") {
    // print pn;
    // Select pn such that Modifies(3, pn)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "print"),
        std::make_shared<Token>(TokenType::NAME, "pn"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "pn"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Modifies"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "pn"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ARG_ENTITY_MATCH_RELATION);
  }

  SECTION("Uses second argument is not variable") {
    // print pn;
    // Select pn such that Uses(3, pn)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "print"),
        std::make_shared<Token>(TokenType::NAME, "pn"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "pn"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Uses"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "pn"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ARG_ENTITY_MATCH_RELATION);
  }

  SECTION("Next first argument is not statement or its subtypes") {
    // variable v;
    // Select v such that Next(v, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Next"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ARG_ENTITY_MATCH_RELATION);
  }

  SECTION("Affects first argument is not statement or its subtypes") {
    // variable v;
    // Select v such that Affects(v, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Affects"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ARG_ENTITY_MATCH_RELATION);
  }

  SECTION("Affects second argument is not statement or its subtypes") {
    // stmt s; variable v;
    // Select v such that Affects(s, v)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Affects"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ARG_ENTITY_MATCH_RELATION);
  }

  SECTION("Calls first argument is not procedure") {
    // stmt p; procedure q;
    // Select p such that Calls(p, q)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "procedure"),
        std::make_shared<Token>(TokenType::NAME, "q"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Calls"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "q"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ARG_ENTITY_MATCH_RELATION);
  }

  SECTION("Calls* second argument is not procedure") {
    // procedure p; print q;
    // Select p such that Calls*(p, q)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "procedure"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "print"),
        std::make_shared<Token>(TokenType::NAME, "q"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Calls*"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "q"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ARG_ENTITY_MATCH_RELATION);
  }
}

TEST_CASE("Synonym match design entity for pattern argument",
          "[SemanticValidator]") {
  SECTION("Pattern first argument is not variable") {
    // constant c; assign a;
    // Select c pattern a(c, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "constant"),
        std::make_shared<Token>(TokenType::NAME, "c"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "c"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "c"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ARG_ENTITY_MATCH_PATTERN);
  }
}

TEST_CASE("Attribute name must be of acceptable attribute of synonym",
          "[SemanticValidator]") {
  SECTION("Matched attribute name") {
    // variable v;
    // Select v.varName
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "varName"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Synonym with unmatched attribute name") {
    // assign a;
    // Select a.varName
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "varName"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::SYNONYM_MATCH_ATTR_NAME);
  }

  SECTION("Matched attribute name in tuple query") {
    // while w;
    // Select <w, w.stmt#>
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "while"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "stmt#"),
        std::make_shared<Token>(TokenType::CLOSE_ANGLE_BRACKET, ">"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Synonym with unmatched attribute name in tuple query") {
    // constant cnst;
    // Select <cnst.procName>
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "constant"),
        std::make_shared<Token>(TokenType::NAME, "cnst"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "cnst"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "procName"),
        std::make_shared<Token>(TokenType::CLOSE_ANGLE_BRACKET, ">"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::SYNONYM_MATCH_ATTR_NAME);
  }

  SECTION("Synonym with unmatched attribute name in with clause") {
    // variable v;
    // Select v with v.stmt# = 7
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "variable"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::NAME, "with"),
        std::make_shared<Token>(TokenType::NAME, "v"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "stmt#"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::INTEGER, "7"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::SYNONYM_MATCH_ATTR_NAME);
  }

  SECTION("Name compare with integer in with clause") {
    // print pn;
    // Select pn with pn.varName = 3
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "print"),
        std::make_shared<Token>(TokenType::NAME, "pn"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "pn"),
        std::make_shared<Token>(TokenType::NAME, "with"),
        std::make_shared<Token>(TokenType::NAME, "pn"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "varName"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::INTEGER, "3"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ATTR_NAME_MATCH_COMPARE_VALUE);
  }

  SECTION("Integer compare with name in with clause") {
    // call c;
    // Select c with 3 = c.procName
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "call"),
        std::make_shared<Token>(TokenType::NAME, "c"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "c"),
        std::make_shared<Token>(TokenType::NAME, "with"),
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::NAME, "c"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "procName"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ATTR_NAME_MATCH_COMPARE_VALUE);
  }

  SECTION("Unmatched comparison in with clause without synonym") {
    // stmt s;
    // Select BOOLEAN with 3 = "x"
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
        std::make_shared<Token>(TokenType::NAME, "with"),
        std::make_shared<Token>(TokenType::INTEGER, "3"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::ATTR_NAME_MATCH_COMPARE_VALUE);
  }
}

TEST_CASE("No exception thrown for semantically valid query",
          "[SemanticValidator]") {
  SECTION("No synonym in relation") {
    // procedure p;
    // Select p such that Parent(1, 2)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "procedure"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Parent"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::INTEGER, "1"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::INTEGER, "2"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("No synonym in pattern") {
    // procedure p; assign a;
    // Select p pattern a("x", _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "procedure"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Declared but never used") {
    // if ifs; while w, w1, w2, w3;
    // Select ifs
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "if"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "while"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "w1"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "w2"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "w3"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Multiple clause with some clause having NOT and AND") {
    // stmt s; assign a;
    // Select s such that Follows(s, a) and not Modifies(s, "x") and Uses(a,
    // "y")
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Follows"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "not"),
        std::make_shared<Token>(TokenType::NAME, "Modifies"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "Uses"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "y"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Calls relation uses procedure for synonym and procedure name") {
    // procedure p;
    // Select p such that Calls(p, "q")
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "procedure"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Calls"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "p"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "q"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Calls relation uses wildcard and procedure for synonym") {
    // procedure q;
    // Select q such that Calls*(_, q)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "procedure"),
        std::make_shared<Token>(TokenType::NAME, "q"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "q"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Calls*"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "q"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Calls relation uses two procedure names") {
    // stmt s;
    // Select s such that Calls("proc1", "proc2")
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Calls"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "proc1"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "proc2"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Calls relation uses two wildcards") {
    // stmt s;
    // Select s such that Calls(_, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "s"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Calls"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("BOOLEAN declared as synonym") {
    // stmt BOOLEAN;
    // Select BOOLEAN
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("BOOLEAN declared as synonym in tuple query") {
    // stmt BOOLEAN;
    // Select <BOOLEAN.stmt#>
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::OPEN_ANGLE_BRACKET, "<"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "stmt#"),
        std::make_shared<Token>(TokenType::CLOSE_ANGLE_BRACKET, ">"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Statement subtypes used in Affects arguments") {
    // print pn; read r;
    // Select r such that Affects(pn, r)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "print"),
        std::make_shared<Token>(TokenType::NAME, "pn"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "read"),
        std::make_shared<Token>(TokenType::NAME, "r"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "r"),
        std::make_shared<Token>(TokenType::NAME, "such"),
        std::make_shared<Token>(TokenType::NAME, "that"),
        std::make_shared<Token>(TokenType::NAME, "Affects"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "pn"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::NAME, "r"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("With clause having ident") {
    // assign a;
    // Select a with "x" = "y"
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::NAME, "with"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "y"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("With clause having integer") {
    // assign a;
    // Select a with a.stmt# = 5
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::NAME, "with"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "stmt#"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::INTEGER, "5"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("With clause having attrRef") {
    // call c;
    // Select c with c.procName = "proc1"
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "call"),
        std::make_shared<Token>(TokenType::NAME, "c"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "c"),
        std::make_shared<Token>(TokenType::NAME, "with"),
        std::make_shared<Token>(TokenType::NAME, "c"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "procName"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "proc1"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("With clause with NOT") {
    // assign a;
    // Select a with not a.stmt# = 5
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::NAME, "with"),
        std::make_shared<Token>(TokenType::NAME, "not"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "stmt#"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::INTEGER, "5"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Multiple with clause with AND") {
    // assign a; call c;
    // Select a with a.stmt# = 5 and c.procName = "x"
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "call"),
        std::make_shared<Token>(TokenType::NAME, "c"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::NAME, "with"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "stmt#"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::INTEGER, "5"),
        std::make_shared<Token>(TokenType::NAME, "and"),
        std::make_shared<Token>(TokenType::NAME, "c"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "procName"),
        std::make_shared<Token>(TokenType::EQ, "="),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Valid assign pattern") {
    // assign a;
    // Select a pattern a(_, _"x"_)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Valid assign pattern with second argument as wildcard") {
    // assign a;
    // Select a pattern a(_, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Valid while pattern") {
    // while w;
    // Select w pattern w(_, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "while"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "w"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Valid if pattern") {
    // if ifs;
    // Select ifs pattern ifs(_, _, _)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "if"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "ifs"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Complex pattern clause with partial matching") {
    // assign a;
    // Select a pattern a(_, _"(x + 5) % 2"_)
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::INTEGER, "5"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::MOD, "%"),
        std::make_shared<Token>(TokenType::INTEGER, "2"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Complex pattern clause with exact matching") {
    // assign a;
    // Select a pattern a(_, "(x + 5) % 2")
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "assign"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::NAME, "pattern"),
        std::make_shared<Token>(TokenType::NAME, "a"),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::WILDCARD, "_"),
        std::make_shared<Token>(TokenType::COMMA, ","),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::OPEN_BRACKET, "("),
        std::make_shared<Token>(TokenType::NAME, "x"),
        std::make_shared<Token>(TokenType::PLUS, "+"),
        std::make_shared<Token>(TokenType::INTEGER, "5"),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
        std::make_shared<Token>(TokenType::MOD, "%"),
        std::make_shared<Token>(TokenType::INTEGER, "2"),
        std::make_shared<Token>(TokenType::DOUBLE_QUOTE, "\""),
        std::make_shared<Token>(TokenType::CLOSE_BRACKET, ")"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }
}

TEST_CASE("Select BOOLEAN...") {
  SECTION("Undeclared BOOLEAN used as synonym with attribute") {
    // Select BOOLEAN.stmt#
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "stmt#"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_THROWS_WITH(validator.validate(it, end),
                        NonGrammarRule::BOOLEAN_WITH_ATTR);
  }

  SECTION("BOOLEAN used as synonym with attribute") {
    // stmt BOOLEAN.stmt#;
    // Select BOOLEAN.stmt#
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
        std::make_shared<Token>(TokenType::PERIOD, "."),
        std::make_shared<Token>(TokenType::ATTR_NAME, "stmt#"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("Plain old Select BOOLEAN") {
    // Select BOOLEAN
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }

  SECTION("BOOLEAN used as synonym") {
    // Select BOOLEAN
    std::vector<std::shared_ptr<Token>> tokens = {
        std::make_shared<Token>(TokenType::NAME, "stmt"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
        std::make_shared<Token>(TokenType::SEMICOLON, ";"),
        std::make_shared<Token>(TokenType::NAME, "Select"),
        std::make_shared<Token>(TokenType::NAME, "BOOLEAN"),
    };
    auto it = tokens.begin();
    auto end = tokens.end();
    REQUIRE_NOTHROW(validator.validate(it, end));
  }
}
