#pragma once

#include <type_traits>
#include <sha256_literal.h>
#include <static_type_info/type_name.h>

#include <array>
#include <climits>
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

    using Hash = sha256_literal::HashType;

    template <typename T, size_t I> static constexpr T scalarHash(Hash data) {
      if constexpr (I == 0) {
        return T(data[I]);
      } else {
        return (scalarHash<T, I - 1>(data) >> CHAR_BIT) + T(data[I]);
      }
    }

    template <typename T> static constexpr auto scalarHash(Hash data) {
      return scalarHash<T, sizeof(T) / sizeof(data[0])>(data);
    }

  }  // namespace detail

  template <class T> constexpr TypeIndex getTypeIndex() {
    constexpr TypeName name = getTypeName<T>();
    constexpr auto shaHash = sha256_literal::compute(detail::asArray<uint8_t, name.size()>(name));
    static_assert(sizeof(shaHash) >= sizeof(TypeIndex));
    return detail::scalarHash<TypeIndex>(shaHash);
  }

}  // namespace static_type_info
