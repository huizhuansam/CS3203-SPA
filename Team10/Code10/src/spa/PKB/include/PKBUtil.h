#pragma once
#include <functional>
#include <string>
#include <unordered_set>

inline std::string getStringFromSet(std::unordered_set<std::string> set) {
  if (!set.empty() && set.size() == 1) {
    return *set.begin();
  } else {
    // return -1 if not found
    return "";
  }
}

inline int getIntFromSet(std::unordered_set<int> set) {
  if (!set.empty() && set.size() == 1) {
    return *set.begin();
  } else {
    // return -1 if not found
    return -1;
  }
}

// ai-gen start(gpt, 0, e)
// prompt:https://chat.openai.com/share/feedba04-6fd0-4e9b-8b5a-c7826127fa4f
// prompt:https://platform.openai.com/playground/p/tZh1kiEEC4XpMgsKqQSAluV6?mode=chat
struct PairHash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    auto hash1 = std::hash<T1>{}(p.first);
    auto hash2 = std::hash<T2>{}(p.second);
    return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
  }
};
// ai-gen end