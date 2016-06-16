//
// Created by rliu14 on 6/16/16.
//

#pragma once

#include <string>

class IOException {
public:
    IOException(const std::string& message);
    const std::string& get_message();
private:
    std::string message;
};


