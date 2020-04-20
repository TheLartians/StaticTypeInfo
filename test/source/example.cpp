#include <doctest/doctest.h>

// clang-format off
#include <iostream>
#include <static_type_info.h>

void example() {
  using namespace static_type_info;

  // compile-time type names
  constexpr auto name = getTypeName<int>();
  static_assert(name == "int");

  // compile-time type indices
  constexpr auto intIdx = getTypeIndex<int>();
  constexpr auto floatIdx = getTypeIndex<float>();
  static_assert(intIdx != floatIdx);
}
// clang-format on

TEST_CASE("example") { CHECK_NOTHROW(example()); }