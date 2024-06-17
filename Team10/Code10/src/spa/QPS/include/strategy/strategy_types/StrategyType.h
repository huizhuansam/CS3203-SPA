#pragma once

namespace QPS {
enum class StrategyType {
  // (stmt, stmt)
  FOLLOWS,
  FOLLOWS_T,
  PARENT,
  PARENT_T,
  NEXT,
  NEXT_T,
  AFFECTS,

  // (ent, ent)
  MODIFIES_P,
  USES_P,
  CALLS,
  CALLS_T,

  // (stmt, ent)
  MODIFIES_S,
  USES_S,

  // pattern
  ASSIGN_PATTERN,
  WHILE_PATTERN,
  IF_PATTERN,
};
}  // namespace QPS
