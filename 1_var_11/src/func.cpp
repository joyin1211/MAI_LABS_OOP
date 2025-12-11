#include <iostream>

std::pair<int, int> closest_pair_tonum(long long n) {
    if (n <= 5) {
        return {-1, -1};
    }
    long long k  = n + n - 3;
    long long l = 1, r = n + n;
    while(r - l > 1) {
        long long m = (l + r) / 2;
        // std::cout << m << " " << n / m << std::endl;
        if (k / m < m) {
            r = m;
        } else {
            l = m;
        }
    }
    long long p1 = l;
    if (2 * n - 3 - p1 * p1 <= 4 && !(p1 % 2)) {
        p1--;
    }
    long long p2 = (2 - p1 % 2);
    // 7 3 (49 9) => 3 * 3 + 5 * 5 = 34 / 2 = 17
    for (p2; ((p1 * p1 + p2 * p2) / 2 < n) && (p1 * p1 - (p1 * p1 + p2 * p2) / 2 < n) && (p1 * p1 - (p1 * p1 + p2 * p2) / 2) > 0; p2 += 2) {
        continue;
    }
    p2 -= 2;
    // std::cout << p1 << " " << p2 << std::endl;
    /*
    17
    9 + 9
    n = 30
    29 + 20 = 49 = 7 * 7
    29 - 20 = 9 = 3 * 3
    */
    //std::cout << p2 << "------<---\n" << std::endl;
    int r1 = ((long long)p1 * p1 + p2 * p2) / 2;
    int r2 = p1 * p1 - r1;
    return {r1, r2};
    /*
    = 81
    = 16
    */
}