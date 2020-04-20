#include <doctest/doctest.h>
#include <static_type_info/type_id.h>

#include <ostream>
#include <unordered_map>

TEST_CASE_TEMPLATE("TypeID", T, int, float, double) {
  using namespace static_type_info;
  constexpr auto typeID = getTypeID<T>();
  static_assert(typeID.name == getTypeName<T>());
  static_assert(typeID.index == getTypeIndex<T>());
  static_assert(typeID == getTypeID<T>());
  static_assert(typeID != getTypeID<char>());
  CHECK(typeID.name == getTypeName<T>());
  CHECK(typeID.index == getTypeIndex<T>());
  CHECK(typeID == getTypeID<T>());
  CHECK(typeID != getTypeID<char>());
}

TEST_CASE("Hashable TypeID") {
  using namespace static_type_info;
  std::unordered_map<TypeID, int> map;
  map[getTypeID<int>()] = 1;
  map[getTypeID<float>()] = 2;
  CHECK(map[getTypeID<int>()] == 1);
  CHECK(map[getTypeID<float>()] == 2);
}
