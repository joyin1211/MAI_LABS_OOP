#pragma once
#include <iostream>
#include "concepts.hpp"

template <Scalar T>
class Point {
public:
    T x{};
    T y{};

    Point() = default;
    Point(T x, T y) : x(x), y(y) {}

    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p.x >> p.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};