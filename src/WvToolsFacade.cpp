//
// Created by rliu14 on 6/16/16.
//

#include <iostream>
using std::cerr;
using std::endl;

#include "WvToolsFacade.h"
#include "io/DataWriter.h"
#include "io/PhysionetWriter.h"

void WvToolsFacade::write_data(std::ostream &os, const std::string &prefix, const bool &scaled, const bool &headers,
                               const bool &timestamps) {
    try {
        InfoReader info_reader(prefix);
        DataWriter writer(os);
    } catch (IOException& e) {
        cerr << e.get_message() << endl;
    }
}

void WvToolsFacade::write_physionet(std::ostream &os, const std::string &prefix) {
    try {
        InfoReader info_reader(prefix);
        PhysionetWriter writer(os);
    } catch (IOException& e) {
        cerr << e.get_message() << endl;
    }
}

