#include <gtest/gtest.h>

#include <cmath>
#include <memory>
#include <sstream>

#include "../src/headers/triangle.hpp"
#include "../src/headers/hexagon.hpp"
#include "../src/headers/octagon.hpp"
#include "../src/headers/array.hpp"
#include "../src/headers/figure_utils.hpp"

static bool near(double a, double b, double eps = 1e-9) {
    return std::fabs(a - b) <= eps;
}

TEST(FigureTest, AreaCentroidTriangle) {
    Triangle<double> t;
    std::istringstream in("0 0  1 0  0 1");
    in >> t;
    EXPECT_TRUE(near(t.area(), 0.5));

    auto c = t.centroid();
    EXPECT_TRUE(near(c.x, 1.0 / 3.0));
    EXPECT_TRUE(near(c.y, 1.0 / 3.0));
    double a = static_cast<double>(t);
    EXPECT_TRUE(near(a, 0.5));
}

TEST(FigureTest, SameTypeSameVerticesEqual) {
    Triangle<int> a, b;

    std::istringstream in1("0 0  1 0  0 1");
    std::istringstream in2("0 0  1 0  0 1");

    in1 >> a;
    in2 >> b;

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(FigureTest, DifferentTypesNotEqual) {
    Triangle<double> t;
    Hexagon<double> h;

    std::istringstream inT("0 0  1 0  0 1");
    inT >> t;
    std::istringstream inH("0 0  1 0  2 0  2 1  1 1  0 1");
    inH >> h;
    Figure<double>& ft = t;
    Figure<double>& fh = h;

    EXPECT_FALSE(ft == fh);
    EXPECT_TRUE(ft != fh);
}

TEST(FigureTest, SumOfAreasInArray) {
    using T = double;
    Array<std::shared_ptr<Figure<T>>> arr;

    auto t = std::make_shared<Triangle<T>>();
    std::istringstream inT("0 0  1 0  0 1");
    inT >> *t;

    auto h = std::make_shared<Hexagon<T>>();
    std::istringstream inH("0 0  1 0  1 0  1 1  0 1  0 0");
    inH >> *h;

    arr.push_back(std::static_pointer_cast<Figure<T>>(t));
    arr.push_back(std::static_pointer_cast<Figure<T>>(h));

    EXPECT_TRUE(near(total_area(arr), 0.5 + 1.0, 1e-9));
}
