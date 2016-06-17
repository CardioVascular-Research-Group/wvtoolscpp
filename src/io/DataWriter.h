//
// Created by rliu14 on 6/17/16.
//

#pragma once

#include <ostream>
#include "WvReader.h"
#include "InfoReader.h"

class DataWriter {
public:
    DataWriter(std::ostream& os);
    void write(InfoReader& info_reader, WvReader& wv_reader, const bool& headers, const bool& timestamps, const bool& scaled);
private:
    std::ostream& os;
};


