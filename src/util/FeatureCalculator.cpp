//
// Created by rliu14 on 6/24/16.
//

#include "FeatureCalculator.h"

using std::vector;

FeatureCalculator::FeatureCalculator(const std::vector<unsigned long> &qrs_onsets) : qrs_onsets(qrs_onsets) {
    current_observation = 0;
}

std::vector<double> FeatureCalculator::calculateFeatures(const std::vector<double> &observations) {
    vector<double> results;

    // TODO

    return results;
}

/**
 * Calculates R-R intervals for the given span.
 */
std::vector<double> FeatureCalculator::calculateRRIntervals(unsigned long startIndex, unsigned long endIndex) {
    return std::vector<double>();
}

