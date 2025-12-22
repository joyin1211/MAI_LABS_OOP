#include "Hexagon.hpp"
#include <vector>

Figure* Hexagon::clone() const {
    return new Hexagon(*this);
}

bool Hexagon::equals(const Figure& other) const {
    auto* o = dynamic_cast<const Hexagon*>(&other);
    if (!o) {
        return false;
    }
    return Figure::equals(other);
}
