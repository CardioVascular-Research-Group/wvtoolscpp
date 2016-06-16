//
// Created by rliu14 on 6/16/16.
//

#include "InfoReader.h"

#include <boost/regex.hpp>
using boost::regex;

using std::string;
using std::exception;

#include <fstream>
using std::ifstream;

InfoReader::InfoReader(const std::string &prefix) throw(IOException) {
    regex expression("([0-9a-zA-Z\\-.]+) (\\d+) 1 ([0-9a-zA-Z]+)");

    string line;
    ifstream file(prefix + ".info");

    if (file.is_open()) {
        do {
            getline(file, line);

        } while(line.length() > 0);
    } else {
        throw IOException("Couldn't read file");
    }
}

