#include <doctest/doctest.h>
#include <static_type_info/type_name.h>

#include <string>

namespace {
  class A {};
  class B {};
  template <class T> class C {};
}  // namespace

namespace ns {
  class A {};
  class B {};
  template <class T> class C {};
}  // namespace ns

TEST_CASE("TypeName") {
  using namespace static_type_info;
  using A = float;
  using B = ::C<A>;

  static_assert(getTypeName<int>() == getTypeName<int>());
  static_assert(getTypeName<int>() != getTypeName<double>());
  static_assert(getTypeName<float>() == getTypeName<A>());
  static_assert(getTypeName<::A>() == getTypeName<::A>());
  static_assert(getTypeName<::A>() != getTypeName<ns::A>());
  static_assert(getTypeName<ns::A>() == getTypeName<ns::A>());
  static_assert(getTypeName<::A>() != getTypeName<A>());
  static_assert(getTypeName<::A>() != getTypeName<::B>());
  static_assert(getTypeName<::C<float>>() == getTypeName<::C<float>>());
  static_assert(getTypeName<::C<float>>() == getTypeName<B>());
  static_assert(getTypeName<::C<float>>() != getTypeName<::C<int>>());

  CHECK(std::string(getTypeName<char>()) == std::string("char"));
  CHECK(std::string(getTypeName<int>()) == std::string("int"));
  CHECK(std::string(getTypeName<float>()) == std::string("float"));
  CHECK(std::string(getTypeName<double>()) == std::string("double"));

#if defined(_MSC_VER)
  CHECK(std::string(getTypeName<ns::A>()) == std::string("class ns::A"));
  CHECK(std::string(getTypeName<ns::C<ns::A>>()) == std::string("class ns::C<class ns::A>"));
#else
  CHECK(std::string(getTypeName<ns::A>()) == std::string("ns::A"));
  CHECK(std::string(getTypeName<ns::C<ns::A>>()) == std::string("ns::C<ns::A>"));
#endif
}
