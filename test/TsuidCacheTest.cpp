//
// Created by ran on 7/5/16.
//


#include <gtest/gtest.h>

#include "../src/tsdb/TsuidCache.h"

using std::string;

TEST(tsuid_test, tests) {

    TsuidCache cache;
    cache.put("ecg", "asdf", "001010101");

    EXPECT_TRUE(cache.contains_subject("asdf"));
    EXPECT_TRUE(cache.contains("ecg", "asdf"));
    EXPECT_EQ(cache.get_tsuid("ecg", "asdf"), "001010101");


}