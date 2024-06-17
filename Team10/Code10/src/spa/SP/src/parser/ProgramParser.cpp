#include "ProgramParser.h"

#include <stack>
#include <unordered_map>
#include <unordered_set>

#include "GrammarRule.h"
#include "NonGrammarRule.h"
#include "ProcedureParser.h"
#include "SemanticError.h"
#include "SyntaxError.h"

namespace SP {
void ProgramParser::parse(std::vector<std::unique_ptr<Token>>::iterator& it,
                          std::vector<std::unique_ptr<Token>>::iterator& end) {
  // program: procedure
  if (it == end) {
    throw SyntaxError(GrammarRule::PROGRAM);
  }

  std::unordered_set<std::string> procedureNames;
  std::unordered_map<std::string, std::unordered_set<std::string>>
      procToProcCalls;

  while (it != end) {
    ProcedureParser procParser{};
    procParser.parse(it, end);

    // handle semantic error: duplicate procedure name
    std::string procedureName = procParser.getProcedureName();
    if (procedureNames.count(procedureName) != 0) {
      throw SemanticError(NonGrammarRule::NO_DUP_PROC);
    }
    procedureNames.insert(procedureName);

    // add proc to proc calls
    std::unordered_set<std::string> procCalledSet =
        procParser.getProcCalledSet();
    for (const std::string& procCalled : procCalledSet) {
      procToProcCalls[procedureName].insert(procCalled);
    }
  }

  // check for semantic errors related to procedure calls
  for (const auto& procToProcCall : procToProcCalls) {
    std::string procToCheck = procToProcCall.first;
    checkProcedureCallSemanticError(procToProcCalls, procedureNames,
                                    procToCheck);
  }
}

void ProgramParser::checkProcedureCallSemanticError(
    std::unordered_map<std::string, std::unordered_set<std::string>>
        procToProcCalls,
    std::unordered_set<std::string> procedureNames, std::string& startProc) {
  std::unordered_set<std::string> visited;
  std::unordered_map<std::string, std::string>
      caller;  // To track the caller of each procName
  std::stack<std::string> stack;
  stack.push(startProc);
  caller[startProc] = "";  // Start procName has no caller

  while (!stack.empty()) {
    std::string procName = stack.top();
    stack.pop();

    if (visited.find(procName) == visited.end()) {
      visited.insert(procName);

      // handle semantic error: call to non-existent procedure
      if (procedureNames.find(procName) == procedureNames.end()) {
        throw SemanticError(NonGrammarRule::NO_CALL_TO_UNDEF_PROC);
      }

      std::unordered_set<std::string> allProcCalled;
      if (procToProcCalls.find(procName) != procToProcCalls.end()) {
        allProcCalled = procToProcCalls.at(procName);
      }

      // handle semantic error: cyclic or recursive call
      // Add procedures called by the current procName to the stack
      for (const auto& procCalled : allProcCalled) {
        if (procCalled == startProc) {
          throw SemanticError(NonGrammarRule::NO_RECURSIVE_OR_CYCLIC_CALL);
        }

        if (visited.find(procCalled) == visited.end()) {
          stack.push(procCalled);
          caller[procCalled] = procName;  // Set caller of the proc called
        }
      }
    }
  }
}
}  // namespace SP
