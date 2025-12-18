cmake_minimum_required(VERSION 3.14)
project(lab_6)

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

add_executable(tests
    tests/tests.cpp
    src/npc/types.hpp
    src/npc/npc.cpp
    src/npc/knight.cpp
    src/npc/druid.cpp
    src/npc/elf.cpp
    src/patterns/observer.cpp
    src/patterns/battle_visitor.cpp
    src/patterns/npc_factory.cpp
    src/editor/editor.cpp
)


target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

add_executable(main
    src/main.cpp
    src/npc/types.hpp
    src/npc/npc.cpp
    src/npc/knight.cpp
    src/npc/druid.cpp
    src/npc/elf.cpp
    src/patterns/observer.cpp
    src/patterns/battle_visitor.cpp
    src/patterns/npc_factory.cpp
    src/editor/editor.cpp
)