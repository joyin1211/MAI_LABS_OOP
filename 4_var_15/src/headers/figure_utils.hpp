#pragma once
#include <iostream>
#include <memory>
#include "array.hpp"
#include "figure.hpp"
#include "concepts.hpp"

template <Scalar T>
inline double total_area(const Array<std::shared_ptr<Figure<T> > >& arr) {
    double sum = 0.0;
    for (std::size_t i = 0; i < arr.getSize(); i++) {
        sum += static_cast<double>(*arr[i]);
    }
    return sum;
}

template <Scalar T>
inline void print_all(const Array<std::shared_ptr<Figure<T> > >& arr) {
    if (arr.empty()) {
        std::cout << "Array is empty.\n";
        return;
    }
    for (std::size_t i = 0; i < arr.getSize(); i++) {
        std::cout << "Index " << i << ":\n" << *arr[i] << "\n";
    }
}
