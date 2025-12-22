#include "Figure.hpp"
#include <vector>

class Pentagon : public Figure {
public:
    Pentagon() {
        points.resize(5, {0, 0});
        sz = 5;
    }
    /*Pentagon() {
     points.resize(4);
        for (size_t i = 0; i < 4; i++) {
            points[i] = pts[i];
        }
        sz = 4;
    }*/
    Pentagon(const Pentagon&) = default;
    Pentagon(Pentagon&&) noexcept = default;
    Pentagon& operator=(const Pentagon&) = default;
    Pentagon& operator=(Pentagon&&) noexcept = default;

    Figure* clone() const;
    bool equals(const Figure& other) const;
};