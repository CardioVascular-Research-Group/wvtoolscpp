//
// Created by rliu14 on 6/16/16.
//

#include "IOException.h"


IOException::IOException(const std::string &message) {
    this->message = message;
}

const std::string &IOException::get_message() {
    return message;
}

