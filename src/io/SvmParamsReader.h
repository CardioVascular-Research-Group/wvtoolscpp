//
// Created by rliu14 on 6/24/16.
//

#pragma once

#include <string>
#include <vector>

/**
 * Reads SVM parameters.
 */
class SvmParamsReader {
public:
    SvmParamsReader(const std::string& filename);
private:
    std::vector<double> coefficients;
    std::vector<double> means;
    std::vector<double> sigmas;
    double bias;
};


