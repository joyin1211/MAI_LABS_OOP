#include <gtest/gtest.h>
#include <cmath>

#include "../src/figures/Rhomb.hpp"
#include "../src/figures/Pentagon.hpp"
#include "../src/figures/Hexagon.hpp"


static bool near(double a, double b, double eps = 1e-9) {
    return std::fabs(a - b) <= eps;
}