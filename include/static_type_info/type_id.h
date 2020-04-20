#pragma once

#include <static_type_info/type_index.h>
#include <static_type_info/type_name.h>

namespace static_type_info {

  struct TypeID {
    TypeName name = TypeName();
    TypeIndex index = TypeIndex();
  };

  template <class T> constexpr TypeID getTypeID() {
    return TypeID{getTypeName<T>(), getTypeIndex<T>()};
  }

}  // namespace static_type_info