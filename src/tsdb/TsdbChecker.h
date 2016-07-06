//
// Created by ran on 7/5/16.
//

#ifndef WVTOOLS_TSDBCHECKER_H
#define WVTOOLS_TSDBCHECKER_H

#include <string>
#include "../io/WvReader.h"
#include "../io/InfoReader.h"
#include "../io/TimestampReader.h"

using std::string;

class TsdbChecker {
public:
    TsdbChecker(const std::string& tsdb_root);
    bool check_presence(const std::string& metric, const std::string& subject_id, const unsigned long& start_time);
    bool validate(const std::string& metric, const std::string& subject_id, WvReader& wv_reader, InfoReader& info_reader, TimestampReader& timestamp_reader);
private:
    std::string tsdb_root;
};


#endif //WVTOOLS_TSDBCHECKER_H
