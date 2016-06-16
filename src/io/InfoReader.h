//
// Created by rliu14 on 6/16/16.
//

#pragma once

#include "IOException.h"

#include <string>
#include <vector>
#include <gtest/gtest.h>

/**
 * Reads .info files.
 */
class InfoReader {
public:
    InfoReader(const std::string& prefix) throw(IOException);
private:
    double sample_rate;
    std::vector<std::string> channel_labels;
    std::vector<std::string> units;
    std::vector<double> gains;

    FRIEND_TEST(info_reader_test, initial);
};
