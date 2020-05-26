#pragma once

#if defined(__clang__) || defined(_WIN32)

namespace static_type_info {

  namespace detail {
    template <typename T> struct IDGenerator { static const void* const id; };
    template <typename T> const void* const IDGenerator<T>::id = nullptr;
  }  // namespace detail

  using TypeIndex = decltype(&detail::IDGenerator<void>::id);
  template <class T> constexpr TypeIndex getTypeIndex() { return &detail::IDGenerator<T>::id; }

}  // namespace static_type_info

#else

#  include <static_type_info/hash.h>
#  include <static_type_info/type_name.h>

namespace static_type_info {

  using TypeIndex = uint64_t;

  template <class T> constexpr TypeIndex getTypeIndex() {
    return hash_64_fnv1a_const(getTypeName<T>());
  }

}  // namespace static_type_info

#endif
