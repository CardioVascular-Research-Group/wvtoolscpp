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
    std::vector<TsdbUploader::annotation_entry> convert_quality_annotations(std::vector<bool>& quality);
private:
    std::string prefix;

    InfoReader& info_reader;
    TimestampCalculator& timestamp_calculator;

    std::vector<std::string> metrics;
    unsigned long current_index;

    TsdbUploader::annotation_entry generate_annotation_entry(const unsigned long& start_index, const unsigned long& end_index);

    bool contains(std::vector<std::string>& v, std::string value);

    friend class WvToolsFacade;

    FRIEND_TEST(tsdb_query_converter_test, test_metric_nomenclature);
};


