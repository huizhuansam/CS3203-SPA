#include "exception/GrammarRule.h"

namespace QPS {
// Reference:
// https://nus-cs3203.github.io/course-website/contents/basic-spa-requirements/program-query-language/introduction.html

const std::string GrammarRule::NAME = "NAME: LETTER (LETTER | DIGIT)*";

const std::string GrammarRule::INTEGER = "INTEGER: 0 | NZDIGIT ( DIGIT )*";

const std::string GrammarRule::ATTR_NAME =
    "attrName : 'procName'| 'varName' | 'value' | 'stmt#'";

const std::string GrammarRule::SELECT_CL =
    "declaration* 'Select' result-cl ( suchthat-cl | pattern-cl | with-cl)*";

const std::string GrammarRule::DECLARATION =
    "declaration : design-entity synonym (',' synonym)* ';'";

const std::string GrammarRule::RESULT_CL = "result-cl : tuple | 'BOOLEAN'";

const std::string GrammarRule::TUPLE =
    "tuple : elem | '<' elem ( ',' elem )* '>'";

const std::string GrammarRule::DESIGN_ENTITY =
    "design-entity : 'stmt' | 'read' | 'print' | 'call' | 'while' |\n"
    "                'if' | 'assign' | 'variable' | 'constant' | 'procedure'";

const std::string GrammarRule::SUCHTHAT_CL =
    "suchthat-cl : 'such' 'that' relCond";

const std::string GrammarRule::WITH_CL = "with-cl : 'with' attrCond";

const std::string GrammarRule::ATTR_COND =
    "[ 'not' ] attrCompare ( 'and' [ 'not' ] attrCompare )*";

const std::string GrammarRule::ATTR_COMPARE = "ref '=' ref";

const std::string GrammarRule::REF =
    "ref : '\"' IDENT '\"' | INTEGER | attrRef";

const std::string GrammarRule::REL_COND =
    "relCond : [ 'not' ] relRef ( 'and' [ 'not' ] relRef )*";

const std::string GrammarRule::REL_REF =
    "relRef : Follows | FollowsT | Parent | ParentT | UsesS | "
    "UsesP | ModifiesS | ModifiesP";

const std::string GrammarRule::FOLLOWS =
    "Follows : 'Follows' '(' stmtRef ',' stmtRef ')'";

const std::string GrammarRule::FOLLOWS_T =
    "FollowsT : 'Follows*' '(' stmtRef ',' stmtRef ')'";

const std::string GrammarRule::PARENT =
    "Parent : 'Parent' '(' stmtRef ',' stmtRef ')'";

const std::string GrammarRule::PARENT_T =
    "ParentT : 'Parent*' '(' stmtRef ',' stmtRef ')'";

const std::string GrammarRule::USES_S =
    "UsesS : 'Uses' '(' stmtRef ',' entRef ')'";

const std::string GrammarRule::USES_P =
    "UsesP : 'Uses' '(' entRef ',' entRef ')'";

const std::string GrammarRule::MODIFIES_S =
    "ModifiesS : 'Modifies' '(' stmtRef ',' entRef ')'";

const std::string GrammarRule::MODIFIES_P =
    "ModifiesP : 'Modifies' '(' entRef ',' entRef ')'";

const std::string GrammarRule::PATTERN_CL =
    "pattern-cl : 'pattern' patternCond";

const std::string GrammarRule::PATTERN_COND =
    "patternCond : [ 'not' ] pattern ( 'and' [ 'not' ] pattern )*";

const std::string GrammarRule::PATTERN = "pattern : assign | while | if";

const std::string GrammarRule::EXPRESSION_SPEC =
    R"(expression-spec :  '"' expr'"' | '_' '"' expr '"' '_' | '_')";

const std::string GrammarRule::EXPR =
    "expr: expr '+' term | expr '-' term | term";

const std::string GrammarRule::TERM =
    "term: term '*' factor | term '/' factor | term '%' factor | factor";

const std::string GrammarRule::FACTOR =
    "factor: var_name | const_value | '(' expr ')'";

const std::string GrammarRule::SYN_ASSIGN = "syn-assign : IDENT";

const std::string GrammarRule::VAR_NAME = "var_name : NAME";

const std::string GrammarRule::CONSTANT_VALUE = "const_value : INTEGER";

const std::string GrammarRule::ASSIGN =
    "assign: syn-assign '(' entRef ',' expression-spec ')'";

const std::string GrammarRule::WHILE =
    "while : syn-while '(' entRef ',' '_' ')'";

const std::string GrammarRule::IF = "syn-if '(' entRef ',' '_' ',' '_' ')''";

const std::string GrammarRule::ENT_REF = "synonym | '_' | '\"' IDENT '\"'";
}  // namespace QPS
