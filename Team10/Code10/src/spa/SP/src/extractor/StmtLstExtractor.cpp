#include "StmtLstExtractor.h"

#include <cassert>

#include "DesignExtractor.h"
#include "GrammarRule.h"
#include "IStmtExtractor.h"
#include "IStmtExtractorFactory.h"
#include "WriteFacade.h"
#include "tokenizer/Token.h"

namespace SP {
StmtLstExtractor::StmtLstExtractor(WriteFacade& writer)
    : writer(writer), containerStmtNo(0) {}

StmtLstExtractor::StmtLstExtractor(WriteFacade& writer, int containerStmtNo)
    : writer(writer), containerStmtNo(containerStmtNo) {}

int StmtLstExtractor::getFirstStmtNo() { return this->firstStmtNo; }

int StmtLstExtractor::getLastStmtNo() { return this->lastStmtNo; }

std::vector<int>& StmtLstExtractor::getNonNestedStmtNo() {
  return this->nonNestedStmtNo;
}

std::unordered_set<std::string>& StmtLstExtractor::getVarModified() {
  return this->varModified;
}

std::unordered_set<std::string>& StmtLstExtractor::getVarUsed() {
  return this->varUsed;
}

std::unordered_set<std::string>& StmtLstExtractor::getProcCalled() {
  return this->procCalled;
}

std::unordered_map<int, std::unordered_set<std::string>>&
StmtLstExtractor::getStmtCallMap() {
  return this->stmtCallMap;
}

std::unordered_set<int> StmtLstExtractor::getLastExecutedStmtNumbers() {
  return this->lastExecutedStmtNumbers;
}

void StmtLstExtractor::extract(
    std::vector<std::unique_ptr<Token>>::iterator& it,
    const std::vector<std::unique_ptr<Token>>::iterator& end) {
  int stmtNumberBeforeParsing = DesignExtractor::getStmtNumber();
  // if not created through "if" / "while" statement, then containerStmtNo = 0
  std::unordered_set<int> lastStmtNumbersBefore = {containerStmtNo};
  while ((*it)->getType() != TokenType::CLOSE_CURLY_BRACKET) {
    int stmtNumberBeforeNextStmt = DesignExtractor::getStmtNumber();
    std::unique_ptr<IStmtExtractor> stmtExtractor =
        IStmtExtractorFactory::of(it, this->writer);
    stmtExtractor->extract(it, end);

    // add non-nested stmt number
    int currentStmtNo = stmtNumberBeforeNextStmt + 1;
    this->nonNestedStmtNo.push_back(currentStmtNo);

    // process next relationship
    for (const auto& lastStmtNumberBefore : lastStmtNumbersBefore) {
      if (lastStmtNumberBefore != 0) {
        // not the first stmt in the list
        this->writer.insertNextRelationship(lastStmtNumberBefore,
                                            currentStmtNo);
      }
    }

    lastStmtNumbersBefore = stmtExtractor->getLastExecutedStmtNumbers();
    this->lastExecutedStmtNumbers = lastStmtNumbersBefore;
    stmtExtractor->dumpContentsInto(*this, currentStmtNo);
  }

  this->firstStmtNo = stmtNumberBeforeParsing + 1;
  this->lastStmtNo = DesignExtractor::getStmtNumber();
  this->processFollowsRelationship();
}

void StmtLstExtractor::processFollowsRelationship() {
  assert(!nonNestedStmtNo.empty() && "nonNestedStmtNo is empty");

  // Direct Follows relationship
  auto currStmtNo = this->nonNestedStmtNo.front();
  for (auto nextStmtNo = std::next(this->nonNestedStmtNo.begin());
       nextStmtNo != this->nonNestedStmtNo.end(); ++nextStmtNo) {
    this->writer.insertDirectFollowsRelationship(currStmtNo, *nextStmtNo);
    currStmtNo = *nextStmtNo;
  }

  // Follows* relationship
  for (auto leader = this->nonNestedStmtNo.begin();
       leader != this->nonNestedStmtNo.end(); ++leader) {
    for (auto follower = std::next(leader);
         follower != this->nonNestedStmtNo.end(); ++follower) {
      this->writer.insertFollowsStarRelationship(*leader, *follower);
    }
  }
}

void StmtLstExtractor::addVarUsedByStmt(
    std::unordered_set<std::string>& varUsedByStmt) {
  for (const auto& var : varUsedByStmt) {
    this->varUsed.insert(var);
  }
}

void StmtLstExtractor::addVarModifiedByStmt(
    std::unordered_set<std::string>& varModifiedByStmt) {
  for (const auto& var : varModifiedByStmt) {
    this->varModified.insert(var);
  }
}

void StmtLstExtractor::addToStmtCallMap(
    int currentStmtNo, std::unordered_set<std::string>& procCalledByStmt) {
  for (const auto& proc : procCalledByStmt) {
    this->stmtCallMap[currentStmtNo].insert(proc);
  }
}

void StmtLstExtractor::appendToStmtCallMap(
    std::unordered_map<int, std::unordered_set<std::string>>& map) {
  for (const auto& [key, value] : map) {
    this->stmtCallMap[key].insert(value.begin(), value.end());
  }
}

void StmtLstExtractor::addProcCalledByStmt(
    std::unordered_set<std::string>& procCalledByStmt) {
  for (const auto& proc : procCalledByStmt) {
    this->procCalled.insert(proc);
  }
}
}  // namespace SP
