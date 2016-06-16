//
// Created by rliu14 on 6/16/16.
//

#ifndef WVTOOLS_INFOREADER_H
#define WVTOOLS_INFOREADER_H

#include <string>
#include <vector>

/**
 * Reads .info files.
 */
class InfoReader {
public:
    InfoReader(const std::string& prefix);
private:
    double sample_rate;
    std::vector<std::string> channel_labels;
    std::vector<std::string> units;
    std::vector<double> gains;
};


#endif //WVTOOLS_INFOREADER_H
