//
// Created by rliu14 on 6/24/16.
//

#pragma once

#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "IOException.h"

/**
 * Reads SVM parameters.
 */
class SvmParamsReader {
public:
    SvmParamsReader(const std::string& filename) throw (IOException);
private:
    std::vector<double> coefficients;
    std::vector<double> means;
    std::vector<double> sigmas;
    double bias;

    double calculate_score(const std::vector<double>& features);
    static std::vector<double> tokenize(const std::string& values);

    friend class QualityChecker;

    FRIEND_TEST(svm_params_reader_test, tokenize_test);
    FRIEND_TEST(svm_params_reader_test, read_file);
};


