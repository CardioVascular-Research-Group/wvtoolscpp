//
// Created by rliu14 on 6/16/16.
//

#pragma once

#include <ostream>

/**
 * Facade interface.
 */
class WvToolsFacade {
public:
    void write_data(std::ostream &os, const std::string& prefix, const bool& scaled, const bool& headers, const bool& timestamps);
    void write_physionet(std::ostream &os, const std::string& prefix);
    void write_checksums(std::ostream &os, const std::string& prefix);
    void write_quality(std::ostream &os, const std::string &prefix, const unsigned int &channel, const std::string &svm);
    void write_features(std::ostream &os, const std::string &prefix, const unsigned int &channel);
    void write_num_channels(std::ostream & os, const std::string& prefix);
};

