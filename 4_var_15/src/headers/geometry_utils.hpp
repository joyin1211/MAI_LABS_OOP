#pragma once
#include <cmath>
#include "point.hpp"

template <Scalar T>
inline double cross(const Point<T>& a, const Point<T>& b) {
    return static_cast<double>(a.x) * static_cast<double>(b.y) -
           static_cast<double>(a.y) * static_cast<double>(b.x);
}

inline bool almost_equal(double a, double b, double eps = 1e-9) {
    return std::fabs(a - b) <= eps;
}
