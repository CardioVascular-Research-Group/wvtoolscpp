//
// Created by rliu14 on 6/17/16.
//

#include "WvReader.h"

#include <ios>
#include <fstream>
using std::ios;
using std::ifstream;

WvReader::WvReader(const std::string &prefix) throw (IOException) : file(prefix + ".wv", ios::binary | ios::ate) {
    if (file.is_open()) {
        file_size = file.tellg();
        file.seekg(0, ios::beg);
    } else {
        throw IOException("Couldn't open waveform file");
    }
}

long WvReader::size() {
    return file_size;
}


long WvReader::num_entries() {
    return file_size / 2; // 2 bytes comprise a 16-bit entry.
}


__int16_t WvReader::next() {
    unsigned char buffer[2];
    file.read((char*)buffer, 2);

    __int16_t result = (buffer[1] << 8) + buffer[0];
    return result;
}

bool WvReader::has_next() {
    long position = file.tellg();
    return position + 2 <= file_size;
}


void WvReader::close() {
    file.close();
}