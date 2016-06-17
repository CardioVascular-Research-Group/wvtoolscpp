//
// Created by rliu14 on 6/17/16.
//

#pragma once

#include <zconf.h>
#include <vector>

/**
 * Calculates checksums.
 */
class ChecksumCalculator {
public:
    ChecksumCalculator(const unsigned int& num_channels);
    void add(__int16_t value);
    __int16_t get(const unsigned int &channel_index);
private:
    unsigned long current_index;
    std::vector<__int16_t> checksums;
};