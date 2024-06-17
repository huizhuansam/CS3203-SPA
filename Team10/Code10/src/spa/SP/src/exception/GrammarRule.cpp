#include "exception/GrammarRule.h"

namespace SP {
// Reference:
// https://nus-cs3203.github.io/course-website/contents/basic-spa-requirements/simple-programming.html

const std::string GrammarRule::NAME = "NAME: LETTER (LETTER | DIGIT)*";

const std::string GrammarRule::INTEGER = "INTEGER: 0 | NZDIGIT ( DIGIT )*";

const std::string GrammarRule::SYNONYM = "synonym : IDENT";

const std::string GrammarRule::STMT_REF = "stmtRef : synonym | '_' | INTEGER";

const std::string GrammarRule::ENT_REF =
    "entRef : synonym | '_' | '\"' IDENT '\"'";

const std::string GrammarRule::PROGRAM = "program: procedure";

const std::string GrammarRule::PROCEDURE =
    "procedure: 'procedure' proc_name '{' stmtLst '}'";

const std::string GrammarRule::STMT_LIST = "stmtLst: stmt+";

const std::string GrammarRule::STMT =
    "stmt: assign | call | while | if | print | read";

const std::string GrammarRule::READ = "read: 'read' var_name';'";

const std::string GrammarRule::PRINT = "print: 'print' var_name';'";

const std::string GrammarRule::CALL = "call: 'call' proc_name';'";

const std::string GrammarRule::WHILE =
    "while: 'while' '(' cond_expr ')' '{' stmtLst '}'";

const std::string GrammarRule::IF =
    "if: 'if' '(' cond_expr ')' 'then' '{' stmtLst '}' 'else' '{' stmtLst '}'";

const std::string GrammarRule::ASSIGN = "assign: var_name '=' expr ';'";

const std::string GrammarRule::COND_EXPR =
    "cond_expr: rel_expr | '!' '(' cond_expr ')' | '(' cond_expr ')' '&&' '(' "
    "cond_expr ')' | '(' cond_expr ')' '||' '(' cond_expr ')'";

const std::string GrammarRule::REL_EXPR =
    "rel_expr: rel_factor '>' rel_factor | rel_factor '>=' rel_factor | "
    "rel_factor '<' rel_factor | rel_factor '<=' rel_factor | rel_factor '==' "
    "rel_factor | rel_factor '!=' rel_factor";

const std::string GrammarRule::REL_FACTOR =
    "rel_factor: var_name | const_value | expr";

const std::string GrammarRule::EXPR =
    "expr: expr '+' term | expr '-' term | term";

const std::string GrammarRule::TERM =
    "term: term '*' factor | term '/' factor | term '%' factor | factor";

const std::string GrammarRule::FACTOR =
    "factor: var_name | const_value | '(' expr ')'";

const std::string GrammarRule::VAR_NAME = "var_name: NAME";

const std::string GrammarRule::PROC_NAME = "proc_name: NAME";

const std::string GrammarRule::CONST_VALUE = "const_value: INTEGER";

const std::string GrammarRule::STMT_NO = "stmt#: NZDIGIT ( DIGIT )*";
}  // namespace SP
