//
// Created by rliu14 on 6/17/16.
//

#include "PhysionetWriter.h"
#include "../util/ChecksumCalculator.h"

using std::endl;

PhysionetWriter::PhysionetWriter(std::ostream &os) : os(os) {

}


void PhysionetWriter::write(InfoReader &info_reader, WvReader &wv_reader, const std::string &prefix) {

    // Calculate checksums
    ChecksumCalculator calculator(info_reader.num_channels());
    while (wv_reader.has_next()) calculator.add(wv_reader.next());

    // Write record line: name, # signals, sampling frequency, # samples per signal
    os << prefix << " " << info_reader.num_channels() << " " << info_reader.sample_rate << " " << wv_reader.num_entries() / info_reader.num_channels() << endl;

    // Write signal lines
    for (unsigned long c = 0; c < info_reader.num_channels(); c++) {
        os << prefix << ".dat 16 " << info_reader.gains[c] << "/" << info_reader.units[c] << " 16 0 0 " << calculator.get(c) << " 0 " << info_reader.channel_labels[c] << endl;
    }

}

