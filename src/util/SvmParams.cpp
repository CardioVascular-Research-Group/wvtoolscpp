//
// Created by rliu14 on 6/24/16.
//

#include "SvmParams.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
using boost::algorithm::split;
using boost::algorithm::is_any_of;

#include <boost/regex.hpp>
using boost::regex;
using boost::cmatch;
using boost::regex_search;

#include <fstream>
using std::string;
using std::ifstream;

using std::stod;
using std::vector;

using std::cout;
using std::endl;


SvmParams::SvmParams(const std::vector<double> &coefficients, const std::vector<double> &means,
                     const std::vector<double> &sigmas, const double &bias) {
    this->coefficients = coefficients;
    this->means = means;
    this->sigmas = sigmas;
    this->bias = bias;
}


SvmParams::SvmParams(const std::string &filename) throw (IOException) {

    static regex coefficients("betas: ([0-9 .\\-]+)");
    static regex means("means: ([0-9 .\\-]+)");
    static regex sigmas("sigmas: ([0-9 .\\-]+)");
    static regex bias("bias: ([0-9.\\-]+)");

    ifstream file(filename);
    string current_line;
    cmatch matches;

    if (file.is_open()) {
        do {
            getline(file, current_line);

            if (regex_search(current_line.c_str(), matches, coefficients)) {
                this->coefficients = tokenize(matches[1]);
            } else if (regex_search(current_line.c_str(), matches, means)) {
                this->means = tokenize(matches[1]);
            } else if (regex_search(current_line.c_str(), matches, sigmas)) {
                this->sigmas = tokenize(matches[1]);
            } else if (regex_search(current_line.c_str(), matches, bias)) {
                this->bias = stod(matches[1]);
            }
        } while (current_line.length() > 0);
    } else {
        throw IOException("Couldn't open SVM parameters file.");
    }

    file.close();

}


double SvmParams::calculate_score(const std::vector<double> &features) {
    double score = 0;
    for (unsigned long c = 0; c < features.size(); c++) {
        score += (features[c] - means[c]) / sigmas[c] * coefficients[c];
    }
    return score;
}


std::vector<double> SvmParams::tokenize(const std::string &values) {
    vector<double> result;

    vector<string> tokens;
    split(tokens, values, is_any_of(" "));

    for (auto &s : tokens) {
        result.push_back(stod(s));
    }

    return result;
}

