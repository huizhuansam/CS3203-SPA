#include "SP.h"

#include "catch.hpp"

// TODO: CREATE MORE ROBUST TEST CASES
TEST_CASE("SP throws when program contains syntax errors", "[SP]") {
  SP::SP sourceProcessor{};

  SECTION("Empty string") {
    std::string empty = "";
    REQUIRE_THROWS_AS(sourceProcessor.processSimple(empty), std::runtime_error);
  }
}
