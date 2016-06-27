//
// Created by rliu14 on 6/27/16.
//

#pragma once


#include "SvmParams.h"

class QualityChecker {
public:
    QualityChecker(const unsigned long& constant_threshold, SvmParams& svm_params);
    void print_stats(std::ostream& os);
    void print_qualities(std::ostream& os);
    void read(const std::vector<double>& features);
private:
    SvmParams& svm_params;

    unsigned long constant_threshold;

    unsigned long num_constant;
    unsigned long num_good;
    unsigned long num_bad;

    std::vector<bool> quality;
};


