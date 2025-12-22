#pragma once
#include "polygon.hpp"

template <Scalar T>
class Octagon : public Polygon<T, 8> {
public:
    using Polygon<T, 8>::Polygon;
};
