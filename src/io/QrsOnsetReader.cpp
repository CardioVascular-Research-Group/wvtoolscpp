//
// Created by rliu14 on 6/24/16.
//

#include "QrsOnsetReader.h"

#include <fstream>
using std::ifstream;
using std::stol;
using std::string;

QrsOnsetReader::QrsOnsetReader(const std::string &filename) throw (IOException) {
    ifstream file(filename);

    string current_line;

    if (file.is_open()) {
        do {
            getline(file, current_line);
            if (current_line.length() > 0) qrs_onsets.push_back((unsigned long)stol(current_line));
        } while (current_line.length() > 0);
    } else {
        throw IOException("Couldn't read QRS onset file.");
    }

    file.close();
}


const std::vector<unsigned long> &QrsOnsetReader::get_onsets() {
    return qrs_onsets;
}

