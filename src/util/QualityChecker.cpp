//
// Created by rliu14 on 6/20/16.
//

#include "QualityChecker.h"

using std::endl;

QualityChecker::QualityChecker(std::ostream &os, const unsigned int& threshold) : os(os) {
    this->threshold = threshold;
    count = 0;
    last_value = 0;
}

void QualityChecker::read(const __int16_t &value) {
    if (value == last_value) {
        count++;
    } else {
        last_value = value;
        flush();
    }
}

void QualityChecker::flush() {
    // We output 1s for quality, 0s for non-quality.
    if (count < threshold) {
        for (unsigned int c = 0; c < count; c++) {
            os << 1 << endl;
        }
    } else {
        for (unsigned int c = 0; c < count; c++) {
            os << 0 << endl;
        }
    }
    count = 1;
}

