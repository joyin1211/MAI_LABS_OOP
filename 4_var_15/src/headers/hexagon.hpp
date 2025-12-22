#pragma once
#include "polygon.hpp"

template <Scalar T>
class Hexagon : public Polygon<T, 6> {
public:
    using Polygon<T, 6>::Polygon;
};
