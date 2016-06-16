//
// Created by rliu14 on 6/16/16.
//

#include <gtest/gtest.h>

using std::cout;
using std::endl;

// A trivial test that determines whether our testing framework is functioning properly.
TEST(hello_test, initial) {
    cout << "Hello, world!" << endl;
    EXPECT_EQ(1, 1);
}