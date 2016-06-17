//
// Created by rliu14 on 6/16/16.
//

#include "InfoReader.h"

#include <boost/regex.hpp>
using boost::regex;
using boost::regex_search;
using boost::cmatch;

using std::string;
using std::exception;
using std::stoi;
using std::stod;

using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

InfoReader::InfoReader(const std::string &prefix) throw(IOException) {
    regex expression("[0-9a-zA-Z\\-.]+ (\\d+) 1 ([0-9a-zA-Z]+) \"([0-9a-zA-Z]+)\" gain=(\\d.\\d+)");

    string line;
    ifstream file(prefix + ".info");

    if (file.is_open()) {
        do {
            getline(file, line);
            cmatch matches;
            if (regex_search(line.c_str(), matches, expression)) {
                sample_rate = stoi(matches[1]);
                units.push_back(matches[2]);
                channel_labels.push_back(matches[3]);
                gains.push_back(stod(matches[4]));
            }
        } while(line.length() > 0);
    } else {
        throw IOException("Couldn't read info file");
    }
    file.close();
}

