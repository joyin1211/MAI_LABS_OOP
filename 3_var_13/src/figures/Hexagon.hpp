#include "Figure.hpp"
#include <vector>

class Hexagon : public Figure {
public:
    Hexagon() {
        points.resize(6, {0, 0});
        sz = 6;
    }

    Hexagon(const Hexagon&) = default;
    Hexagon(Hexagon&&) noexcept = default;
    Hexagon& operator=(const Hexagon&) = default;
    Hexagon& operator=(Hexagon&&) noexcept = default;

    Figure* clone() const;
    bool equals(const Figure& other) const;
};