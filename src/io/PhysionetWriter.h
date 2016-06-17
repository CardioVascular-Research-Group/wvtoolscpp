//
// Created by rliu14 on 6/17/16.
//

#pragma once

#include <ostream>
#include "InfoReader.h"
#include "WvReader.h"

/**
 * Writes physionet headers.
 */
class PhysionetWriter {
public:
    PhysionetWriter(std::ostream& os);
    void write(InfoReader &info_reader, WvReader &wv_reader, const std::string &prefix);
private:
    std::ostream& os;
};

