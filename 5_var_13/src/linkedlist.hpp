#pragma once

#include <cstddef>
#include <iterator>
#include <memory_resource>
#include <new>
#include <type_traits>
#include <utility>

template <class T>
class LinkedList {
private:
    struct Node {
        Node* next{nullptr};
        T value;

        template <class... Args>
        explicit Node(Node* n, Args&&... args)
            : next(n), value(std::forward<Args>(args)...)
        {}
    };

    using NodeAlloc = std::pmr::polymorphic_allocator<Node>;

public:
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        iterator() = default;
        explicit iterator(Node* p) : p_(p) {}

        reference operator*() const { return p_->value; }
        pointer operator->() const { return &p_->value; }

        iterator& operator++() { p_ = p_->next; return *this; }
        iterator operator++(int) { iterator tmp(*this); ++(*this); return tmp; }

        friend bool operator==(const iterator& a, const iterator& b) { return a.p_ == b.p_; }
        friend bool operator!=(const iterator& a, const iterator& b) { return !(a == b); }

    private:
        Node* p_{nullptr};
        friend class LinkedList;
    };

    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = const T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator() = default;
        explicit const_iterator(const Node* p) : p_(p) {}
        const_iterator(iterator it) : p_(it.p_) {}

        reference operator*() const { return p_->value; }
        pointer operator->() const { return &p_->value; }

        const_iterator& operator++() { p_ = p_->next; return *this; }
        const_iterator operator++(int) { const_iterator tmp(*this); ++(*this); return tmp; }

        friend bool operator==(const const_iterator& a, const const_iterator& b) { return a.p_ == b.p_; }
        friend bool operator!=(const const_iterator& a, const const_iterator& b) { return !(a == b); }

    private:
        const Node* p_{nullptr};
    };

    explicit LinkedList(std::pmr::memory_resource* mr = std::pmr::get_default_resource())
        : alloc_(mr)
    {}

    ~LinkedList() { clear(); }

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    LinkedList(LinkedList&& other) noexcept
        : head_(other.head_), size_(other.size_), alloc_(other.alloc_.resource())
    {
        other.head_ = nullptr;
        other.size_ = 0;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this == &other) return *this;
        clear();
        head_ = other.head_;
        size_ = other.size_;
        other.head_ = nullptr;
        other.size_ = 0;
        return *this;
    }

    template <class... Args>
    T& emplace_front(Args&&... args) {
        Node* n = alloc_.allocate(1);
        try {
            std::construct_at(n, head_, std::forward<Args>(args)...);
        } catch (...) {
            alloc_.deallocate(n, 1);
            throw;
        }
        head_ = n;
        ++size_;
        return head_->value;
    }

    void push_front(const T& v) { emplace_front(v); }
    void push_front(T&& v) { emplace_front(std::move(v)); }

    void pop_front() {
        if (!head_) return;
        Node* n = head_;
        head_ = head_->next;
        std::destroy_at(n);
        alloc_.deallocate(n, 1);
        --size_;
    }

    void clear() {
        while (head_) pop_front();
    }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return head_ == nullptr; }

    iterator begin() noexcept { return iterator(head_); }
    iterator end() noexcept { return iterator(nullptr); }
    const_iterator begin() const noexcept { return const_iterator(head_); }
    const_iterator end() const noexcept { return const_iterator(nullptr); }
    const_iterator cbegin() const noexcept { return const_iterator(head_); }
    const_iterator cend() const noexcept { return const_iterator(nullptr); }

private:
    Node* head_{nullptr};
    std::size_t size_{0};
    NodeAlloc alloc_;
};
