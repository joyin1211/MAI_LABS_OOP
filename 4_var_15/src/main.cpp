#include <iomanip>
#include <iostream>
#include <memory>

#include "headers/array.hpp"
#include "headers/figure_utils.hpp"
#include "headers/polygon.hpp"
#include "headers/point.hpp"
#include "headers/concepts.hpp"
#include "headers/figure_utils.hpp"
#include "headers/geometry_utils.hpp"
#include "headers/triangle.hpp"
#include "headers/hexagon.hpp"
#include "headers/octagon.hpp"

int main() {
    using Coord = double;

    Array<std::shared_ptr<Figure<Coord>>> figures;

        try {
            {
                auto f = std::make_shared<Triangle<Coord>>();
                std::cout << "Enter 3 points (x y) for Triangle:\n";
                std::cin >> *f;
                figures.push_back(f);
            }
            {
                auto f = std::make_shared<Hexagon<Coord>>();
                std::cout << "Enter 6 points (x y) for Hexagon:\n";
                std::cin >> *f;
                figures.push_back(f);
            }
            auto f = std::make_shared<Octagon<Coord>>();
            std::cout << "Enter 8 points (x y) for Octagon:\n";
            std::cin >> *f;
            figures.push_back(f);
            print_all(figures);
            std::cout << "Total area = " << std::fixed << std::setprecision(6)
                      << total_area(figures) << "\n";
            std::size_t idx;
            std::cout << "Index to erase: ";
            std::cin >> idx;
            figures.erase(idx);
            std::cout << "Erased.\n";
            print_all(figures);
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }

    return 0;
}
