//
// Created by rliu14 on 6/17/16.
//

#include <gtest/gtest.h>
#include "../src/util/ChecksumCalculator.h"

using std::cout;
using std::endl;

TEST(checksum_calculator_test, test_single_channel) {
    ChecksumCalculator calculator(1);

    calculator.add(32767);
    EXPECT_EQ(calculator.get(0), 32767);
    calculator.add(1);
    EXPECT_NE(calculator.get(0), 32768);
    EXPECT_EQ(calculator.get(0), -32768);

}

TEST(checksum_calculator_test, test_multi_channel) {
    ChecksumCalculator calculator(3);

    calculator.add(2);
    calculator.add(5);
    calculator.add(35);
    calculator.add(-5);
    calculator.add(5);
    calculator.add(32);

    EXPECT_EQ(calculator.get(0), -3);
    EXPECT_EQ(calculator.get(1), 10);
    EXPECT_EQ(calculator.get(2), 67);
}