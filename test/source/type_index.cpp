#include <doctest/doctest.h>
#include <static_type_info/type_index.h>

#include <type_traits>

namespace ns {
  class A {};
  class B {};
  template <class T> class C {};
}  // namespace ns

template <class A, class B> void checkType() {
  using namespace static_type_info;
  constexpr auto ia = getTypeIndex<A>();
  constexpr auto ib = getTypeIndex<B>();
  static_assert(ia != ib || std::is_same<A, B>::value);
  if (std::is_same<A, B>::value) {
    CHECK(ia == ib);
  } else {
    CHECK(ia != ib);
  }
}
#include <iostream>
TEST_CASE_TEMPLATE("TypeIndex", T, char, int, unsigned, float, double, long, long long, size_t,
                   ns::A, ns::B, ns::C<ns::A>, ns::C<ns::B>) {
  checkType<char, T>();
  checkType<int, T>();
  checkType<unsigned, T>();
  checkType<float, T>();
  checkType<double, T>();
  checkType<long, T>();
  checkType<long long, T>();
  checkType<size_t, T>();
  checkType<ns::A, T>();
  checkType<ns::B, T>();
  checkType<ns::C<ns::A>, T>();
  checkType<ns::C<ns::B>, T>();
}
