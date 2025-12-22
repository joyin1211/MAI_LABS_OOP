#pragma once
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

template <class T>
class Array {
public:
    Array() : cap(0), size(0) {}

    std::size_t getSize() const { return size; }
    bool empty() const { return size == 0; }

    T& operator[](std::size_t i) {
        if (i >= size) {
            throw std::out_of_range("Array index out of range");
        }
        return data[i];
    }

    const T& operator[](std::size_t i) const {
        if (i >= size) throw std::out_of_range("Array index out of range");
        return data[i];
    }

    void push_back(T value) {
        if (size == cap) reserve(cap == 0 ? 2 : cap * 2);
        data[size++] = std::move(value);
    }

    void erase(std::size_t index) {
        if (index >= size) throw std::out_of_range("erase: bad index");
        for (std::size_t i = index + 1; i < size; i++) {
            data[i - 1] = std::move(data[i]);
        }
        size--;
    }

    void reserve(std::size_t new_cap) {
        if (new_cap <= cap) return;
        auto new_data = std::make_unique<T[]>(new_cap);

        for (std::size_t i = 0; i < size; i++) {
            new_data[i] = std::move(data[i]);
        }

        data = std::move(new_data);
        cap = new_cap;
    }

private:
    std::unique_ptr<T[]> data;
    std::size_t cap;
    std::size_t size;
};
