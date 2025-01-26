//
// Created by oddgeir on 1/25/25.
//

#include <gtest/gtest.h>
#include "libcalc.h"

// Demonstrate some basic assertions.
TEST(CalculatorTest, SimpleTest) {
    // Expect two strings not to be equal.
    // Expect equality.
    EXPECT_EQ(libcalc::evaluate("4+3"), "7");

}

TEST(CalculatorTest, SimpleTest2) {
    EXPECT_EQ(libcalc::evaluate("4+5/2"), "6.5");
}

TEST(CalculatorTest, SimpleTest3) {
    EXPECT_EQ(libcalc::evaluate("50/2+5"), "30");
}

TEST(CalculatorTest, SimpleTest4) {
    EXPECT_EQ(libcalc::evaluate("(4/2*6)/4"), "3");
}
