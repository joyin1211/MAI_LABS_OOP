#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "../src/decimal.hpp"

TEST(DecimalTest, DefaultConstructor) {
    Decimal d;
    EXPECT_EQ(d.toString(), "0");
    EXPECT_EQ(d.getSize(), 1);
}

TEST(DecimalTest, StringConstructor) {
    Decimal d1("12345");
    EXPECT_EQ(d1.toString(), "12345");
    Decimal d2("00100");
    EXPECT_EQ(d2.toString(), "100");
    Decimal d3("0");
    EXPECT_EQ(d3.toString(), "0");
    Decimal d4("10000000000000000000000000");
    EXPECT_EQ(d4.toString(),"10000000000000000000000000");
}

TEST(DecimalTest, StringConstructorInvalid) {
    EXPECT_THROW(Decimal("12a34"), std::invalid_argument);
    EXPECT_THROW(Decimal("abc"), std::invalid_argument);
    EXPECT_THROW(Decimal("123 456"), std::invalid_argument);
}

TEST(DecimalTest, InitializerListConstructor) {
    Decimal d1({1, 2, 3, 4, 5});
    EXPECT_EQ(d1.toString(), "54321");
    Decimal d2({0, 0, 1});
    EXPECT_EQ(d2.toString(), "100");
    Decimal d3({0, 0, 0});
    EXPECT_EQ(d3.toString(), "0");
}

TEST(DecimalTest, InitializerListConstructorInvalid) {
    EXPECT_THROW(Decimal({1, 10, 5, 16, 0}), std::invalid_argument);
}

TEST(DecimalTest, AddToSimpleNoCarry) {
    Decimal a("12");
    Decimal b("34");
    EXPECT_EQ(a.addTo(b).toString(), "46");
}

TEST(DecimalTest, AddToCarryWithinSameLength) {
    Decimal a("19");
    Decimal b("7");
    EXPECT_EQ(a.addTo(b).toString(), "26");
}

TEST(DecimalTest, AddToCarryExtendsLength) {
    Decimal a("999");
    Decimal b("1");
    EXPECT_EQ(a.addTo(b).toString(), "1000");
}

TEST(DecimalTest, AddToAddingZero) {
    Decimal a("123456789");
    Decimal z("0");
    EXPECT_EQ(a.addTo(z).toString(), "123456789");
    EXPECT_EQ(z.addTo(a).toString(), "123456789");
}

TEST(DecimalTest, SubToSimple) {
    Decimal a("1000");
    Decimal b("1");
    EXPECT_EQ(a.subTo(b).toString(), "999");
}

TEST(DecimalTest, SubToBorrowAcrossDigits) {
    Decimal a("10000");
    Decimal b("1");
    EXPECT_EQ(a.subTo(b).toString(), "9999");
}

TEST(DecimalTest, SubToEqualResultsZero) {
    Decimal a("55555");
    Decimal b("55555");
    EXPECT_EQ(a.subTo(b).toString(), "0");
    EXPECT_EQ(a.subTo(b).getSize(), 1);
}

TEST(DecimalTest, SubToNegativeResult) {
    Decimal a("1");
    Decimal b("2");
    EXPECT_THROW(a.subTo(b), std::invalid_argument);
}

TEST(DecimalTest, CompareEqualSameString) {
    Decimal a("12345");
    Decimal b("12345");
    EXPECT_TRUE(a.isEqual(b));
    EXPECT_FALSE(a.isLess(b));
    EXPECT_FALSE(a.isGreater(b));
}

TEST(DecimalTest, CompareDifferentLengthsShorterIsLess) {
    Decimal a("999");
    Decimal b("1000");

    EXPECT_TRUE(a.isLess(b));
    EXPECT_FALSE(a.isGreater(b));
    EXPECT_FALSE(a.isEqual(b));

    EXPECT_TRUE(b.isGreater(a));
    EXPECT_FALSE(b.isLess(a));
    EXPECT_FALSE(b.isEqual(a));
}

TEST(DecimalTest, CompareSameLengthDifferentValue) {
    Decimal a("1200");
    Decimal b("1199");

    EXPECT_TRUE(a.isGreater(b));
    EXPECT_FALSE(a.isLess(b));
    EXPECT_FALSE(a.isEqual(b));

    EXPECT_TRUE(b.isLess(a));
    EXPECT_FALSE(b.isGreater(a));
    EXPECT_FALSE(b.isEqual(a));
}

TEST(DecimalTest, CompareWithZero) {
    Decimal z("0");
    Decimal a("1");
    
    EXPECT_TRUE(z.isLess(a));
    EXPECT_TRUE(a.isGreater(z));
}
