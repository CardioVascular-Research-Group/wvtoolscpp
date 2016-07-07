//
// Created by ran on 7/5/16.
//

#ifndef WVTOOLS_TSDBCHECKER_H
#define WVTOOLS_TSDBCHECKER_H

#include <string>
#include "../io/WvReader.h"
#include "../io/InfoReader.h"
#include "../io/TimestampReader.h"
#include "../util/TimestampCalculator.h"

class TsdbChecker {
public:
    TsdbChecker(const std::string& tsdb_root);
    bool check_presence(const std::string& metric, const std::string& subject_id, const unsigned long& start_time);
    std::vector<bool> validate(const std::string& prefix, InfoReader& info_reader, WvReader& wv_reader, TimestampReader& timestamp_reader, TimestampCalculator& timestamp_calculator, const int& query_size);
    std::vector<double> read(const std::string& prefix, const std::string& metric, const unsigned long& start_time);
private:
    std::string tsdb_root;
};


#endif //WVTOOLS_TSDBCHECKER_H
