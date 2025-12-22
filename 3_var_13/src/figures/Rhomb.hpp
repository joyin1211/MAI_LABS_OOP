#include "Figure.hpp"
#include "Point.hpp"
#include <vector>

class Rhomb : public Figure {
public:
    Rhomb() {
        points.resize(4, {0, 0});
        sz = 4;
    }

    Rhomb(const Rhomb &other) {
        points.resize(4);
        for (size_t i = 0; i < 4; i++) {
            points[i] = other.points[i];
        }
        sz = 4;
    }

    Rhomb(Rhomb&&) noexcept = default;
    Rhomb& operator=(const Rhomb&) = default;
    Rhomb& operator=(Rhomb&&) noexcept = default;

    Figure* clone() const;
    bool equals(const Figure& other) const;
};