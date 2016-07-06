//
// Created by ran on 7/5/16.
//

#include <restclient-cpp/restclient.h>

#include "TsdbChecker.h"

TsdbChecker::TsdbChecker() {

}

bool TsdbChecker::check_presence(const std::string &metric, const std::string &subject_id) {
    return false;
}

bool TsdbChecker::validate(const std::string &metric, const std::string &subject_id, WvReader &wv_reader,
                           InfoReader &info_reader) {
    return false;
}

