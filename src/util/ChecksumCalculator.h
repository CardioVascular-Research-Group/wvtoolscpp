//
// Created by rliu14 on 6/17/16.
//

#pragma once

#include <ctype.h>
#include <vector>

/**
 * Calculates checksums.
 */
class ChecksumCalculator {
public:
    ChecksumCalculator(const unsigned long& num_channels);
    void add(__int16_t value);
    __int16_t get(const unsigned long &channel_index);
private:
    unsigned long current_index;
    std::vector<__int16_t> checksums;
};