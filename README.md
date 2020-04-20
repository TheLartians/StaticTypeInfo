[![Actions Status](https://github.com/TheLartians/StaticTypeInfo/workflows/MacOS/badge.svg)](https://github.com/TheLartians/StaticTypeInfo/actions)
[![Actions Status](https://github.com/TheLartians/StaticTypeInfo/workflows/Windows/badge.svg)](https://github.com/TheLartians/StaticTypeInfo/actions)
[![Actions Status](https://github.com/TheLartians/StaticTypeInfo/workflows/Ubuntu/badge.svg)](https://github.com/TheLartians/StaticTypeInfo/actions)
[![Actions Status](https://github.com/TheLartians/StaticTypeInfo/workflows/Style/badge.svg)](https://github.com/TheLartians/StaticTypeInfo/actions)
[![Actions Status](https://github.com/TheLartians/StaticTypeInfo/workflows/Install/badge.svg)](https://github.com/TheLartians/StaticTypeInfo/actions)
[![codecov](https://codecov.io/gh/TheLartians/StaticTypeInfo/branch/master/graph/badge.svg)](https://codecov.io/gh/TheLartians/StaticTypeInfo)

# StaticTypeInfo

A simple C++17 compile-time type info library. 

## API

The header-only library exposes two `constexpr` functions: `string_view getTypeName<T>()` and `TypeIndex getTypeIndex<T>()`.

```cpp
#include <iostream>
#include <static_type_info.h>

void example() {
  using namespace static_type_info;

  // compile-time type names
  constexpr auto name = getTypeName<int>();
  static_assert(name == "int");

  // compile-time type indices
  constexpr auto intIdx = getTypeIndex<int>();
  constexpr auto floatIdx = getTypeIndex<float>();
  static_assert(intIdx != floatIdx);
}
```
