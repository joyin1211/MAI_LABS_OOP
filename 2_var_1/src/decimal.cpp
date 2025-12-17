#include "decimal.hpp"
#include <stdexcept>
#include <algorithm>
#include <string>
#include <iostream>

void Decimal::removeLeadingZeroes() {
    while (size > 1 && digits[size - 1] == '0') {
        size--;
    }
}

Decimal::Decimal() :size(1), capacity(1){
    digits = new unsigned char[1]{'0'};
}

Decimal::Decimal (const size_t n, unsigned char t) : size(n), capacity(n){
    if (t > 9) {
        throw std::invalid_argument("Second argument must be between digit between 0 and 9.");
    }
    if (n == 0) {
        digits = new unsigned char[1]{'0'};
        size = 1;
        capacity = 1;
        return;
    }
    digits = new unsigned char[size];
    std::fill(digits, digits + size, t + '0');
    removeLeadingZeroes();
}

Decimal::Decimal(const std::initializer_list<unsigned char> &t) : size(t.size()), capacity(t.size()) {
    if (size == 0) {
        digits = new unsigned char[1]{'0'};
        size = 1;
        capacity = 1;
        return;
    }
    digits = new unsigned char[size];
    size_t i = 0;
    for (auto &to : t) {
        if (to > 9 || to < 0) {
            delete[] digits;
            throw std::invalid_argument("Argument must be between digit between 0 and 9.");
        }
        digits[i++] = to + '0';
    }
    removeLeadingZeroes();
}

Decimal::Decimal(const std::string &t) : size(t.size()), capacity(t.size()) {
    if (size == 0) {
        digits = new unsigned char[1]{'0'};
        size = 1;
        capacity = 1;
        return;
    }
    digits = new unsigned char[size];
    size_t i = 0;
    for (auto it = t.rbegin(); it != t.rend(); it++) {
        if (*it > '9' || *it < '0') {
            delete[] digits;
            throw std::invalid_argument("Symbols must be between digit between 0 and 9.");
        }
        digits[i++] = *it;
    }
    removeLeadingZeroes();
}

Decimal::Decimal(const Decimal& other) : size(other.size), capacity(other.capacity) {
    digits = new unsigned char[size];
    std::copy(other.digits, other.digits + size, digits);
}

Decimal::Decimal(Decimal&& other) noexcept : digits(other.digits), size(other.size), capacity(other.capacity) {    
    other.digits = nullptr;
    other.size = 0;
}

Decimal::~Decimal() noexcept {
    delete[] digits;
}

Decimal Decimal::copy() const {
    std::string newDigits;
    newDigits.resize(size);
    for (size_t i = size - 1; i >= 0; i--) {
        newDigits[i] = digits[i];
        if (!i) break;
    }
    return Decimal(newDigits);
}

Decimal Decimal::addTo(const Decimal &other) const {
    size_t maxSize = std::max(size, other.size);
    Decimal result(maxSize + 1, 0);
    result.size = maxSize + 1;
    unsigned int cf = 0;
    for (size_t i = 0; i < maxSize || cf > 0; i++) {
        unsigned int sum = cf;
        if (i < size) {
            sum += digits[i] - '0';
        }
        if (i < other.size) {
            sum += other.digits[i] - '0';
        }
        
        result.digits[i] = sum % 10 + '0';
        cf = sum / 10;
    }
    result.removeLeadingZeroes();
    return result;
}

Decimal Decimal::subTo(const Decimal &other) const {
    if (isLess(other)) {
        throw std::invalid_argument("Result would be negative.");
    }
    Decimal result(size, 0);
    unsigned int bf = 0;
    for (size_t i = 0; i < size; ++i) {
        int diff = digits[i] - '0' - bf;
        if (i < other.size) {
            diff -= other.digits[i] - '0';
        }
        if (diff < 0) {
            diff += 10;
            bf = 1;
        } else {
            bf = 0;
        }
        result.digits[i] = diff + '0';
    }
    result.size = size;
    result.removeLeadingZeroes();
    return result;
}

int Decimal::compare(const Decimal& other) const {
    if (size != other.size) {
        return (size < other.size) ? -1 : 1;
    }
    for (size_t i = size - 1; i >= 0; i--) {
        if (digits[i] != other.digits[i]) {
            return (digits[i] < other.digits[i]) ? -1 : 1;
        }
        if (!i) break;
    }
    return 0;
}

Decimal Decimal::add(const Decimal& first, const Decimal& second) const {
    return first.addTo(second);
}

Decimal Decimal::sub(const Decimal& first, const Decimal& second) const {
    return first.subTo(second);
}

bool Decimal::isLess(const Decimal& other) const {
    return compare(other) < 0;
}

bool Decimal::isGreater(const Decimal& other) const {
    return compare(other) > 0;
}

bool Decimal::isEqual(const Decimal& other) const {
    return compare(other) == 0;
}

size_t Decimal::getSize() const {
    return size;
}

std::string Decimal::toString() const {
    if (size == 1 && digits[0] == '0') {
        return "0";
    }
    std::string result;
    for (size_t i = size - 1; i >= 0; i--) {
        result.push_back(digits[i]);
        if (!i) break;
    }
    return result;
}