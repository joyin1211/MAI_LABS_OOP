#pragma once
#include <ostream>
#include "concepts.hpp"
#include "point.hpp"

template <Scalar T>
class Figure {
public:
    virtual ~Figure() = default;

    virtual double area() const = 0;
    virtual Point<double> centroid() const = 0;
    virtual void print(std::ostream& os) const = 0;

    virtual bool equals(const Figure<T>& other) const = 0;

    explicit operator double() const { return area(); }

    bool operator==(const Figure<T>& other) const { return equals(other); }
    bool operator!=(const Figure<T>& other) const { return !equals(other); }

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& f) {
        f.print(os);
        return os;
    }
};
