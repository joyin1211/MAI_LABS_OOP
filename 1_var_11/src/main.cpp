#include <iostream>
#include "func.hpp"

int main () {
    // closest_pair_tonum(10);
    // closest_pair_tonum(30);
    // closest_pair_tonum(50);
    // std::cout << closest_pair_tonum(10).first << " " << closest_pair_tonum(10).second << std::endl;
    // std::cout << closest_pair_tonum(30).first << " " << closest_pair_tonum(30).second << std::endl;
    // std::cout << closest_pair_tonum(50).first << " " << closest_pair_tonum(50).second << std::endl;
    // std::cout << closest_pair_tonum(81).first << " " << closest_pair_tonum(81).second << std::endl;
    int n;
    std::cin >> n;
    std::pair<int, int> res = closest_pair_tonum(n);
    std::cout << res.first << " " << res.second << std::endl;
}