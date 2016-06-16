//
// Created by rliu14 on 6/16/16.
//

#include <gtest/gtest.h>
#include "../src/io/InfoReader.h"

TEST(info_reader_test, initial) {
    try {
        InfoReader reader("data/test");

        EXPECT_EQ(reader.channel_labels.size(), 2);

        EXPECT_EQ(reader.channel_labels[0], "ECG");
        EXPECT_EQ(reader.channel_labels[1], "PLETH");

        EXPECT_EQ(reader.gains.size(), 2);
        EXPECT_DOUBLE_EQ(reader.gains[0], 0.123);
        EXPECT_DOUBLE_EQ(reader.gains[1], 4.321);

    } catch (IOException& e) {
        std::cerr << e.get_message();
        FAIL();
    }
}