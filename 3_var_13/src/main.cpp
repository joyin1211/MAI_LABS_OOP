#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>

#include "figures/Rhomb.hpp"
#include "figures/Pentagon.hpp"
#include "figures/Hexagon.hpp"

static void print_centers_and_areas(const std::vector<Figure*>& figs) {
    std::cout << std::fixed << std::setprecision(6);
    for (std::size_t i = 0; i < figs.size(); i++) {
        Point c = figs[i]->center();
        double a = (double)(*figs[i]);
        std::cout << "#" << i << " center=(" << c.x << ", " << c.y << "), area=" << a << "\n";
    }
}

static double total_area(const std::vector<Figure*>& figs) {
    double s = 0.0;
    for (const auto* f : figs) s += (double)(*f);
    return s;
}

static void erase_at(std::vector<Figure*>& figs, std::size_t idx) {
    if (idx >= figs.size()) throw std::out_of_range("Bad index");
    delete figs[idx];
    figs.erase(figs.begin() + (long long)idx);
}

static void clear_all(std::vector<Figure*>& figs) {
    for (auto* f : figs) delete f;
    figs.clear();
}
int main() {
    std::vector<Figure*> figs;

    std::cout << "Commands: add, list, info, total, erase, clone, cmp, quit\n";
    std::cout << "Add format: add <type> then enter vertices:\n";
    std::cout << "rhomb : 4 points  (x y)\n";
    std::cout << "pentagon : 5 points  (x y)\n";
    std::cout << "hexagon : 6 points  (x y)\n\n";

    std::string cmd;
    while (std::cout << "> " && (std::cin >> cmd)) {
        try {
            if (cmd == "add") {
                std::string type;
                std::cin >> type;

                Figure* fig;
                if (type == "rhomb") {
                    fig = new Rhomb();
                } else if (type == "pentagon") {
                    fig = new Pentagon();
                } else if (type == "hexagon") {
                    fig = new Hexagon();
                }
                std::cin >> *fig;
                figs.push_back(fig);

                std::cout << "Added.\n";
            } else if (cmd == "list") {
                for (std::size_t i = 0; i < figs.size(); i++) {
                    std::cout << "Index " << i << "\n" << *figs[i];
                }
            } else if (cmd == "info") {
                print_centers_and_areas(figs);
            } else if (cmd == "total") {
                std::cout << std::fixed << std::setprecision(6)
                          << "Total area = " << total_area(figs) << "\n";
            } else if (cmd == "erase") {
                std::size_t idx;
                std::cin >> idx;
                erase_at(figs, idx);
                std::cout << "Erased.\n";
            } else if (cmd == "clone") {
                std::size_t idx;
                std::cin >> idx;
                if (idx >= figs.size()) throw std::out_of_range("Bad index");
                figs.push_back(figs[idx]->clone());
                figs[idx] = figs[idx + 1];
                std::cout << "Cloned into new element at index " << (figs.size() - 1) << ".\n";
            } else if (cmd == "cmp") {
                std::size_t i, j;
                std::cin >> i >> j;
                if (i >= figs.size() || j >= figs.size()) throw std::out_of_range("Bad index");
                std::cout << ((*figs[i] == *figs[j]) ? "EQUAL\n" : "NOT EQUAL\n");
            } else if (cmd == "quit") {
                break;
            } else {
                std::cout << "Unknown command.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
            if (!std::cin) {
                std::cin.clear();
                std::string dummy;
                std::getline(std::cin, dummy);
            }
        }
    }

    clear_all(figs);
    return 0;
}