#pragma once

namespace QPS {
class HashCombiner {
 public:
  template <typename W>
  static void hash_combine(size_t& seed, const W& value) {
    std::hash<W> hasher;
    // 0x9e3779b9 is a prime number - "magic number" for hashing
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }
};
}  // namespace QPS
