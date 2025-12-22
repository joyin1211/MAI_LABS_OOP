#pragma once
#include <cmath>

struct Point {
    double x{0.0};
    double y{0.0};
};

inline bool almost_equal(double a, double b, double eps = 1e-9) {
    return std::fabs(a - b) <= eps;
}

inline bool operator==(const Point& a, const Point& b) {
    return almost_equal(a.x, b.x) && almost_equal(a.y, b.y);
}
