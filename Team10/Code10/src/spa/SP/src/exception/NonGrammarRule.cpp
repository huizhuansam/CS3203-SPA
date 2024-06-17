#include "exception/NonGrammarRule.h"

namespace SP {
// Reference:
// https://nus-cs3203.github.io/course-website/contents/basic-spa-requirements/simple-programming.html

const std::string NonGrammarRule::NO_DUP_PROC =
    "A program cannot have two procedures with the same name";

const std::string NonGrammarRule::NO_CALL_TO_UNDEF_PROC =
    "A procedure cannot call a non-existing procedure";

const std::string NonGrammarRule::NO_RECURSIVE_OR_CYCLIC_CALL =
    "Recursive and cyclic calls are not allowed";
}  // namespace SP
