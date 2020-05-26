#pragma once

namespace static_type_info {

  template <typename T> struct IDGenerator { static const T* const id; };

  template <typename T> const T* const IDGenerator<T>::id = nullptr;

  using TypeIndex = const void*;

  template <class T> constexpr TypeIndex getTypeIndex() { return &IDGenerator<T>::id; }

}  // namespace static_type_info
