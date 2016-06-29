//
// Created by rliu14 on 6/29/16.
//

#pragma once

#include "../io/InfoReader.h"
#include "TsdbUploader.h"
#include "../util/TimestampCalculator.h"

/**
 * Converts multiplexed data into TSDB queries.
 */
class TsdbQueryConverter {
public:
    TsdbQueryConverter(const std::string& prefix, InfoReader& info_reader, TimestampCalculator& timestamp_calculator);
    TsdbUploader::data_entry convert_scaled_data(const double& scaled_data_point);
private:
    std::string prefix;

    InfoReader& info_reader;
    TimestampCalculator& timestamp_calculator;

    std::vector<std::string> metrics;
    unsigned long current_index;
};


