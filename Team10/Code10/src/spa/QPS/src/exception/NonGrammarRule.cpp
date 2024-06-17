#include "exception/NonGrammarRule.h"

namespace QPS {
// Reference:
// https://nus-cs3203.github.io/course-website/contents/basic-spa-requirements/program-query-language/introduction.html

const std::string NonGrammarRule::NO_DUP_SYNONYM =
    "A synonym name can only be declared once";

const std::string NonGrammarRule::ALL_SYNONYM_DECLARED =
    "All the synonyms used in clauses must be declared exactly once";

const std::string NonGrammarRule::SYN_ASSIGN_IS_ASSIGN =
    "`syn-assign` must be declared as a synonym of an assignment (design "
    "entity `assign`)";

const std::string NonGrammarRule::FIRST_ARG_NOT_WILDCARD =
    "The first argument for `Modifies` and `Uses` cannot be `_`, as it is "
    "unclear whether `_` refers to a statement or procedure";

const std::string NonGrammarRule::ARG_ENTITY_MATCH_RELATION =
    "Synonyms of design entities can appear as relationship arguments, and "
    "should match the design entity defined for the relationship";

const std::string NonGrammarRule::ARG_ENTITY_MATCH_PATTERN =
    "Synonyms of design entities can appear as arguments in pattern "
    "clauses, and should match the design entity defined for pattern clauses";

const std::string NonGrammarRule::SYNONYM_MATCH_ATTR_NAME =
    "The attrName must be of acceptable attribute of synonym";

const std::string NonGrammarRule::ATTR_NAME_MATCH_COMPARE_VALUE =
    "For attrCompare, the two ref comparison must be of the same type (both "
    "NAME, or both INTEGER)";

const std::string NonGrammarRule::SYN_WHILE_IS_WHILE =
    "syn-while must be declared as a synonym of an while-statement (design "
    "entity while)";

const std::string NonGrammarRule::SYN_IF_IS_IF =
    "syn-if must be declared as a synonym of an if-statement (design entity "
    "if)";

const std::string NonGrammarRule::VALID_PATTERN_SYN =
    "synonym for pattern must be either assign, while, or if stmt";

const std::string NonGrammarRule::BOOLEAN_WITH_ATTR =
    "BOOLEAN cannot have attributes unless declared as a synonym";
}  // namespace QPS
