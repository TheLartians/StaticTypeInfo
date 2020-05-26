#include <doctest/doctest.h>
#include <static_type_info/type_index.h>

#include <cstddef>
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
  if constexpr (std::is_same<A, B>::value) {
    CHECK(ia == ib);
    static_assert(ia == ib);
  } else {
    CHECK(ia != ib);
    static_assert(ia != ib);
  }
}

TEST_CASE_TEMPLATE("TypeIndex", T, char, int, unsigned, float, double, long, long long, std::size_t,
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

#ifdef STATIC_TYPE_INFO_USE_MEMBER_POINTER
// Anonymous functions are incompatible with the name based implementation

template <class T> constexpr auto getAnonymousTypeIndex() {
  using namespace static_type_info;
  struct X {};
  return getTypeIndex<X>();
}

TEST_CASE("Anonymous types") {
  static_assert(getAnonymousTypeIndex<int>() != getAnonymousTypeIndex<unsigned>());
  static_assert(getAnonymousTypeIndex<int>() != getAnonymousTypeIndex<float>());
  static_assert(getAnonymousTypeIndex<int>() != getAnonymousTypeIndex<double>());
}

#endif