#include "../src/single_block.hpp"
#include "../src/linkedlist.hpp"

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>
#include <vector>

struct Complex {
    int x;
    double y;
    std::int64_t z;
};

bool operator==(const Complex& a, const Complex& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

TEST(LinkedList, InitiallyEmpty) {
    single_block mr(16 * 1024);
    LinkedList<int> li(&mr);

    EXPECT_TRUE(li.empty());
    EXPECT_EQ(li.size(), 0);
    EXPECT_EQ(li.begin(), li.end());
}

TEST(LinkedList, PushFrontOrder) {
    single_block mr(16 * 1024);
    LinkedList<int> li(&mr);

    li.push_front(1);
    li.push_front(2);
    li.push_front(3);

    std::vector<int> got;
    for (int x : li) {
        got.push_back(x);
    }

    ASSERT_EQ(got.size(), 3);
    EXPECT_EQ(got[0], 3);
    EXPECT_EQ(got[1], 2);
    EXPECT_EQ(got[2], 1);

    EXPECT_FALSE(li.empty());
    EXPECT_EQ(li.size(), 3);
}

TEST(LinkedList, PopFrontWorks) {
    single_block mr(16 * 1024);
    LinkedList<int> li(&mr);

    li.push_front(10);
    li.push_front(20);
    li.push_front(30);

    li.pop_front();
    li.pop_front();

    std::vector<int> got;
    for (int x : li) {
        got.push_back(x);
    }

    ASSERT_EQ(got.size(), 1);
    EXPECT_EQ(got[0], 10);
    EXPECT_EQ(li.size(), 1);

    li.pop_front();
    EXPECT_TRUE(li.empty());
    EXPECT_EQ(li.size(), 0);

    li.pop_front();
    EXPECT_TRUE(li.empty());
}

TEST(LinkedList, ClearEmptiesList) {
    single_block mr(16 * 1024);
    LinkedList<int> li(&mr);

    for (int i = 0; i < 100; ++i) {
        li.push_front(i);
    }
    EXPECT_FALSE(li.empty());
    EXPECT_EQ(li.size(), 100);

    li.clear();
    EXPECT_TRUE(li.empty());
    EXPECT_EQ(li.size(), 0u);
    EXPECT_EQ(li.begin(), li.end());
}

TEST(LinkedList, IsForwardIterator) {
    using It = LinkedList<int>::iterator;
    using Cat = typename std::iterator_traits<It>::iterator_category;
    static_assert(std::is_same_v<Cat, std::forward_iterator_tag>,
                  "Iterator must be std::forward_iterator_tag");

    SUCCEED();
}

TEST(LinkedList, IteratorTraversal) {
    single_block mr(16 * 1024);
    LinkedList<int> li(&mr);

    li.push_front(1);
    li.push_front(2);
    li.push_front(3);

    auto it = li.begin();
    ASSERT_NE(it, li.end());
    EXPECT_EQ(*it, 3);
    ++it;
    ASSERT_NE(it, li.end());
    EXPECT_EQ(*it, 2);
    ++it;
    ASSERT_NE(it, li.end());
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(it, li.end());
}

TEST(LinkedList, WorksWithComplexType) {
    single_block mr(32 * 1024);
    LinkedList<Complex> lc(&mr);

    Complex a{1, 3.14, 100};
    Complex b{2, 2.71, 200};
    Complex c{3, 1.62, 300};

    lc.push_front(a);
    lc.push_front(b);
    lc.push_front(c);

    std::vector<Complex> got;
    for (const auto& x : lc) {
        got.push_back(x);
    }

    ASSERT_EQ(got.size(), 3);
    EXPECT_TRUE(got[0] == c);
    EXPECT_TRUE(got[1] == b);
    EXPECT_TRUE(got[2] == a);
}
