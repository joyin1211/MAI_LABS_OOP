#include "Pentagon.hpp"
#include <vector>

Figure* Pentagon::clone() const {
    return new Pentagon(*this);
}

bool Pentagon::equals(const Figure& other) const {
    auto* o = dynamic_cast<const Pentagon*>(&other);
    if (!o) {
        return false;
    }
    return Figure::equals(other);
}
