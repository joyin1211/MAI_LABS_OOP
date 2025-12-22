#include "Figure.hpp"
#include <cmath>

double Figure::signedArea() const {
    long double s = 0.0L;
    for (std::size_t i = 0; i < sz; ++i) {
        const auto& a = points[i];
        const auto& b = points[(i + 1) % sz];
        s += (long double)a.x * (long double)b.y - (long double)b.x * (long double)a.y;
    }
    return (double)(s * 0.5L);
}

double Figure::area() const {
    return std::fabs(signedArea());
}

Point Figure::center() const {
    const double A2 = 2.0 * signedArea();
    if (almost_equal(A2, 0.0)) {
        Point c{};
        for (auto& pt : points) { 
            c.x += pt.x; c.y += pt.y; 
        }
        c.x /= (double)sz; c.y /= (double)sz;
        return c;
    }

    long double cx = 0.0L, cy = 0.0L;
    long double cross_sum = 0.0L;

    for (size_t i = 0; i < sz; ++i) {
        const auto& a = points[i];
        const auto& b = points[(i + 1) % sz];
        long double cross = (long double)a.x * (long double)b.y - (long double)b.x * (long double)a.y;
        cross_sum += cross;
        cx += ((long double)a.x + (long double)b.x) * cross;
        cy += ((long double)a.y + (long double)b.y) * cross;
    }

    const long double denom = 3.0L * cross_sum;

    Point c{};
    c.x = (double)(cx / denom);
    c.y = (double)(cy / denom);
    return c;
}

void Figure::print(std::ostream& os) const {
    for (std::size_t i = 0; i < sz; ++i) {
        os << "  P" << (i + 1) << " = (" << points[i].x << ", " << points[i].y << ")\n";
    }
}

void Figure::read(std::istream& is) {
    for (int i = 0; i < sz; i++) {
        Point tmp;
        is >> tmp.x >> tmp.y;
        points[i] = tmp;
    }
}

bool Figure::equals(const Figure &other) const {
    for (std::size_t i = 0; i < sz; ++i) {
        if (!(points[i] == other.points[i])) { 
            return false; 
        }
    }
    return true;
}