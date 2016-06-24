//
// Created by rliu14 on 6/24/16.
//

#pragma once

#include <vector>

/**
 * Calculates features for quality checking.
 */
class FeatureCalculator {
public:
    FeatureCalculator(const std::vector<unsigned long>& qrs_onsets);
    std::vector<double> calculateFeatures(const std::vector<double>& observations);
private:
    std::vector<double> calculateRRIntervals(unsigned long startIndex, unsigned long endIndex);
    const std::vector<unsigned long>& qrs_onsets;
    unsigned long current_observation;
};

