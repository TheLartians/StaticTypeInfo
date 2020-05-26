#pragma once

namespace static_type_info {

  namespace detail {
    template <typename T> struct IDGenerator { static const void* const id; };

    template <typename T> const void* const IDGenerator<T>::id = nullptr;
  }  // namespace detail

  using TypeIndex = const void*;
  template <class T> constexpr TypeIndex getTypeIndex() { return &detail::IDGenerator<T>::id; }

}  // namespace static_type_info
