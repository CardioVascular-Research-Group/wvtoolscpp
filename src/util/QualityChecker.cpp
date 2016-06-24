//
// Created by rliu14 on 6/24/16.
//

#include "QualityChecker.h"

using std::endl;

void QualityChecker::print_stats(std::ostream &os) {
    os << "good: " << good_windows << ", bad: " << bad_windows << ", constant: " << constant_windows << ", total: " << total_windows << endl;
}

bool QualityChecker::check_quality(const std::vector<double> &feature_vector) {
    return false;
}

