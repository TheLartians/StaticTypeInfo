#pragma once

#include <static_type_info/hash.h>
#include <static_type_info/type_name.h>

#include <array>
#include <climits>
#include <type_traits>
#include <utility>

namespace static_type_info {

  using TypeIndex = size_t;

  template <class T> constexpr TypeIndex getTypeIndex() {
    return hash_64_fnv1a_const(getTypeName<T>());
  }

}  // namespace static_type_info
