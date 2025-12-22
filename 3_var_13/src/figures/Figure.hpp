#pragma once
#include <iostream>
#include <vector>
#include "Point.hpp"

class Figure {
protected:
    std::vector<Point> points;
    size_t sz;
    double signedArea() const;

public:
    virtual ~Figure() = default;
    Figure() = default;

    Figure(const std::vector<Point> pts) {
        points = pts;
        sz = pts.size();
    }

    Point center() const;
    double area() const;

    void print(std::ostream& os) const;
    void read(std::istream& is);

    virtual Figure* clone() const = 0;
    bool equals(const Figure& other) const;

    explicit operator double() const { return area(); }

    friend std::ostream& operator<<(std::ostream& os, const Figure& f) {
        f.print(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure& f) {
        f.read(is);
        return is;
    }

    friend bool operator==(const Figure& a, const Figure& b) {
        return a.equals(b);
    }
};
