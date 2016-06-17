//
// Created by rliu14 on 6/17/16.
//

#include "DataWriter.h"

using std::endl;

DataWriter::DataWriter(std::ostream &os) : os(os) {

}

void DataWriter::write(InfoReader& info_reader, WvReader& wv_reader, const bool& headers, const bool& timestamps, const bool& scaled) {
    if (headers) {
        for (unsigned int c = 0; c < info_reader.channel_labels.size(); c++) {
            os << info_reader.channel_labels[c];
            if (scaled) {
                os << "(" << info_reader.units[c] << ")";
            }
            if (c + 1 == info_reader.channel_labels.size()) {
                os << endl;
            } else {
                os << "\t";
            }
        }
    }

    unsigned long num_entries_read = 0;
    unsigned long num_channels = info_reader.channel_labels.size();
    unsigned long last_channel = num_channels - 1;

    while (wv_reader.has_next()) {
        unsigned long current_channel = num_entries_read % num_channels;
        __int16_t value = wv_reader.next();

        if (scaled) {
            double scaled_value = info_reader.gains[current_channel] * value;
            os << scaled_value;
        } else {
            os << value;
        }

        if (current_channel == last_channel) {
            os << endl;
        } else {
            os << "\t";
        }

        num_entries_read++;
    }
}

