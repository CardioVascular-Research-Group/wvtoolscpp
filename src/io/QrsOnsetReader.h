//
// Created by rliu14 on 6/24/16.
//

#pragma once

#include <string>
#include <vector>
#include "IOException.h"

class QrsOnsetReader {
public:
    QrsOnsetReader(const std::string& filename) throw (IOException);
    const std::vector<unsigned long>& get_onsets();
private:
    std::vector<unsigned long> qrs_onsets;
};


