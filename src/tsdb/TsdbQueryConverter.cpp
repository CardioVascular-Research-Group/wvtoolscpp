//
// Created by rliu14 on 6/29/16.
//

#include "TsdbQueryConverter.h"

#include <boost/algorithm/string.hpp>

using nlohmann::json;
using std::vector;

TsdbQueryConverter::TsdbQueryConverter(const std::string& prefix, InfoReader &info_reader, TimestampCalculator& timestamp_calculator) : info_reader(info_reader), timestamp_calculator(timestamp_calculator) {
    this->prefix = prefix;
    current_index = 0;

    for (std::string& s : info_reader.channel_labels) {
        metrics.push_back(boost::algorithm::to_lower_copy(s));
    }
}

TsdbUploader::data_entry TsdbQueryConverter::convert_scaled_data(const double &scaled_data_point) {
    auto current_channel = current_index % info_reader.num_channels();
    auto current_offset = current_index++ / info_reader.num_channels();

    TsdbUploader::data_entry entry;
    entry.metric = metrics[current_channel];
    entry.timestamp = (unsigned long)timestamp_calculator.calculate_timestamp(timestamp_calculator.calculate_offset(current_offset));
    entry.tags = {{"subject_id", prefix}};
    entry.value = scaled_data_point;

    return entry;
}


std::vector<TsdbUploader::annotation_entry> TsdbQueryConverter::convert_quality_annotations(std::vector<bool> &quality) {
    vector<TsdbUploader::annotation_entry> result;

    unsigned long current_start_index = 0;

    bool was_true = false;

    for (unsigned long c = 0; c < quality.size(); c++) {
        if (!was_true && quality[c]) {
            current_start_index = c;
            was_true = true;
        } else if (was_true && !quality[c]) {
            was_true = false;
            result.push_back(generate_annotation_entry(current_start_index * 625, c * 625 - 1));
        }
    }
    if (was_true) {
        result.push_back(generate_annotation_entry(current_start_index * 625, quality.size() * 625 - 1));
    }

    return result;
}


TsdbUploader::annotation_entry TsdbQueryConverter::generate_annotation_entry(const unsigned long &start_index,
                                                                             const unsigned long &end_index) {
    TsdbUploader::annotation_entry entry;
    entry.description = "good";
    entry.start_time = (unsigned long)timestamp_calculator.calculate_timestamp(timestamp_calculator.calculate_offset(start_index));
    entry.end_time = (unsigned long)timestamp_calculator.calculate_timestamp(timestamp_calculator.calculate_offset(end_index));

    return entry;
}

