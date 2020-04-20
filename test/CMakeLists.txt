cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(StaticTypeIndexTests
  LANGUAGES CXX
)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME doctest
  GITHUB_REPOSITORY onqtam/doctest
  GIT_TAG 2.3.7
)

if (TEST_INSTALLED_VERSION)
  find_package(StaticTypeInfo REQUIRED)
else()
  CPMAddPackage(
    NAME StaticTypeInfo
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
  )
endif()

CPMAddPackage(
  NAME Format.cmake
  GITHUB_REPOSITORY TheLartians/Format.cmake
  VERSION 1.0
)

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(StaticTypeIndexTests ${sources})
target_link_libraries(StaticTypeIndexTests doctest StaticTypeInfo)

set_target_properties(StaticTypeIndexTests PROPERTIES CXX_STANDARD 17)

# enable compiler warnings
if (NOT TEST_INSTALLED_VERSION)
  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(StaticTypeInfo INTERFACE -Wall -pedantic -Wextra -Werror)
  elseif(MSVC)
    target_compile_options(StaticTypeInfo INTERFACE /W4 /WX)
  endif()
endif()

# ---- Add StaticTypeIndexTests ----

ENABLE_TESTING() 

# Note: doctest and similar testing frameworks can automatically configure CMake tests
# For other testing frameworks add the tests target instead:
# ADD_TEST(StaticTypeIndexTests StaticTypeIndexTests)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(StaticTypeIndexTests)

# ---- code coverage ----

if (ENABLE_TEST_COVERAGE)
  target_compile_options(StaticTypeIndexTests PUBLIC -O0 -g -fprofile-arcs -ftest-coverage --coverage)
  target_link_options(StaticTypeIndexTests PUBLIC "--coverage")
endif()
