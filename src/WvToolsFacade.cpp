//
// Created by rliu14 on 6/16/16.
//

#include <iostream>
using std::cerr;
using std::endl;

#include "WvToolsFacade.h"
#include "io/DataWriter.h"
#include "io/PhysionetWriter.h"
#include "util/ChecksumCalculator.h"

void WvToolsFacade::write_data(std::ostream &os, const std::string &prefix, const bool &scaled, const bool &headers,
                               const bool &timestamps) {
    try {
        InfoReader info_reader(prefix);
        WvReader wv_reader(prefix);

        DataWriter writer(os);
        writer.write(info_reader, wv_reader, headers, timestamps, scaled);
        wv_reader.close();
    } catch (IOException& e) {
        cerr << e.get_message() << endl;
    }
}

void WvToolsFacade::write_physionet(std::ostream &os, const std::string &prefix) {
    try {
        InfoReader info_reader(prefix);
        WvReader wv_reader(prefix);

        PhysionetWriter writer(os);
        writer.write(info_reader, wv_reader, prefix);
        wv_reader.close();
    } catch (IOException& e) {
        cerr << e.get_message() << endl;
    }
}


void WvToolsFacade::write_checksums(std::ostream &os, const std::string &prefix) {
    try {
        InfoReader info_reader(prefix);
        WvReader wv_reader(prefix);

        ChecksumCalculator calculator(info_reader.num_channels());
        while (wv_reader.has_next()) {
            calculator.add(wv_reader.next());
        }
        wv_reader.close();

        for (unsigned long c = 0; c < info_reader.num_channels(); c++) {
            os << calculator.get(c);
            if (c + 1 < info_reader.num_channels()) {
                os << "\t";
            }
        }
        os << endl;

    } catch (IOException& e) {
        cerr << e.get_message() << endl;
    }

}

