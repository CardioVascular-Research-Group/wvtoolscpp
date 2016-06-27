//
// Created by rliu14 on 6/27/16.
//

#pragma once

#include <gtest/gtest.h>

#include <vector>

class FeatureCalculator {
public:
    FeatureCalculator(const std::vector<unsigned long>& qrs_onsets, const unsigned long& total_length);
    std::vector<double> calculate_features(const std::vector<double>& observations, const unsigned long& index);
private:
    const std::vector<unsigned long>& qrs_onsets;
    std::vector<double> qrs_intervals;

    static void push_multiple(std::vector<double>& vector, const double& value, const unsigned long& quantity);
    static double mode(const std::vector<double>& vector);
    static unsigned long count(const std::vector<double>& vector, const double& value);

    FRIEND_TEST(feature_calculator_test, test_interval_calculation);
    FRIEND_TEST(feature_calculator_test, calculate_mode);

};


