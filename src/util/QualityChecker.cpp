//
// Created by rliu14 on 6/27/16.
//

#include "QualityChecker.h"

using std::endl;

QualityChecker::QualityChecker(const unsigned long &constant_threshold, SvmParamsReader &svm_params) : svm_params(svm_params) {

}

void QualityChecker::print_stats(std::ostream &os) {
    os << num_good << "\t" << num_constant << "\t" << num_bad << endl;
}

void QualityChecker::print_qualities(std::ostream &os) {
    for (auto &v : quality) {
        os << v << endl;
    }
}

void QualityChecker::read(const std::vector<double> &features) {
    if (features[4] == 625) {
        num_constant++;
        quality.push_back(false);
    } else {
        //
    }

}

