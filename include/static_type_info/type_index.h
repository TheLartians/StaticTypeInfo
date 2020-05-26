#pragma once

namespace static_type_info {

  template <typename T> void idGenerator() {}
  using TypeIndex = void (*)(void);

  template <class T> constexpr TypeIndex getTypeIndex() { return &idGenerator<T>; }

}  // namespace static_type_info
