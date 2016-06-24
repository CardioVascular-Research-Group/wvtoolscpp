//
// Created by rliu14 on 6/24/16.
//

#include "FeatureCalculator.h"

FeatureCalculator::FeatureCalculator(const std::vector<unsigned long> &qrs_onsets) : qrs_onsets(qrs_onsets) {

}

std::vector<double> FeatureCalculator::calculateFeatures(const std::vector<double> &observations) {
    return std::vector<double>();
}

