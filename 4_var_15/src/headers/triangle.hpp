#pragma once
#include "polygon.hpp"

template <Scalar T>
class Triangle : public Polygon<T, 3> {
public:
    using Polygon<T, 3>::Polygon;
};
