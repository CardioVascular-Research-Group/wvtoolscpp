//
// Created by rliu14 on 6/24/16.
//

#include <gtest/gtest.h>
#include "../src/io/QrsOnsetReader.h"

using std::vector;
using std::cout;
using std::endl;

TEST(qrs_onset_reader_test, test_read) {
    QrsOnsetReader reader("data/test.wqrs.txt");
    const vector<unsigned long> onsets = reader.get_onsets();
    EXPECT_EQ(9, onsets.size());
    EXPECT_EQ(9, onsets[0]);
    EXPECT_EQ(51, onsets[1]);
    EXPECT_EQ(92, onsets[2]);
    EXPECT_EQ(133, onsets[3]);
    EXPECT_EQ(174, onsets[4]);


}