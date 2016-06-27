//
// Created by rliu14 on 6/27/16.
//

#include <gtest/gtest.h>
#include <cmath>

#include "../src/util/FeatureCalculator.h"

using std::vector;
using std::cout;
using std::endl;
using std::sqrt;

TEST(feature_calculator_test, test_interval_calculation) {

    vector<unsigned long> onsets = {3, 10, 27};
    FeatureCalculator calculator(onsets, 35);

    EXPECT_EQ(calculator.qrs_intervals.size(), 35);
    EXPECT_EQ(calculator.qrs_intervals[3], 7);
    EXPECT_EQ(calculator.qrs_intervals[10], 17);
    EXPECT_EQ(calculator.qrs_intervals[9], 7);

}

TEST(feature_calculator_test, test_feature_calculation) {


    vector<unsigned long> onsets = {3, 10, 27};
    FeatureCalculator calculator(onsets, 35);

    vector<double> observations = {1, 2, 3, 4, 5};
    auto features = calculator.calculate_features(observations, 0);

    EXPECT_EQ(features[0], 3);
    EXPECT_EQ(features[1], 2);
    EXPECT_EQ(features[2], sqrt(2));
    EXPECT_EQ(features[3], 4);
    EXPECT_EQ(features[4], 1);
}

TEST(feature_calculator_test, calculate_mode) {

    vector<double> observations = {1, 3, 3, 1, 2, 3, 4, 3.21, 5.2};
    EXPECT_EQ(FeatureCalculator::mode(observations), 3);
}