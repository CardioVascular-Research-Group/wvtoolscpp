//
// Created by ran on 7/5/16.
//

#ifndef WVTOOLS_TSDBCHECKER_H
#define WVTOOLS_TSDBCHECKER_H

#include <string>
#include "../io/WvReader.h"
#include "../io/InfoReader.h"

using std::string;

class TsdbChecker {
public:
    TsdbChecker();
    bool check_presence(const std::string& metric, const std::string& subject_id);
    bool validate(const std::string& metric, const std::string& subject_id, WvReader& wv_reader, InfoReader& info_reader);

};


#endif //WVTOOLS_TSDBCHECKER_H
