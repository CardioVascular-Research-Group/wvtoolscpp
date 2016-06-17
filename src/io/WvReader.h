//
// Created by rliu14 on 6/17/16.
//

#pragma once

#include <string>
#include <fstream>

#include "IOException.h"

/**
 * Reads waveform data.
 */
class WvReader {
public:
    WvReader(const std::string& prefix) throw (IOException);
    long size();
    __int16_t next();
    bool has_next();
    void close();
private:
    std::ifstream file;
    long file_size;
};

