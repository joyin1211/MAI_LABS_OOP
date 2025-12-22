#pragma once
#include <type_traits>

template <class T>
concept Scalar = std::is_arithmetic_v<T>;
