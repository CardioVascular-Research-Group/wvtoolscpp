//
// Created by rliu14 on 6/17/16.
//

#include "ChecksumCalculator.h"


ChecksumCalculator::ChecksumCalculator(const unsigned long &num_channels) {
    current_index = 0;
    for (unsigned long c = 0; c < num_channels; c++) {
        checksums.push_back(0);
    }
}

void ChecksumCalculator::add(__int16_t value) {
    unsigned long current_channel = current_index++ % checksums.size();
    checksums[current_channel] += value;
}

__int16_t ChecksumCalculator::get(const unsigned long &channel_index) {
    return checksums[channel_index];
}

