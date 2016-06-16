//
// Created by rliu14 on 6/16/16.
//

#include <gtest/gtest.h>
#include "../src/io/InfoReader.h"

TEST(info_reader_test, initial) {
    try {
        InfoReader reader("data/test");

        EXPECT_EQ(reader.channel_labels.size(), 2);

    } catch (IOException& e) {
        std::cerr << e.get_message();
        FAIL();
    }
}