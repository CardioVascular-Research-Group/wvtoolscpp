//
// Created by rliu14 on 6/20/16.
//

#pragma once


#include <ostream>

class QualityChecker {
public:
    QualityChecker(std::ostream& os, const unsigned int& threshold);
    void read(const __int16_t& value);
    void flush();
private:
    std::ostream& os;
    __int16_t last_value;
    unsigned int count;
    unsigned int threshold;
};


