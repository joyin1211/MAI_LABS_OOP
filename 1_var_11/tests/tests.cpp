#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/func.hpp"

TEST(ClosestPairToNum, SmallValues) {
    EXPECT_EQ(closest_pair_tonum(5), std::pair(-1, -1));
    EXPECT_EQ(closest_pair_tonum(4), std::pair(-1, -1));
    EXPECT_EQ(closest_pair_tonum(1), std::pair(-1, -1));
    EXPECT_EQ(closest_pair_tonum(-2), std::pair(-1, -1));
}

TEST(ClosestPairToNum, Sample) {
    EXPECT_EQ(closest_pair_tonum(10), std::pair(5, 4));
    EXPECT_EQ(closest_pair_tonum(30), std::pair(29, 20));
    EXPECT_EQ(closest_pair_tonum(50), std::pair(45, 36));
}

TEST(ClosestPairToNum, SomeValues) {
  EXPECT_EQ(closest_pair_tonum(70), std::pair(65, 56));
  EXPECT_EQ(closest_pair_tonum(100), std::pair(97, 72));
  EXPECT_EQ(closest_pair_tonum(200), std::pair(193, 168));
}

TEST(ClosestPairToNum, BigNumberTL) {
  auto start = std::chrono::steady_clock::now();
  closest_pair_tonum(INT_MAX);
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  ASSERT_LT(elapsed.count(), 1);
}