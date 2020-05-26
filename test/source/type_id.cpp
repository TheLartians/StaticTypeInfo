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

template <class T> constexpr auto getAnonymousTypeIndex() {
  using namespace static_type_info;
  struct X {};
  return getTypeID<X>();
}

TEST_CASE("Anonymous types") {
  static_assert(getAnonymousTypeIndex<int>() != getAnonymousTypeIndex<unsigned>());
  static_assert(getAnonymousTypeIndex<int>() != getAnonymousTypeIndex<float>());
  static_assert(getAnonymousTypeIndex<int>() != getAnonymousTypeIndex<double>());
}
