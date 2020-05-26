#pragma once

#include <static_type_info/type_index.h>
#include <static_type_info/type_name.h>

namespace static_type_info {

  struct TypeID {
    TypeName name = TypeName();
    TypeIndex index = TypeIndex();

    constexpr bool operator==(const TypeID &other) const { return index == other.index; }
    constexpr bool operator!=(const TypeID &other) const { return index != other.index; }
    constexpr bool operator<(const TypeID &other) const { return index < other.index; }
  };

  template <class T> constexpr TypeID getTypeID() {
    return TypeID{getTypeName<T>(), getTypeIndex<T>()};
  }

}  // namespace static_type_info

namespace std {
  template <> struct hash<static_type_info::TypeID> {
    hash<static_type_info::TypeIndex> hasher;
    size_t operator()(const static_type_info::TypeID &id) const { return hasher(id.index); }
  };
}  // namespace std
