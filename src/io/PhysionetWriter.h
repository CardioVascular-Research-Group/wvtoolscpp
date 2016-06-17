//
// Created by rliu14 on 6/17/16.
//

#pragma once

#include <ostream>

class PhysionetWriter {
public:
    PhysionetWriter(std::ostream& os);
private:
    std::ostream& os;
};


