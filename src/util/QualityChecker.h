//
// Created by rliu14 on 6/24/16.
//

#pragma once

#include <ostream>
#include <vector>

/**
 * Quality checker.
 */
class QualityChecker {
public:
    void print_stats(std::ostream& os);
    bool check_quality(const std::vector<double>& feature_vector);
};


