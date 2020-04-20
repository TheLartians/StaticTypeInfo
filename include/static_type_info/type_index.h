#pragma once

#include <static_type_info/hash.h>
#include <static_type_info/type_name.h>

#include <array>
#include <climits>
#include <type_traits>
#include <utility>

namespace static_type_info {

  using TypeIndex = size_t;

  namespace detail {
    template <typename T, size_t N, size_t... I>
    static constexpr auto asArray(TypeName data, std::index_sequence<I...>) {
      return std::array<T, N>{T(data[I])...};
    }

    template <typename T, size_t N> static constexpr auto asArray(TypeName data) {
      return asArray<T, N>(data, std::make_index_sequence<N>());
    }

  }  // namespace detail

  template <class T> constexpr TypeIndex getTypeIndex() {
    return hash_64_fnv1a_const(getTypeName<T>());
  }

}  // namespace static_type_info
