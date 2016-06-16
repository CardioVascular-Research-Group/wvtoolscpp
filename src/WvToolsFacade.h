//
// Created by rliu14 on 6/16/16.
//

#pragma once

#include <ostream>

class WvToolsFacade {
public:
    void write_data(std::ostream &os, const std::string& prefix, const bool& scaled, const bool& headers, const bool& timestamps);
    void write_physionet(std::ostream &os, const std::string& prefix);
};

