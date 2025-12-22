#include "Rhomb.hpp"
#include <vector>

Figure* Rhomb::clone() const {
    return new Rhomb(*this);
}



bool Rhomb::equals(const Figure& other) const {
    auto* o = dynamic_cast<const Rhomb*>(&other);
    if (!o) {
        return false;
    }
    return Figure::equals(other);
}
