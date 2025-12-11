cmake_minimum_required(VERSION 3.14)
project(lab_1)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

enable_testing()

find_package(GTest REQUIRED)

add_executable(
  tests
  tests/tests.cpp
  src/func.cpp
)

target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

add_executable(main
    src/main.cpp
    src/func.cpp
)
