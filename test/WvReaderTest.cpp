//
// Created by rliu14 on 6/17/16.
//

#include <gtest/gtest.h>
#include "../src/io/WvReader.h"

using std::cout;
using std::cerr;
using std::endl;

TEST(wv_reader_test, test_file_size) {

    try {
        WvReader reader("data/test");
        EXPECT_EQ(reader.size(), 6);
    } catch (IOException& e) {
        cerr << e.get_message();
        FAIL();
    }

}

TEST(wv_reader_test, test_file_input) {
    try {
        std::vector<__int16_t> values;
        WvReader reader("data/test");
        while (reader.has_next()) values.push_back(reader.next());

        EXPECT_EQ(3, values.size());
        EXPECT_EQ(-1503, values[0]);
        EXPECT_EQ(-20686, values[1]);
        EXPECT_EQ(63, values[2]);

    } catch (IOException& e) {
        cerr << e.get_message();
        FAIL();
    }
}