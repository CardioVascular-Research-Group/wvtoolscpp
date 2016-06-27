//
// Created by rliu14 on 6/27/16.
//

#include "FeatureCalculator.h"

#include <boost/bind.hpp>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/variance.hpp>

#include <unordered_map>

using std::unordered_map;
using std::sqrt;

using namespace boost::accumulators;
using boost::bind;
using boost::ref;

using std::vector;
using std::for_each;

#include <iostream>
using std::cout;
using std::endl;

FeatureCalculator::FeatureCalculator(const std::vector<unsigned long> &qrs_onsets, const unsigned long& total_length) : qrs_onsets(qrs_onsets) {
    push_multiple(qrs_intervals, qrs_onsets[1] - qrs_onsets[0], qrs_onsets[0]);
    for (unsigned long index = 1; index < qrs_onsets.size(); index++) {
        auto interval_width = qrs_onsets[index] - qrs_onsets[index-1];
        push_multiple(qrs_intervals, interval_width, interval_width);
    }
    push_multiple(qrs_intervals, qrs_onsets[qrs_onsets.size() - 1] - qrs_onsets[qrs_onsets.size() - 2], total_length - qrs_onsets[qrs_onsets.size() - 1]);
}


std::vector<double> FeatureCalculator::calculate_features(const std::vector<double> &observations, const unsigned long &index) {
    vector<double> result;

    accumulator_set<double, features<tag::min, tag::mean, tag::max, tag::variance>> accumulator;
    accumulator_set<double, features<tag::min, tag::mean, tag::max, tag::variance>> qrs_accumulator;
    for (auto &v : observations) {
        accumulator(v);
    }
    for (unsigned long c = index; c < index + observations.size(); c++) {
        qrs_accumulator(qrs_intervals[c]);
    }

    result.push_back(mean(accumulator));
    result.push_back(variance(accumulator) * 625/624); // We want sample, not population variance. Normalize by n/n-1.
    result.push_back(sqrt(variance(accumulator) * 625/624));
    result.push_back(max(accumulator) - min(accumulator));
    result.push_back(count(observations, mode(observations)));
    result.push_back(mean(qrs_accumulator));
    result.push_back(sqrt(variance(qrs_accumulator) * 625/624));
    result.push_back(max(qrs_accumulator) - min(qrs_accumulator));

    return result;
}


double FeatureCalculator::mode(const std::vector<double> &vector) {
    unordered_map<double, int> counts;
    for (auto& d : vector) {
        if (counts.find(d) == counts.end()) {
            counts[d] = 1;
        } else {
            counts[d] += 1;
        }
    }
    int max_count = 0;
    double mode = 0;
    for (unordered_map<double, int>::iterator it = counts.begin(); it != counts.end(); ++it) {
        if (it->second > max_count) {
            max_count = it->second;
            mode = it->first;
        }
    }
    return mode;
}


unsigned long FeatureCalculator::count(const std::vector<double> &vector, const double &value) {
    unsigned long result = 0;
    for (auto& d: vector) {
        if (d == value) result++;
    }
    return result;
}


void FeatureCalculator::push_multiple(std:: vector<double> &vector, const double &value, const unsigned long &quantity) {
    for (unsigned long c = 0; c < quantity; c++) {
        vector.push_back(value);
    }
}
