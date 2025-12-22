#include "single_block.hpp"
#include "linkedlist.hpp"

#include <cstdint>
#include <iostream>

struct Complex {
    int x;
    double y;
    std::int64_t z;
};

int main() {
    single_block mr(64 * 1024);

    LinkedList<int> li(&mr);
    for (int i = 1; i <= 10; i++) {
        li.push_front(i);
    }

    std::cout << "ints: ";
    for (int x : li) {
        std::cout << x << ' ';
    }
    std::cout << "\n";

    li.pop_front();
    li.pop_front();
    li.emplace_front(111);
    li.emplace_front(222);

    for (int x : li) {
        std::cout << x << ' ';
    }
    std::cout << "\n";

    LinkedList<Complex> lc(&mr);
    lc.emplace_front(Complex{1, 3.14, 100});
    lc.emplace_front(Complex{2, 2.71, 200});
    lc.emplace_front(Complex{3, 1.62, 300});

    std::cout << "complex: ";
    for (const auto& c : lc) {
        std::cout << "{x=" << c.x << ", w=" << c.y << ", t=" << c.z << "} ";
    }
    std::cout << "\n";

    li.clear();
    lc.clear();
}
