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
        EXPECT_EQ(reader.size(), 16);
        reader.close();
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
        reader.close();

        EXPECT_EQ(8, values.size());
        EXPECT_EQ(206, values[0]);
        EXPECT_EQ(100, values[1]);
        EXPECT_EQ(11293, values[2]);
        EXPECT_EQ(6735, values[3]);
        EXPECT_EQ(200, values[4]);
        EXPECT_EQ(100, values[5]);
        EXPECT_EQ(11667, values[6]);
        EXPECT_EQ(6735, values[7]);

    } catch (IOException& e) {
        cerr << e.get_message();
        FAIL();
    }
}