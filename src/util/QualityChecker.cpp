//
// Created by rliu14 on 6/27/16.
//

#include "QualityChecker.h"

using std::endl;

QualityChecker::QualityChecker(const unsigned long &constant_threshold, SvmParams &svm_params) : svm_params(svm_params) {
    this->constant_threshold = constant_threshold;
}

void QualityChecker::print_stats(std::ostream &os) {
    os << num_good << "\t" << num_constant << "\t" << num_bad << endl;
}

void QualityChecker::print_qualities(std::ostream &os) {
    for (bool v : quality) {
        os << v << endl;
    }
}

void QualityChecker::read(const std::vector<double> &features) {
    if (features[4] >= constant_threshold) {
        num_constant++;
        quality.push_back(false);
    } else {
        auto score = svm_params.calculate_score(features);
        if (score + svm_params.bias < 0) {
            num_bad++;
            quality.push_back(false);
        } else {
            num_good++;
            quality.push_back(true);
        }
    }
}



