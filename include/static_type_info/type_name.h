#pragma once

#include <string_view>

// based on
// https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c/56766138#56766138

namespace static_type_info {

  template <class T> constexpr std::string_view rawTypeName() {
#if defined(_MSC_VER)
    return __FUNCSIG__;
#else
    return __PRETTY_FUNCTION__;
#endif
  }

  namespace probe {
    constexpr auto probeRawTypeName = rawTypeName<double>();
    constexpr size_t probeRawTypeLength = std::string_view("double").size();
    constexpr size_t prefixLength = probeRawTypeName.find("double");
    static_assert(prefixLength != std::string_view::npos,
                  "cannot extract typename from function signature");
    constexpr size_t suffixLength = probeRawTypeName.size() - prefixLength - probeRawTypeLength;
  }  // namespace probe

  using TypeName = std::string_view;

  template <class T> constexpr TypeName getTypeName() {
    std::string_view name = rawTypeName<T>();
    return std::string_view(name.data() + probe::prefixLength,
                            name.size() - probe::prefixLength - probe::suffixLength);
  }

}  // namespace static_type_info