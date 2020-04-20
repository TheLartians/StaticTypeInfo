#include <doctest/doctest.h>
#include <static_type_info/type_name.h>
#include <string>
#include <iostream>
namespace ns {
  class A { };
  class B { };
  template <class T> class C { };
}

TEST_CASE("Type name") {
  using namespace static_type_info;

  static_assert(typeName<int>() == typeName<int>());
  static_assert(typeName<int>() != typeName<double>());
  static_assert(typeName<ns::A>() == typeName<ns::A>());
  static_assert(typeName<ns::A>() != typeName<ns::B>());
  static_assert(typeName<ns::C<float>>() == typeName<ns::C<float>>());
  static_assert(typeName<ns::C<float>>() != typeName<ns::C<int>>());

  CHECK(std::string(typeName<int>()) == std::string("int"));

#if defined(_MSC_VER)
  CHECK(std::string(typeName<ns::A>()) == std::string("class ns::A"));
  CHECK(std::string(typeName<ns::C<ns::A>>()) == std::string("class ns::C<class ns::A>"));
#else
  CHECK(std::string(typeName<ns::A>()) == std::string("ns::A"));
  CHECK(std::string(typeName<ns::C<ns::A>>()) == std::string("ns::C<ns::A>"));
#endif
}
