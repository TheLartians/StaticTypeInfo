#include <doctest/doctest.h>
#include <static_type_info/type_id.h>

#include <ostream>

TEST_CASE_TEMPLATE("TypeID", T, int, float, double) {
  using namespace static_type_info;
  constexpr auto typeID = getTypeID<T>();
  static_assert(typeID.name == getTypeName<T>());
  static_assert(typeID.index == getTypeIndex<T>());
  CHECK(typeID.name == getTypeName<T>());
  CHECK(typeID.index == getTypeIndex<T>());
}
