cmake_minimum_required(VERSION 3.14)
project(lab_3)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

enable_testing()

find_package(GTest REQUIRED)


include(GoogleTest)

add_executable(main
    src/main.cpp
    src/figures/Figure.cpp
    src/figures/Hexagon.cpp
    src/figures/Pentagon.cpp
    src/figures/Rhomb.cpp
)