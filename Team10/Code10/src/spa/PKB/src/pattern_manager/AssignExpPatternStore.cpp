#include "pattern_manager/AssignExpPatternStore.h"

void AssignExpPatternStore::addExp(
    int stmtNo, const std::string& var,
    const std::vector<std::string>& infixTokens) {
  std::pair<std::string, std::string> key =
      std::make_pair(std::to_string(stmtNo), var);

  assignExps.insert({key, infixToPostfix(infixTokens)});
}

void AssignExpPatternStore::clear() { assignExps.clear(); }

std::unordered_set<std::pair<std::string, std::string>, PairHash>
AssignExpPatternStore::getAllExpPairs() {
  std::unordered_set<std::pair<std::string, std::string>, PairHash> pairs;

  for (const auto& e : assignExps) {
    pairs.insert(e.first);
  }

  return pairs;
};

std::unordered_set<std::pair<std::string, std::string>, PairHash>
AssignExpPatternStore::getExpPairsPartialMatch(
    const std::string& var, const std::vector<std::string>& infixTokens) {
  std::unordered_set<std::pair<std::string, std::string>, PairHash> pairs;

  std::vector<std::string> postfixTokens = infixToPostfix(infixTokens);

  for (const auto& e : assignExps) {
    if (e.first.second == var && isSubVector(e.second, postfixTokens)) {
      pairs.insert(e.first);
    }
  }

  return pairs;
}

std::unordered_set<std::pair<std::string, std::string>, PairHash>
AssignExpPatternStore::getExpPairsSynonymPartialMatch(
    const std::vector<std::string>& infixTokens) {
  std::unordered_set<std::pair<std::string, std::string>, PairHash> pairs;

  std::vector<std::string> postfixTokens = infixToPostfix(infixTokens);

  for (const auto& e : assignExps) {
    if (isSubVector(e.second, postfixTokens)) {
      pairs.insert(e.first);
    }
  }

  return pairs;
};

std::unordered_set<std::pair<std::string, std::string>, PairHash>
AssignExpPatternStore::getExpPairsExactMatch(
    const std::string& var, const std::vector<std::string>& infixTokens) {
  std::unordered_set<std::pair<std::string, std::string>, PairHash> pairs;

  std::vector<std::string> postfixTokens = infixToPostfix(infixTokens);

  for (const auto& e : assignExps) {
    if (e.first.second == var && isExactMatch(e.second, postfixTokens)) {
      pairs.insert(e.first);
    }
  }

  return pairs;
}

std::unordered_set<std::pair<std::string, std::string>, PairHash>
AssignExpPatternStore::getExpPairsSynonymExactMatch(
    const std::vector<std::string>& infixTokens) {
  std::unordered_set<std::pair<std::string, std::string>, PairHash> pairs;

  std::vector<std::string> postfixTokens = infixToPostfix(infixTokens);

  for (const auto& e : assignExps) {
    if (isExactMatch(e.second, postfixTokens)) {
      pairs.insert(e.first);
    }
  }

  return pairs;
};

// Function to convert infix expression to postfix expression,
// using Shunting Yard Algorithm
std::vector<std::string> AssignExpPatternStore::infixToPostfix(
    const std::vector<std::string>& infixTokens) {
  std::vector<std::string> postfixTokens;
  std::stack<std::string> operatorStack;

  for (auto token : infixTokens) {
    if (isAlphanumeric(token)) {
      postfixTokens.push_back(token);
    } else if (token == "(") {
      operatorStack.push(token);
    } else if (token == ")") {
      while (!operatorStack.empty() && operatorStack.top() != "(") {
        postfixTokens.push_back(operatorStack.top());
        operatorStack.pop();
      }
      operatorStack.pop();  // Discard the '('
    } else if (isArithmeticOperator(token)) {
      while (!operatorStack.empty() &&
             precedence(operatorStack.top()) >= precedence(token)) {
        postfixTokens.push_back(operatorStack.top());
        operatorStack.pop();
      }
      operatorStack.push(token);
    }
  }

  while (!operatorStack.empty()) {
    postfixTokens.push_back(operatorStack.top());
    operatorStack.pop();
  }

  return postfixTokens;
}

// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/aa82bf6b-8a80-4cc8-97d0-371119c5ef4d
bool AssignExpPatternStore::isAlphanumeric(const std::string& str) {
  return std::all_of(str.begin(), str.end(),
                     [](unsigned char c) { return std::isalnum(c); });
}
// ai-gen end

bool AssignExpPatternStore::isArithmeticOperator(const std::string& str) {
  return str == "+" || str == "-" || str == "*" || str == "/" || str == "%";
}

int AssignExpPatternStore::precedence(const std::string& str) {
  if (str == "*" || str == "/" || str == "%") {
    return 2;
  } else if (str == "+" || str == "-") {
    return 1;
  } else {
    return 0;
  }
}

bool AssignExpPatternStore::isSubVector(
    const std::vector<std::string>& largerVector,
    const std::vector<std::string>& smallerVector) {
  if (smallerVector.empty()) {
    // An empty vector is always a subvector
    return true;
  }

  if (largerVector.size() < smallerVector.size()) {
    return false;
  }

  for (size_t i = 0; i <= largerVector.size() - smallerVector.size(); ++i) {
    if (std::equal(smallerVector.begin(), smallerVector.end(),
                   largerVector.begin() + static_cast<long>(i))) {
      // Found a match
      return true;
    }
  }

  // No match found
  return false;
}

bool AssignExpPatternStore::isExactMatch(const std::vector<std::string>& arr1,
                                         const std::vector<std::string>& arr2) {
  return arr1.size() == arr2.size() &&
         std::equal(std::begin(arr1), std::end(arr1), std::begin(arr2));
}
